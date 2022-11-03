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

#endif	/* TEST_H */

