#ifndef ENCM511_GR6_ADC_H
#define	ENCM511_GR6_ADC_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define Idle() {__asm__ volatile ("pwrsav #1");}

extern uint8_t ADCflag; //user defined ADC flag

void ADC_init();
//PROMISES:
// Initialize value of registers AD1CON1, AD1CON2, AD1CON3.
// Select AN5 as the analog input.
// Set AN5 as an analog port, rest set to digital
// Configured ADC conversion completion interrupt routine
// The interrupt priority is set to 5.

uint16_t do_ADC(void);
//PROMISES:
// Samples an analog signal detected from AN5(pin8) and 
//return the digital 16 bit number of said sample.
// Returns 0 if no analog signal was sampled.

void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void);
//PROMISES:
// Clears the microcontroller ADC1 flag.
// Sets the user defined ADC flag.

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

