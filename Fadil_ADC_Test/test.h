#ifndef TEST_H
#define	TEST_H

#include "xc.h"
#include "ADC.h"
#include "UART2.h"

extern uint16_t sample_voltage;

void test();
// tests if ADC module works.
// does so by sampling RA3/AN5 (pin8) and 
//displays the converted signal into a terminal
// via sending it through UART-USB

void displayBarPercent(uint16_t voltage);
//REQUIRES:
// voltage to be a number part of the set [0, 1023]
//PROMISES:
// Displays onto the terminal the number of boxes as the number of percent.
// Percent calculated out of 1023.
// Each box on terminal = 1%.
// Any decimal values gets rounded down.

void displayBar16Box(uint16_t voltage);
//REQUIRES:
// voltage to be a number part of the set [0, 1023]
//PROMISES:
// Displays onto the terminal a bar, with 16 boxes at maximum.
// Each box is worth 64.
// Any voltage between multiples of 64 are rounded down to lower multiple of 64.

#endif	/* TEST_H */

