#ifndef CN_INTERRUPTS_H
#define CN_INTERRUPTS_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "timer.h"

extern uint8_t inputChangeFlag; 
extern uint8_t T2flag;

void CNinit();
// REQUIRES: RA2, RA4, RB4 to be set as input.
// PROMISES: initializtion of ports CN30, CN0, CN1.
// Then configures CN interrtupt settings.

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void);
// REQUIRES: CNinit() to have already been called as it sets the CN interrupts.
// PROMISES: When change in input is detected: 
// 1. clears CN interrupt flag
// 2. sets the user defined global flag inputChanged

#endif	/* XC_HEADER_TEMPLATE_H */
