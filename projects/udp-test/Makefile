all: client server broadcast_pinger

APPS=servreg-hack

#WITH_UIP6=1
#UIP_CONF_IPV6=1
#CFLAGS+= -DUIP_CONF_IPV6_RPL


# CFLAGS += -DNETSTACK_CONF_MAC=nullmac_driver
#CFLAGS += -DNETSTACK_CONF_MAC=csma_driver


# CFLAGS += -DNETSTACK_CONF_RDC=nullrdc_driver
#CFLAGS += -DNETSTACK_CONF_RDC=contikimac_driver

CONTIKI=../../contiki-arduino

CFLAGS += -DPROJECT_CONF_H=\"project-conf.h\"


include $(CONTIKI)/Makefile.include
