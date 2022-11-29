// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef DRIVER_PROJECT_2_IO_H
#define	DRIVER_PROJECT_2_IO_H

#include <xc.h>  // include processor files - each processor file is guarded.  

// LED control macros. 
#define LED_OFF      LATBbits.LATB8 = 0 
#define LED_ON       LATBbits.LATB8 = 1 
#define LED_SWITCH   LATBbits.LATB8 = ~LATBbits.LATB8;

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

