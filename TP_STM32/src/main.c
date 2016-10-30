/* Main */

#include <stdio.h>
#include <string.h>

#include "ch.h"
#include "hal.h"

#include "pwmcfg.h"
#include "irq.h"

/* Wakup button thread */
int pwm_wakup = 0;
static thread_reference_t wakup_thd_p = NULL;

static THD_WORKING_AREA(wa_wakup_thd, 128);
static THD_FUNCTION(wakup_thd, arg)
{
	(void) arg;
	chRegSetThreadName("wakup Neo");
	/* low light PWM */
	pwm_wakup = 64;
	while (true) {
		chSysLock();
		chThdSuspendS(&wakup_thd_p);
		chSysUnlock();

		pwm_wakup *= pwm_wakup;
		if (pwm_wakup > 1024)
			pwm_wakup = 64;
		
	}
}

/* LED blinker thread */
static THD_WORKING_AREA(blinker_thd_wa, 128);
static THD_FUNCTION(blinker_thd, arg) {

	(void) arg;
	chRegSetThreadName("blinker");
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
		chThdSleepMilliseconds( 200);
		pwmEnableChannel(&PWMD1, 1, 256);
		chThdSleepMilliseconds( 200);
		pwmEnableChannel(&PWMD1, 2, 256);
		pwmEnableChannel(&PWMD1, 0, 0);
		chThdSleepMilliseconds( 200);
		pwmEnableChannel(&PWMD1, 3, 256);
		pwmEnableChannel(&PWMD1, 1, 0);
		chThdSleepMilliseconds( 200);
		pwmEnableChannel(&PWMD1, 2, 0);
		chThdSleepMilliseconds( 200);
		pwmEnableChannel(&PWMD1, 3, 0);
	}
}

/* Main */
int
main(void)
{
	halInit();
	chSysInit();
	pwm_init();

	chThdCreateStatic(blinker_thd_wa, sizeof(blinker_thd_wa),
		NORMALPRIO, blinker_thd, NULL);

	nvicEnableVector(RTC_WKUP_IRQn, NVIC_PRIORITY_MASK(1));
	chThdCreateStatic(wa_wakup_thd, sizeof(wa_wakup_thd),
		NORMALPRIO, wakup_thd, NULL);

	while (true)
		chThdSleepMilliseconds(500);

	return 0;
}
