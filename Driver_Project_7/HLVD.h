#ifndef DRIVER_PROJECT_2_HLVD_H
#define	DRIVER_PROJECT_2_HLVD_H

//user-defined flag
extern uint8_t HLVDflag;

// HLVD Setup
void HLVDinit(unsigned int hlvd);

// HLVD Interrupt
void __attribute__ ((interrupt,no_auto_psv)) _HLVDInterrupt(void);

// HLVD trip point decider
void decideHLVD(float voltageValue);

#endif