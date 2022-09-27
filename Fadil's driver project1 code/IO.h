/* 
 * File: IO.h  
 * Author: Fadil Husain
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef IO_H
#define	IO_H

#include <xc.h> // include processor files - each processor file is guarded.  

void IOinit();
//PROMISES:
// Set up pins 2-10 as output and pins 11-14 as input.
// This results in:
// RA0, RA1, RB0, RB1, RB2, RA2, RA3, RB4, RA4 set to output.
// RB7, RB8, RB9, RA6 set to input.

void output_zero();
//PROMISES:
// Make all output pins (2-10) set to 0.
// This results in no LED lights to be turned on.

void output_one();
// PROMISES:
// Make pin 2(RA0) output a 1, rest of the output pins a 0.
// This results in only one LED light to be turned on.

void output_two();
// PROMISES:
// Make pins 2 and 3 output a 1, rest of the output pins a 0.
// This results in two LEDs to be turned on.

void output_three();
// PROMISES:
// Make pins 2,3,4  output a 1, rest of the output pins a 0.
// This results in three LEDs to be turned on.

void output_four();
// PROMISES:
// Make pins 2,3,4,5  output a 1, rest of the output pins a 0.
// This results in four LEDs to be turned on.

void output_five();
// PROMISES:
// Make pins 2,3,4,5,6  output a 1, rest of the output pins a 0.
// This results in five LEDs to be turned on.

void output_six();
// PROMISES:
// Make pins 2,3,4,5,6,7  output a 1, rest of the output pins a 0.
// This results in six LEDs to be turned on.

void output_seven();
// PROMISES:
// Make pins 2,3,4,5,6,7,8  output a 1, rest of the output pins a 0.
// This results in seven LEDs to be turned on.

void output_eight();
// PROMISES:
// Make pins 2,3,4,5,6,7,8,9 output a 1, rest of the output pins a 0.
// This results in eight LEDs to be turned on.

void output_nine();
// PROMISES:
// Make all output pins 2-10 output a 1.
// This results in nine LEDs to be turned on.

uint8_t read_input();
// PROMISES:
// Read 4 bit input from the 4 input pins(11-14).
// Returns the input read.
// Most significant digit is pin 14(RA6), 
// then pin 13(RB9), pin12(RB8), pin11(RB7)

void display_UCID_digit(const uint8_t index);
//PROMISES: 
// Displays the UCID digit depending on the index. 
// UCID is 1-indexed.
// Any index resulting in outside the UCID will turn off all LEDs.
// UCID is 30113409.
// Ex. 0b0001 will result in 3 LEDs to light up.
// 0b0011 will result in 1 LED to light up.
// 0b1000 will result in 9 LEDS to light up.
//REQUIRES:
// 4 bit binary pattern as input.
// Binary pattern treated as unsigned number.

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* IO_H */

