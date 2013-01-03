#ifndef PROJECT_CONF_H____
#define PROJECT_CONF_H____

#define CONTIKI_CONF_H


#undef  NETSTACK_CONF_MAC
#define NETSTACK_CONF_MAC     csma_driver
//#define NETSTACK_CONF_MAC     nullmac_driver


#undef  NETSTACK_CONF_RDC
#define NETSTACK_CONF_RDC     contikimac_driver
// #define NETSTACK_CONF_RDC     nullrdc_driver



#endif // PROJECT_CONF_H____