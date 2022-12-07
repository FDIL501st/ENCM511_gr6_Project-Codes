#ifndef DRIVER7_H
#define	DRIVER7_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "HLVD.h"
#include "timer.h"


extern uint8_t HLVDflag;

void driver7();
// PROMISES: The main loop of the driver project.
// Every 1000ms, will transmit to UART current status of the battery charge.
// Transmit a 1 if over-supply of voltage detected(>3V). 
// Transmit a 0 otherwise.

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

