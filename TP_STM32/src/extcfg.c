/* EXT Driver configuration file */

#include "hal.h"
#include "extcfg.h"

int pwm_wakup = 64; /* Low light LED PWM */
int pwm_tamper = 64; /* Low light LED PWM */

void
ext_wkup_cb(EXTDriver *extp, expchannel_t channel)
{
	(void) extp;
	(void) channel;
	static systime_t before = 0;
	systime_t now = chVTGetSystemTimeX();

	if (before != 0 && now - before < 1337)
		return;

	pwm_wakup *= 2;
	if (pwm_wakup > 1024)
		pwm_wakup = 64;

	chSysLockFromISR();
	chThdResumeI(&trp, (msg_t)0x1337);
	chSysUnlockFromISR();

	now = chVTGetSystemTimeX();
}

void
ext_tamper_cb(EXTDriver *extp, expchannel_t channel)
{
	(void) extp;
	(void) channel;
	static systime_t before = 0;
	systime_t now = chVTGetSystemTimeX();

	if (before != 0 && now - before < 1337)
		return;

	pwm_tamper *= 2;
	if (pwm_tamper > 1024)
		pwm_tamper = 64;

	chSysLockFromISR();
	chThdResumeI(&trp, (msg_t)0x1337);
	chSysUnlockFromISR();

	now = chVTGetSystemTimeX();
}

static const EXTConfig extcfg = {
	{
	/* Channel Config: {mode, callback} */
		{EXT_CH_MODE_RISING_EDGE | \
			EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOA, ext_wkup_cb},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_RISING_EDGE | \
			EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOC, ext_tamper_cb},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL}
	}
};

void
ext_init(void)
{
	extStart(&EXTD1, &extcfg);
}
