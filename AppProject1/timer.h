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
#include <p24F16KA101.h>

extern uint8_t T2flag;  //flag if T2 interrupt occured

// Timer clock frequency init function. 
void CLKinit(unsigned int clkval);

// Timer 2 interrupt subroutine
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void);

// Delay function. 
void delay_ms(uint16_t time_ms);

#endif	/* ENCM511_GROUP6_TIMER_H */

