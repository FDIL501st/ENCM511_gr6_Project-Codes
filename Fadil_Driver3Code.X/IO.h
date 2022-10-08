/* 
 * File: IO.h  
 * Author: Fadil Husain
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef DRIVER_PROJECT_2_IO_H
#define	DRIVER_PROJECT_2_IO_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "timer.h"

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

uint8_t read_input();
// PROMISES:
// Read 3 bit input from the 3 input ports, RA2, RB4, RA4.
// Returns the input read.
// Most significant digit is pin 7(RA2), 
// then pin 9(RB4), pin 10(RA4)

void LED_off();
// PROMISES: To turn off LED connected to RB8.
//  So, have RB8 output a 0.

void LED_on();
// PROMISES: To turn on LED connected to RB8.
//  So, have RB8 output a 1.

void PB1_pressed(uint8_t input);
// REQUIRES: The current input (3 digit binary pattern)
// PROMISES: Have LED on for ~1s and then off ~1s.
//  During the 1s that the LED is on or off for,
//      repeatedly checks for change of input on breadboard.
//  If detected, will stop function.

void PB2_pressed(uint8_t input);
// REQUIRES: The current input (3 digit binary pattern)
// PROMISES: Have LED on for ~2s and then off ~2s.
//  During the 1s that the LED is on or off for,
//      repeatedly checks for change of input on breadboard.
//  If detected, will stop function.

void PB3_pressed(uint8_t input);
// REQUIRES: The current input (3 digit binary pattern)
// PROMISES: Have LED on for ~3s and then off ~3s.
//  During the 1s that the LED is on or off for,
//      repeatedly checks for change of input on breadboard.
//  If detected, will stop function.

uint8_t choose_output_func(uint8_t input);
// REQUIRES: The current input (3 digit binary pattern)
// PROMSIES: Use input to choose the output function wanted.
//  Then read input and return it (the most up to date input)
#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* IO_H */

