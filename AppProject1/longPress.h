#ifndef ENCM511_GR6_TIMER23_H
#define	ENCM511_GR6_TIMER23_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "timer.h"

extern uint8_t T2flag;
extern uint8_t inputChangeFlag;

// function to check if press is long or not
uint8_t longPress(uint16_t time_ms);
//REQUIRES: a time in ms that determines 
//  how long to wait before press is considered "long".
//PROMISES:
// Return a 1 if long press is detected, 
//  meaning a timer 2 interrupt occurs.
// Return a 0 if short press is detected, 
//  meaning CN interrupt occurs before timer 2 interrupt.
// If WDT reset occurs, returns a 1 as WDT is ~4s.
// If for some odd reason none of the cases above occurs, return a 1 by default

#endif	/* ENCM511_GR6_TIMER23_H */