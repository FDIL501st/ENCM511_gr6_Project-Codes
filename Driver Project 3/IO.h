// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef IO_H
#define	IO_H

#include <xc.h> // include processor files - each processor file is guarded.  

void IOinit();
// PROMISES:
// Set up pins 7,9,10 as input and pin 12 as output.
// Also enables the internal CNPU resistors for pins 7,9,10.
// This is done because inputs are connected to a push button 
//  connected to ground.
// This results in:
// RA2, RB4, RA4 set to input.
// CN30, CN1, CN0 enabled CNPU resistors
// RB8 set to output.

void IOcheck();
/*
* PROMISES:
* Change the clock
* Read the input whithin a while loop, and continue to operate with that input accordingly
*/

void NewClk(unsigned int clkval);
/*
* REQUIRES: A clock value to change into, 8MHz, 500kHz, 32kHz
* PROMISES: Change the the clock frequency to the given clock speed
*/

void _T2Interrupt(_attribute_((interrupt, no_auto_psv)));
/*
*
*/

void delay_ms(uint16_t time_ms);
/*
* REQUIRES: A specific amount of time need to be delayed
* PROMISES: provide a delay of time in ms with the given clock speed
*/
#endif

