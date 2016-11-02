/* Main */

#include <stdio.h>
#include <string.h>

#include "ch.h"
#include "hal.h"

#include "pwmcfg.h"
#include "extcfg.h"
#include "adccfg.h"

/* LED blinker thread */
thread_reference_t trp = NULL;
static THD_WORKING_AREA(blinker_thd_wa, 128);
static THD_FUNCTION(blinker_thd, arg) {

	(void) arg;
	chRegSetThreadName("blinker");

	pwmEnableChannel(&PWMD1, 0, 0);
	pwmEnableChannel(&PWMD1, 1, 0);
	pwmEnableChannel(&PWMD1, 2, 0);
	pwmEnableChannel(&PWMD1, 3, 0);
	pwmEnableChannelNotification(&PWMD1, 0);
	pwmEnableChannelNotification(&PWMD1, 1);
	pwmEnableChannelNotification(&PWMD1, 2);
	pwmEnableChannelNotification(&PWMD1, 3);

	while (true) {
		pwmEnableChannel(&PWMD1, 0, pwm_wakup);
		pwmEnableChannel(&PWMD1, 1, pwm_tamper);
		/* 12 bit trimmer resolution */
		pwmEnableChannel(&PWMD1, 2,
			PWM_PERCENTAGE_TO_WIDTH(&PWMD1, trim * 100 / 4096));

		chSysLock();
		chThdSuspendS(&trp);
		chSysUnlock();
	}
}

/* Main */
int
main(void)
{
	halInit();
	chSysInit();
	pwm_init();
	ext_init();
	adc_init();

	chThdCreateStatic(blinker_thd_wa, sizeof(blinker_thd_wa),
		NORMALPRIO, blinker_thd, NULL);

	chThdSleep(TIME_INFINITE);

	return 0;
}
