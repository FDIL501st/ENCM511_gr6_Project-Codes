/* 
 * File: timer.h
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef ENCM511_GROUP6_TIMER_H
#define	ENCM511_GROUP6_TIMER_H

#include <xc.h> // include processor files - each processor file is guarded.  

void NewClk (unsigned int clkval);

void _attribute_((interrupt, no_auto_psv))_T2Interrupt(void);

void delay_ms(uint16_t time_ms);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* ENCM511_GROUP6_TIMER_H */

