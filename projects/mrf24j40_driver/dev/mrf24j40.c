

#include "mrf24j40.h"
#include "mrf24j40_constants.h"


#include "lib/assert.h"
#include "sys/clock.h"

#include "net/packetbuf.h"
#include "net/netstack.h"

#define RXFIFO_MAX_SIZE 144
static uint8_t sg_frame[RXFIFO_MAX_SIZE]; // @todo: fix size
static uint8_t sg_frame_len;
static uint8_t sg_frame_lqi;
static uint8_t sg_frame_rssi;

static volatile uint8_t sg_last_interrupt;


static void write_srg(uint8_t address, uint8_t data)
{
	assert(0x0 <= address && address <= 0x3f);
	assert(0 && "NI");
}

static void write_lrg(uint16_t address, uint8_t data)
{
	assert(0x200 <= address && address <= 0x24C);
	assert(0 && "NI");
}

static uint8_t read_srg(uint8_t address)
{
	assert(0x0 <= address && address <= 0x3f);
	assert(0 && "NI");
	return 0;
}

static uint8_t read_lrg(uint16_t address)
{
	//assert(0x200 <= address && address <= 0x24C);
	assert(0 && "NI");
	return 0;
}

////

static inline void soft_reset(void)
{
	write_srg(MRF_SRG_SOFTRST, 0x7);
}


/**
 * Reset RF state machine
 */
static inline void rf_sm_reset(void)
{
	write_srg(MRF_SRG_RFCTL, 0x04);
	write_srg(MRF_SRG_RFCTL, 0x00);
	clock_delay_usec(192);
}

static inline void set_interrupts(void)
{
    // interrupts for rx and tx normal complete
    // left only normal rx/tx
    write_srg(MRF_SRG_INTCON,
    	TXG1IE |
    	TXG2IE |
    	SECIE |
    	HSYMTMRIE |
    	WAKEIE |
    	SLPIE);
}

static inline void set_channel(uint8_t channel)
{
	uint8_t val = ((channel - 11) << 4) | 0x03;
	write_lrg(MRF_LRG_RFCON0, val);
}

////

// disable receiving packets from air
static inline void rx_disable(void)
{
	write_srg(MRF_SRG_BBREG1, RXDECINV);
}

// enable receiving packets from air
static inline void rx_enalbe(void)
{
	write_srg(MRF_SRG_BBREG1, ~RXDECINV);
}


static inline void get_rxfifo_data(void* buf, uint8_t start, uint8_t len)
{
	uint8_t* pbuf = (uint8_t*)buf;
	while (len--)
	{
		*pbuf = read_lrg(MRF_LRG_RXFIFO + start++);
		++pbuf;
	}
}

static inline void get_rx_frame()
{
	// disable host mcu interrupts

	rx_disable();

	get_rxfifo_data(sg_frame + 0, 0, 1);
	sg_frame_len = sg_frame[0];
	get_rxfifo_data(sg_frame + 1, 1, sg_frame_len + 2);
	sg_frame_lqi = sg_frame[1 + sg_frame_len];
	sg_frame_rssi = sg_frame[1 + sg_frame_len + 1];

	rx_enalbe();

	// enable host mcu interrupts
}

////

static int mrf24j40_init(void);
static int mrf24j40_prepare(const void *payload, unsigned short payload_len);
static int mrf24j40_transmit(unsigned short transmit_len);
static int mrf24j40_send(const void *payload, unsigned short payload_len);
static int mrf24j40_read(void *buf, unsigned short buf_len);
static int mrf24j40_channel_clear(void);
static int mrf24j40_receiving_packet(void);
static int mrf24j40_pending_packet(void);
static int mrf24j40_on(void);
static int mrf24j40_off(void);

PROCESS(mrf24j40_process, "MRF24J40 driver");


const struct radio_driver mrf24j40_driver =
  {
    .init = mrf24j40_init,
    .prepare = mrf24j40_prepare,
    .transmit = mrf24j40_transmit,
    .send = mrf24j40_send,
    .read = mrf24j40_read,
    .channel_clear = mrf24j40_channel_clear,
    .receiving_packet = mrf24j40_receiving_packet,
    .pending_packet = mrf24j40_pending_packet,
    .on = mrf24j40_on,
    .off = mrf24j40_off
  };

///

static int mrf24j40_init(void)
{
	soft_reset();
	write_srg(MRF_SRG_PACON2,   0x98);
	write_srg(MRF_SRG_TXSTBL,   0x95);
	write_lrg(MRF_LRG_RFCON0,   0x03);
	write_lrg(MRF_LRG_RFCON1,   0x01);
	write_lrg(MRF_LRG_RFCON2,   0x80);
	write_lrg(MRF_LRG_RFCON6,   0x90);
	write_lrg(MRF_LRG_RFCON7,   0x80);
	write_lrg(MRF_LRG_RFCON8,   0x10);
	write_lrg(MRF_LRG_SLPCON1,  0x21);

#if 1
	// non-beacon

	write_srg(MRF_SRG_BBREG2,   0x80);
	write_srg(MRF_SRG_CCAEDTH,  0x60);
	write_srg(MRF_SRG_BBREG6,   0x40);

	// @todo: set interrupt edge polarity INTEDGE
	set_interrupts();
	set_channel(12);


	// set tx power
	rf_sm_reset();

#endif

	return 0;
}

static int mrf24j40_prepare(const void *payload, unsigned short payload_len)
{
	return 0;
}

static int mrf24j40_transmit(unsigned short transmit_len)
{
	return 0;
}

static int mrf24j40_send(const void *payload, unsigned short payload_len)
{
	int ret = mrf24j40_prepare(payload, payload_len);
	if (ret)
	{
		return ret;
	}

	return mrf24j40_transmit(payload_len);
}

static int mrf24j40_read(void *buf, unsigned short buf_len)
{
	int ret = 0;
	uint8_t len;
	uint8_t lqi;
	uint8_t rssi;

	get_rxfifo_data(&len, 0, 1);

	if (len > buf_len)
	{
		ret = 0;
		goto read_end;
	}

	/// @todo: another checks

	get_rxfifo_data(buf   , 1           , len);
	get_rxfifo_data(&lqi  , 1 + len     , 1);
	get_rxfifo_data(&rssi , 1 + len + 1 , 1);

	packetbuf_set_attr(PACKETBUF_ATTR_LINK_QUALITY, lqi);
	packetbuf_set_attr(PACKETBUF_ATTR_RSSI, rssi);


	ret = len - 2;

read_end:

	rx_enalbe();

	return ret;
}

static int mrf24j40_channel_clear(void)
{
	return 0;
}

static int mrf24j40_receiving_packet(void)
{
	return 0;
}

static int mrf24j40_pending_packet(void)
{
	return 0;
}

static int mrf24j40_on(void)
{
	return 0;
}

static int mrf24j40_off(void)
{
	return 0;
}

void mrf24j40_interrupt(void)
{
	// will be enabled in mrf24j40_read
	sg_last_interrupt = read_srg(MRF_SRG_INTSTAT);

	if (sg_last_interrupt & RXIF)
	{
		rx_disable();
	}
	/// @todo: process other interrupts



	process_poll(&mrf24j40_process);
}

ISR(MRF24J40_INTERRUPT)
{
	mrf24j40_interrupt();
}


PROCESS_THREAD(mrf24j40_process, ev, data)
{
	int len;
	PROCESS_BEGIN();

	while (1)
	{
		PROCESS_YIELD_UNTIL(PROCESS_EVENT_POLL == ev);

		if (sg_last_interrupt & RXIF)
		{
			packetbuf_clear();
			len = mrf24j40_read(packetbuf_dataptr(), PACKETBUF_SIZE);
			if (len > 0)
			{
				packetbuf_set_datalen(len);
				NETSTACK_RDC.input();
			}
		}


	}

	PROCESS_END();
}
