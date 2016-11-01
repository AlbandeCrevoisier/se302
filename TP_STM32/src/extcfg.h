/* EXT Driver configuration file */
#ifndef EXTCFG_H
#define EXTCFG_H

#include "hal.h"

void ext_init(void);
extern int pwm_wakup; /* Low light LED PWM */
extern thread_reference_t trp;

#endif /* EXTCFG_H */
