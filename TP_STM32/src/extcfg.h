/* EXT Driver configuration file */
#ifndef EXTCFG_H
#define EXTCFG_H

#include "hal.h"

extern int pwm_wakup;
extern int pwm_tamper;
extern thread_reference_t trp;

void ext_init(void);

#endif /* EXTCFG_H */
