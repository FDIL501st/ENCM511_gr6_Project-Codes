#ifndef CN_INTERRUPTS_H
#define CN_INTERRUPTS_H

#include <xc.h> // include processor files - each processor file is guarded.  
extern uint8_t inputChanged; 

void CNinit();
// REQUIRES: RA2, RA4, RB4 to be set as input.
// PROMISES: initializtion of ports CN30, CN0, CN1.
// Then configures CN interrtupt settings.

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void);
// REQUIRES: CNinit() to have already been called as it sets the CN interrupts.
// PROMISES: When change in input is detected: 
// 1. clears CN interrupt flag
// 2. sets the user defined global flag inputChanged

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

