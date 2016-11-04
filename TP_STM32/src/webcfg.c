/* lwIP */

#include "ch.h"

#include "lwipthread.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "lwipopts.h"

#include "serialusbcfg.h"

/* Since I can't find what to include to use lwip types, I'll use int instead,
 * but I need to rewrite some macro.
 */
#define IP4(ip, a, b, c, d) ip = \
	((u32_t)((d) & 0xff) << 24) | \
	((u32_t)((c) & 0xff) << 16) | \
	((u32_t)((b) & 0xff) << 8) | \
	(u32_t)((a) & 0xff)

THD_WORKING_AREA(web_thd_wa, 2048);
THD_FUNCTION(web_thd, arg)
{
	(void) arg;
	chRegSetThreadName("web");
	
}

void
web_init(void)
{
	uint32_t ip, mask, gateway;
	uint8_t mac[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	IP4(ip, 137, 194, 66, 52); /* rose02.enst.fr */
	IP4(mask, 255, 255, 255, 0);
	IP4(gateway, 137, 194, 64, 254);

	const lwipthread_opts_t lwip_opts = {
		mac,
		ip,
		mask,
		gateway
	};
	lwipInit(&lwip_opts);
}
