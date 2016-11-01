/* Interrupt handler */

#include "irq.h"

extern thread_reference_t blinker_thd_p;

/* Wakup button interrupt handler */
CH_IRQ_HANDLER(RTC_WKUP_IRQHandler)
{
	CH_IRQ_PROLOGUE();

	chSysLockFromISR();
	chThdResumeI(&blinker_thd_p, (msg_t) 0x42);
	chSysUnlockFromISR();

	CH_IRQ_EPILOGUE();
}
