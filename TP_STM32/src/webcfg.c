/* lwIP */

#include "ch.h"

#include "lwipthread.h"
#include "lwipopts.h"
#include "lwip/api.h"
#include "lwip/arch.h"

#include "serialusbcfg.h"

THD_WORKING_AREA(web_thd_wa, 2048);
THD_FUNCTION(web_thd, arg)
{
	(void) arg;
	chRegSetThreadName("web");
	
}

void
web_init(void)
{
	ip_addr_t ip, mask, gateway;
	uint8_t mac[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	IP4_ADDR(&ip, 137, 194, 66, 52); /* rose02.enst.fr */
	IP4_ADDR(&mask, 255, 255, 255, 0);
	IP4_ADDR(&gateway, 137, 194, 64, 254);

	const lwipthread_opts_t lwip_opts = {
		mac,
		ip.addr,
		mask.addr,
		gateway.addr
	};
	lwipInit(&lwip_opts);
}
