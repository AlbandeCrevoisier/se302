/* Serial over USB configuration file */

#include "hal.h"
#include "usbcfg.h"

void
serial_usb_init(void)
{
	/* Serial over USB cDc driver */
	sduObjectInit(&SDU1);
	sduStart(&SDU1, &serusbcfg);
	/* USB */
	usbDisconnectBus(serusbcfg.usbp);
	chThdSleepMilliseconds(1500);
	usbStart(serusbcfg.usbp, &usbcfg);
	usbConnectBus(serusbcfg.usbp);
}
