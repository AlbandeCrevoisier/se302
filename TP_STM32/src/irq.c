/* Interrupt handler */

/* Wakup button interrupt handler */
CH_IRQ_HANDLER(RTC_WKUP_IRQHandler)
{
	CH_IRQ_PROLOGUE();

	chSysLockFromISR();
	chThdResumeI(&wakup_thd_p, (msg_t) 0x42);
	chSysUnlockFromISR();

	CH_IRQ_EPILOGUE();
}
