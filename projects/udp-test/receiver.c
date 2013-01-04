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

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/*===========================================================================*/

static void get_ping(const packet_t* p);

/*===========================================================================*/

static void uc_recv(struct unicast_conn* c, const rimeaddr_t* from);
static struct unicast_conn uc;
static struct unicast_callbacks cu = { uc_recv, NULL };
static rimeaddr_t remote_addr;

static void init_network(void)
{
	unicast_open(&uc, 2012, &cu);

	remote_addr.u8[0] = 1;
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

	get_ping((packet_t*)msg);
}

/*===========================================================================*/

CCIF process_event_t ack_event;
static struct process* our_process;

static struct etimer periodic;

static void post_ack_ev(void)
{
	process_post(our_process, ack_event, NULL);
}

static void init_event_sys(void)
{
	ack_event = process_alloc_event();
	our_process = PROCESS_CURRENT();
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


static void get_ping(const packet_t* p)
{
	packet_t a = *p;
	a.op = 'a';

	send(&a);

	PRINTF("got packet ");
	PRINTPACKET(*p);
	PRINTF("\n");
}

/*===========================================================================*/

PROCESS(ping_receiver, "ping_receiver");
AUTOSTART_PROCESSES(&ping_receiver);

PROCESS_THREAD(ping_receiver, ev, data)
{


	PROCESS_BEGIN();

	// init_event_sys();
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
		// if (ack_event == ev)
		// {
		// 	send_ping();
		// }
	}

	PROCESS_END();
}



