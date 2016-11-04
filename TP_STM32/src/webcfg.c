/* lwIP */

#include "ch.h"

#include "lwipthread.h"
#include "lwipopts.h"
#include "lwip/api.h"
#include "lwip/arch.h"

#include "serialusbcfg.h"

#define ser_usb (BaseSequentialStream *)&SDU1

THD_WORKING_AREA(web_thd_wa, 2048);
THD_FUNCTION(web_thd, arg)
{
	(void) arg;
	chRegSetThreadName("web");

	struct netconn *conn;
	struct netbuf *inbuf;
	char *buf;
	u16_t buflen;
	const char http_get[] =
		"GET / HTTP/1.0\r\nHost: www.telecom-paristech.fr\r\n\r\n";
	ip_addr_t tpt_ip;
	err_t err;

	conn = netconn_new(NETCONN_TCP);
	IP4_ADDR(&tpt_ip, 137, 194, 52, 7);

	err = netconn_connect(conn, &tpt_ip, 80);
	chprintf(ser_usb, "%d\r\n", err);
	err = netconn_write(conn, http_get, sizeof(http_get), NETCONN_NOCOPY);
	chprintf(ser_usb, "%d\r\n", err);

	while (netconn_recv(conn, &inbuf) == ERR_OK) {
		err = netbuf_data(inbuf, (void **) &buf, &buflen);
		chprintf(ser_usb, buf);
		netbuf_free(inbuf);
		netbuf_delete(inbuf);
	}
	chprintf(ser_usb, "%d\r\n", err);
	netbuf_delete(inbuf);

	err = netconn_close(conn);
	chprintf(ser_usb, "%d\r\n", err);
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
	chThdCreateStatic(
		web_thd_wa, sizeof(web_thd_wa), NORMALPRIO + 1, web_thd, NULL);
}
