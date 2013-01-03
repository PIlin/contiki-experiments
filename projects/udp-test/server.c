#include "contiki.h"
#include "contiki-lib.h"
#include "contiki-net.h"
#include "net/uip.h"
#include "net/rpl/rpl.h"

#include "net/netstack.h"
#include "dev/button-sensor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "servreg-hack.h"

#define DEBUG DEBUG_PRINT
#include "net/uip-debug.h"

#define UIP_IP_BUF   ((struct uip_ip_hdr *)&uip_buf[UIP_LLH_LEN])

#define UDP_CLIENT_PORT	8765
#define UDP_SERVER_PORT	5678

#define SERVICE_ID 190

static struct uip_udp_conn *server_conn;

PROCESS(udp_server_process, "UDP server process");
AUTOSTART_PROCESSES(&udp_server_process);




static uip_ipaddr_t *
set_global_address(void)
{
  static uip_ipaddr_t ipaddr;
  int i;
  uint8_t state;

  uip_ip6addr(&ipaddr, 0xaaaa, 0, 0, 0, 0, 0, 0, 0);
  uip_ds6_set_addr_iid(&ipaddr, &uip_lladdr);
  uip_ds6_addr_add(&ipaddr, 0, ADDR_AUTOCONF);

  printf("IPv6 addresses: ");
  for(i = 0; i < UIP_DS6_ADDR_NB; i++) {
    state = uip_ds6_if.addr_list[i].state;
    if(uip_ds6_if.addr_list[i].isused &&
       (state == ADDR_TENTATIVE || state == ADDR_PREFERRED)) {
      uip_debug_ipaddr_print(&uip_ds6_if.addr_list[i].ipaddr);
      printf("\n");
    }
  }

  return &ipaddr;
}

static void
create_rpl_dag(uip_ipaddr_t *ipaddr)
{
  struct uip_ds6_addr *root_if;

  root_if = uip_ds6_addr_lookup(ipaddr);
  if(root_if != NULL) {
    rpl_dag_t *dag;
    uip_ipaddr_t prefix;

    rpl_set_root(RPL_DEFAULT_INSTANCE, ipaddr);
    dag = rpl_get_any_dag();
    uip_ip6addr(&prefix, 0xaaaa, 0, 0, 0, 0, 0, 0, 0);
    rpl_set_prefix(dag, &prefix, 64);
    PRINTF("created a new RPL dag\n");
  } else {
    PRINTF("failed to create a new RPL DAG\n");
  }
}

static void tcpip_handler()
{
	if (uip_newdata())
	{
		char *const appdata = (char *const) uip_appdata;
		appdata[uip_datalen()] = 0;
		PRINTF("DATA recv '%s' from ", appdata);
		PRINTF("%d", UIP_IP_BUF->srcipaddr.u8[sizeof(UIP_IP_BUF->srcipaddr.u8) - 1]);
		PRINTF("\n");

#if SERVER_REPLY
	    PRINTF("DATA sending reply\n");
	    uip_ipaddr_copy(&server_conn->ripaddr, &UIP_IP_BUF->srcipaddr);
	    uip_udp_packet_send(server_conn, "Reply", sizeof("Reply"));
	    uip_create_unspecified(&server_conn->ripaddr);
#endif
	}
}

PROCESS_THREAD(udp_server_process, ev, data)
{
	uip_ipaddr_t *ipaddr;

	PROCESS_BEGIN();

	PROCESS_PAUSE();



	PRINTF("UDP server started\n");

	servreg_hack_init();


	ipaddr = set_global_address();
	create_rpl_dag(ipaddr);
	servreg_hack_register(SERVICE_ID, ipaddr);

	//print_local_addresses();

	server_conn = udp_new(NULL, UIP_HTONS(UDP_CLIENT_PORT), NULL);
	if(server_conn == NULL) {
		PRINTF("No UDP connection available, exiting the process!\n");
		PROCESS_EXIT();
	}
	udp_bind(server_conn, UIP_HTONS(UDP_SERVER_PORT));

	PRINTF("Created a server connection with remote address ");
	PRINT6ADDR(&server_conn->ripaddr);
	PRINTF(" local/remote port %u/%u\n", UIP_HTONS(server_conn->lport),
		UIP_HTONS(server_conn->rport));

	while (1)
	{
		PROCESS_YIELD();
		if (ev == tcpip_event)
		{
			tcpip_handler();
		}
		else
		{
			PRINTF("Some other event");
		}
	}

	PROCESS_END();
}