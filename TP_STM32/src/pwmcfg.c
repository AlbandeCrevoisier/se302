/* PWM Configuration file */

#include "hal.h"

void
toggle_leds(void)
{
	palTogglePad(GPIOF, GPIOF_STAT1);
	palTogglePad(GPIOF, GPIOF_STAT2);
	palTogglePad(GPIOF, GPIOF_STAT3);
	palTogglePad(GPIOF, GPIOF_CAM_PWR);
}

void
toggle_led1(void)
{
	palTogglePad(GPIOF, GPIOF_STAT1);
}

void
toggle_led2(void)
{
	palTogglePad(GPIOF, GPIOF_STAT2);
}

void
toggle_led3(void)
{
	palTogglePad(GPIOF, GPIOF_STAT3);
}

void
toggle_led4(void)
{
	palTogglePad(GPIOF, GPIOF_CAM_PWR);
}

/* PWM Config structure */
static const PWMConfig pwmcfg = {
	200000,			/* frequency: 200kHz */
	1024,			/* period */
	(pwmcallback_t) toggle_leds,	/* callback */
	/* Use 4 channels: {mode, callback} */
	{
		{PWM_OUTPUT_ACTIVE_HIGH, (pwmcallback_t) toggle_led1},
		{PWM_OUTPUT_ACTIVE_HIGH, (pwmcallback_t) toggle_led2},
		{PWM_OUTPUT_ACTIVE_HIGH, (pwmcallback_t) toggle_led3},
		{PWM_OUTPUT_ACTIVE_HIGH, (pwmcallback_t) toggle_led4}
	},
	0,
	0
};

void
pwm_init(void)
{
	pwmStart(&PWMD1, &pwmcfg);
	pwmEnablePeriodicNotification(&PWMD1);
}
