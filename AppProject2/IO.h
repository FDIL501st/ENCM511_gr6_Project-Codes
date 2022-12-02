// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef DRIVER_PROJECT_2_IO_H
#define	DRIVER_PROJECT_2_IO_H

#include <xc.h>  // include processor files - each processor file is guarded.  

// LED control macros. 
#define LED7_OFF      LATBbits.LATB7 = 0
#define LED7_ON       LATBbits.LATB7 = 1
#define LED7_SWITCH   LATBbits.LATB7 = ~LATBbits.LATB7

#define LED8_OFF      LATBbits.LATB8 = 0 
#define LED8_ON       LATBbits.LATB8 = 1 
#define LED8_SWITCH   LATBbits.LATB8 = ~LATBbits.LATB8

#define LED9_OFF      LATBbits.LATB9 = 0
#define LED9_ON       LATBbits.LATB9 = 1
#define LED9_SWITCH   LATBbits.LATB9 = ~LATBbits.LATB9

void IOinit();
// PROMISES:
// Set up pins 7,9,10 as input and pin 11,12,13 as output.
// Also enables the internal CNPU resistors for pins 7,9,10.
// This is done because inputs are connected to a push button 
//  connected to ground.
// This results in:
// RA2, RB4, RA4 set to input.
// CN30, CN1, CN0 enabled CNPU resistors
// RB7,RB8,RB9 set to output.


#endif	/* IO_H */

