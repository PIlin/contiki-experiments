

#include "mrf24j40.h"

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


static int mrf24j40_init(void)
{
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
	return 0;
}

static int mrf24j40_read(void *buf, unsigned short buf_len)
{
	return 0;
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
	process_poll(&mrf24j40_process);
}

ISR(MRF24J40_INTERRUPT)
{
	mrf24j40_interrupt();
}


PROCESS_THREAD(mrf24j40_process, ev, data)
{
	PROCESS_BEGIN();

	while (1)
	{
		PROCESS_YIELD_UNTIL(PROCESS_EVENT_POLL == ev);
	}

	PROCESS_END();
}