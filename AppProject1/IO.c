#include "IO.h"

void IOinit()   //Works as intended
{
    // Make ports RA2, RB4 and RA4 digital input
    AD1PCFGbits.PCFG4 = 1; // Disable Analog input for RA2.
    
	TRISAbits.TRISA2  = 1; // Make port RA2 Input
    TRISAbits.TRISA4  = 1; // Make port RA4 Input
    TRISBbits.TRISB4  = 1; // Make port RB4 Input
    TRISBbits.TRISB8  = 0; // Make port RB8 output
    
    // Enable CNPU for pins used as input(pins 7,9,10)
    CNPU2bits.CN30PUE = 1;  // pin 7
    CNPU1bits.CN1PUE  = 1;  // pin 9
    CNPU1bits.CN0PUE  = 1;  // pin 10
}

