#include <stdio.h>

#include "contiki.h"
#include "contiki-lib.h"
#include "contiki-net.h"

// #include "net/uip.h"

// #include "net/uip-ds6.h"

#include "assert.h"

#define DEBUG DEBUG_PRINT
// #include "net/uip-debug.h"

#include "net/rime/broadcast.h"


#ifdef DEBUG
# ifndef PRINTF
#  define PRINTF printf
# endif
#endif

#define UDP_PORT 60000

#define PERIOD_TIME (CLOCK_SECOND /2)


typedef struct packet_t
{
	int seq;
	char op;
} __attribute__((packed))
packet_t;

#define PRINTPACKET(p) do { PRINTF("%c %d", (p).op, (p).seq); } while (0)

static struct uip_udp_conn *outconn, *inconn;

static void br_recv(struct broadcast_conn* c, const rimeaddr_t* f);
static struct broadcast_conn bc;
static struct broadcast_callbacks cb = { br_recv, NULL };

static void uc_recv(struct unicast_conn* c, const rimeaddr_t* from);
static struct unicast_conn uc;
static struct unicast_callbacks cu = { uc_recv, NULL };

rimeaddr_t remote_addr;


static void send_broadcast(packet_t* data, size_t len)
{
	//uip_udp_packet_send(outconn, data, len);

	packetbuf_copyfrom(data, len);
	//broadcast_send(&bc);
	unicast_send(&uc, &remote_addr);
	
	// PRINTF("send packet ");
	PRINTF("send packet to %d.%d ", remote_addr.u8[0], remote_addr.u8[1]);
	PRINTPACKET(*data);
	PRINTF("\n");
}

static void send_ping()
{
	static int seq = 0;

	packet_t p = {
		.seq = seq++,
		.op = 'p'
	};

	send_broadcast(&p, sizeof(p));
}

//static void send_pong(struct uip_udp_conn* conn, )

static void process_received(void* data, size_t len)
{
	packet_t* p = (packet_t*)data;

	PRINTF("got packet ");
	PRINTPACKET(*p);
	PRINTF("\n");

	if ('p' == p->op)
	{
		packet_t a = {
			.seq = p->seq,
			.op  = 'a'
		};

		send_broadcast(&a, sizeof(a));
	}
}

static void br_recv(struct broadcast_conn* c, const rimeaddr_t* f)
{
	unsigned char* msg = packetbuf_dataptr();
	size_t len = packetbuf_datalen();

	printf("Broadcast received from: %u.%u\n", f->u8[0], f->u8[1]);

	process_received(msg, len);
}

static void uc_recv(struct unicast_conn* c, const rimeaddr_t* f)
{
	unsigned char* msg = packetbuf_dataptr();
	size_t len = packetbuf_datalen();

	printf("Unicast received from: %u.%u\n", f->u8[0], f->u8[1]);

	process_received(msg, len);
}

PROCESS(broadcast_pinger, "broadcast_pinger");
AUTOSTART_PROCESSES(&broadcast_pinger);

PROCESS_THREAD(broadcast_pinger, ev, data)
{
	
	static struct etimer periodic_send;

	PROCESS_BEGIN();
	// PROCESS_PAUSE();

	//broadcast_open(&bc, 2012, &cb);
	unicast_open(&uc, 2012, &cu);

	remote_addr.u8[0] = 1;
	remote_addr.u8[1] = 0;
	if (rimeaddr_cmp(&remote_addr, &rimeaddr_node_addr))
	{
		remote_addr.u8[0] = 2;
	}

/*
	outconn = udp_broadcast_new(UIP_HTONS(UDP_PORT), NULL);
	udp_bind(outconn, UIP_HTONS(UDP_PORT));

	inconn = udp_new(NULL, UIP_HTONS(UDP_PORT), NULL);
	udp_bind(inconn, UIP_HTONS(UDP_PORT));
*/
	etimer_set(&periodic_send, /*random_rand() %*/ PERIOD_TIME);

	while (1)
	{
		//process_post(PROCESS_CURRENT(), PROCESS_EVENT_CONTINUE, NULL);
		PROCESS_WAIT_EVENT();
		PRINTF("new event %d\n", ev);
		
		/*if (tcpip_event == ev)
		{
			process_tcpip();
		}
		else 
			*/if (PROCESS_EVENT_TIMER == ev && data == &periodic_send)
		// else if (PROCESS_EVENT_CONTINUE == ev)
		{
			etimer_reset(&periodic_send);

			send_ping();

		}

	}
	/*
*/



	PROCESS_END();
}