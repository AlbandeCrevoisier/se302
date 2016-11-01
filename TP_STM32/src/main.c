/* Main */

#include <stdio.h>
#include <string.h>

#include "ch.h"
#include "hal.h"

#include "pwmcfg.h"
#include "irq.h"

/* LED blinker thread */

thread_reference_t blinker_thd_p = NULL;

static THD_WORKING_AREA(blinker_thd_wa, 128);
static THD_FUNCTION(blinker_thd, arg) {

	(void) arg;
	chRegSetThreadName("blinker");
	/* low light PWM controlled by wakup button */
	int pwm_wakup = 64;

	while (true) {
		pwmEnableChannel(&PWMD1, 0, 0);
		pwmEnableChannel(&PWMD1, 1, 0);
		pwmEnableChannel(&PWMD1, 2, 0);
		pwmEnableChannel(&PWMD1, 3, 0);
		pwmEnableChannelNotification(&PWMD1, 0);
		pwmEnableChannelNotification(&PWMD1, 1);
		pwmEnableChannelNotification(&PWMD1, 2);
		pwmEnableChannelNotification(&PWMD1, 3);

		pwmEnableChannel(&PWMD1, 0, pwm_wakup);

		chSysLock();
		chThdSuspendS(&blinker_thd_p);
		chSysUnlock();

		pwm_wakup *= pwm_wakup;
		if (pwm_wakup > 1024)
			pwm_wakup = 64;

	}
}

/* Main */
int
main(void)
{
	halInit();
	chSysInit();
	pwm_init();

	nvicEnableVector(RTC_WKUP_IRQn, STM32_EXT_EXTI22_IRQ_PRIORITY);
	chThdCreateStatic(blinker_thd_wa, sizeof(blinker_thd_wa),
		NORMALPRIO, blinker_thd, NULL);

	chThdSleep(TIME_INFINITE);

	return 0;
}
