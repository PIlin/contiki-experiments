all: client server

APPS=servreg-hack

WITH_UIP6=1
UIP_CONF_IPV6=1

CFLAGS+= -DUIP_CONF_IPV6_RPL


CONTIKI=../../contiki-arduino
include $(CONTIKI)/Makefile.include
