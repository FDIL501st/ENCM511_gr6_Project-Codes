#include "timer.h"

//clkval 8 for 8MHz;
//clkval = 500 for 500kHz:
//clkval = 32 for 32kHz;

void CLKinit(unsigned int clkval) //Works
{
	char COSCNOSC;
	if (clkval == 8) //8MHZ
	{
		COSCNOSC = 0x00;
	}
	else if (clkval == 500) //500 kHz
	{
		COSCNOSC = 0x66;
	}
	else if (clkval== 32)   //32 kHz
	{
		COSCNOSC = 0x55;
	}
	else                    // default 32 kHz
	{
		COSCNOSC = 0x55;
	}
	
	// Switch clock to 31 kHz
	SRbits.IPL = 7;                 //disable interrupts
	CLKDIVbits.RCDIV = 0;           // CLK division = 0
	__builtin_write_OSCCONH(COSCNOSC);
	__builtin_write_OSCCONL(0x01) ;
	OSCCONbits.OSWEN = 1;
    while(OSCCONbits.OSWEN == 1){}
	SRbits.IPL = 0; //enable interrupts
}

uint8_t T2flag = 0;

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void) //works
{
	IFS0bits.T2IF = 0; // Clear timer 2 interrupt flag.
	T2CONbits.TON = 0; // Stops T2 clock.
    T2flag = 1; //Sets T2flag 
}

void delay_ms(uint16_t time_ms) //works
{
	TMR2   = 0;          // Clear timer accumulator.
	//T2CON Configuration
    T2CONbits.T32   = 0; // Set to 16-bit mode.
	T2CONbits.TSIDL = 0; // Set to continue operation when in idle mode.
	T2CONbits.TCS   = 0; // Clk src is internal.
	
	//Timer 2 Interrupt Operation
	
	//Priority level 7
	IPC1bits.T2IP  = 7;   
	IEC0bits.T2IE  = 1;  // enable T2 interrupts
	IFS0bits.T2IF  = 0;  // clear T2 interrupt flag
	
    
	//PR2
	PR2 = (time_ms)/(1000 * 0.0000625 * 1); 
    // time_ms = required delay in ms, 0.0000625 = 2/32kHz, 1 = prescaler
    // With 32kHz clock, will result in a whole number PR2 that can fit
    // 32 bit clock but not 16 bit clock for 3s. 1s and 2s also fit.
    
    T2CONbits.TON   = 1;

    Idle(); // Put the system in idle mode until an interrupt is satisfied.    
}
