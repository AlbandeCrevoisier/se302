/* ADC Configuration file */

#include "ch.h"
#include "hal.h"
#include "adccfg.h"

#define ADC_NUM_CHAN 1
#define ADC_BUF_DEPTH 2

int trim = 0;
static adcsample_t samples[ADC_NUM_CHAN * ADC_BUF_DEPTH];

void
adc_cb(ADCDriver *adcp, adcsample_t *buffer, size_t n)
{
	(void) adcp;
	(void) n;

	trim = buffer[0];

	chSysLockFromISR();
	chThdResumeI(&trp, (msg_t)0x1337);
	chSysUnlockFromISR();
}

static const ADCConversionGroup adc_cg = {
	TRUE,
	ADC_NUM_CHAN,
	adc_cb,
	NULL, /* error callback */
	0, /* CR1 */
	ADC_CR2_SWSTART,
	ADC_SMPR1_SMP_AN10(ADC_SAMPLE_84),
	0, /* SMPR2 */
	0, /* SQR1 */
	0,/* SQR2 */
	ADC_SQR3_SQ1_N(ADC_CHANNEL_IN10)
};

void
adc_init(void)
{
	palSetPadMode(GPIOC, GPIOC_TRIM, PAL_MODE_INPUT_ANALOG);
	adcStart(&ADCD1, NULL);
	adcStartConversion(&ADCD1,&adc_cg, samples, ADC_BUF_DEPTH);
}
