#define DEBUG DEBUG_PRINT

#include <stdio.h>

#include "contiki.h"
#include "contiki-lib.h"
#include "contiki-net.h"

#include "net/rime/broadcast.h"



#ifdef DEBUG
# ifndef PRINTF
#  define PRINTF printf
# endif
#endif

typedef struct packet_t
{
	int seq;
	clock_time_t time;
	char op;
} __attribute__((packed))
packet_t;

#define PRINTPACKET(p) do { PRINTF("%c %d %u", (p).op, (p).seq, (unsigned int)(p).time); } while (0)

#define PERIOD_TIME (CLOCK_SECOND / 2)

#define PING_TIMEOUT (CLOCK_SECOND * 2)

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/*===========================================================================*/

static void get_pong(const packet_t* p);

/*===========================================================================*/

static void uc_recv(struct unicast_conn* c, const rimeaddr_t* from);
static struct unicast_conn uc;
static struct unicast_callbacks cu = { uc_recv, NULL };
static rimeaddr_t remote_addr;

static void init_network(void)
{
	unicast_open(&uc, 2012, &cu);

	remote_addr.u8[0] = 2;
	remote_addr.u8[1] = 0;
}

static void send(const packet_t* p)
{
	packetbuf_copyfrom(p, sizeof(packet_t));
	unicast_send(&uc, &remote_addr);
}

static void uc_recv(struct unicast_conn* c, const rimeaddr_t* f)
{
	unsigned char* msg = packetbuf_dataptr();
	// size_t len = packetbuf_datalen();

	get_pong((packet_t*)msg);
}

/*===========================================================================*/

CCIF process_event_t ack_event;
static struct process* our_process;

//static struct etimer periodic;

static struct ctimer timeout_timer;
static void timeout_event(void*);

static void post_ack_ev(void)
{
	process_post(our_process, ack_event, NULL);
}

static void init_event_sys(void)
{
	ack_event = process_alloc_event();
	our_process = PROCESS_CURRENT();

	ctimer_set(&timeout_timer, PING_TIMEOUT, timeout_event, NULL);
}

/*===========================================================================*/

#define TIME_SAMPLES_COUNT 32
static struct
{
	int seq;
	int lost;

	struct
	{
		clock_time_t min;
		clock_time_t max;
		clock_time_t values[TIME_SAMPLES_COUNT];
		int nvalues;
	} time;
} stats;


/*===========================================================================*/



static void send_ping(void)
{
	packet_t p = {
		.seq = stats.seq,
		.time = clock_time(),
		.op = 'p'
	};

	send(&p);
}

#define SEQ_INC do { ++stats.seq; } while (0)

static clock_time_t get_diff(clock_time_t t, clock_time_t now)
{
	if (now < t)
	{
		const clock_time_t max_val = (clock_time_t)~0;
		return now + (max_val - t);
	}
	else
	{
		return now - t;
	}
}

static void get_pong(const packet_t* p)
{
	clock_time_t now = clock_time();

	ctimer_restart(&timeout_timer);

	clock_time_t inflight = get_diff(p->time, now);

	if (stats.seq != p->seq)
	{
		stats.lost++;

		PRINTF("got lost packet ");
	}
	else
	{
		stats.time.min = MIN(stats.time.min, inflight);
		stats.time.max = MAX(stats.time.min, inflight);

		stats.time.values[stats.time.nvalues % TIME_SAMPLES_COUNT] = inflight;
		stats.time.nvalues++;

		PRINTF("got packet ");
	}

	post_ack_ev();


	PRINTPACKET(*p);
	PRINTF(" at time %u, in flight = %u\n", (unsigned int)now, (unsigned int)inflight);

	SEQ_INC;
}

static void timeout_event(void* a)
{
	SEQ_INC;
	stats.lost++;

	PRINTF("timeout\n");
}

/*===========================================================================*/

PROCESS(ping_sender, "ping_sender");
AUTOSTART_PROCESSES(&ping_sender);

PROCESS_THREAD(ping_sender, ev, data)
{


	PROCESS_BEGIN();

	init_event_sys();
	init_network();

	//etimer_set(&periodic, PERIOD_TIME);


	post_ack_ev();

	while (1)
	{
		PROCESS_WAIT_EVENT();

		// if (PROCESS_EVENT_TIMER == ev && data == &periodic)
		// {

		// }
		// else
		if (ack_event == ev)
		{
			send_ping();
		}
	}

	PROCESS_END();
}



