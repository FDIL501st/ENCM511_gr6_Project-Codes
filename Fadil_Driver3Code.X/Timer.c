#include "timer.h"

//clkval 8 for 8MHz;
//clkval = 500 for 500kHz:
//clkval = 32 for 32kHz;
uint8_t T2flag;

void NewClk (unsigned int clkval)
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
	else if (clkval== 32) //32 kHz
	{
		COSCNOSC = 0x55;
	}
	else // default 32 kHz
	{
		COSCNOSC = 0x55;
	}
	
	// Switch clock to 31 kHz
	SRbits.IPL = 7; //disable interrupts
	CLKDIVbits.RCDIV = 0; // CLK division = 0
	__builtin_write_OSCCONH(COSCNOSC);
	__builtin_write_OSCCONL(0x01) ;
	OSCCONbits.OSWEN = 1;
	while(OSCCONbits.OSWEN == 1)
	{}
	SRbits.IPL = 0; //enable interrupts
}

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void)
{
	IFS0bits.T2IF = 0; //Clear timer 2 interrupt flag
	T2CONbits.TON = 0; // Stops T2 clock
	TMR2 = 0;   // reset T2 counter to 0
}

void delay_ms(uint16_t time_ms)
{
	//New clock configuration
	NewClk(32);
	
	//T2CON Configuration
	T2CONbits.TON = 1;
	T2CONbits.TSIDL = 0;
	T2CONbits.T32 = 0;
	T2CONbits.TCS = 0;
	
	//Timer 2 Interrupt Operation
	
	//Priority level 7
	IPC1bits.T2IP2 = 1;
	IPC1bits.T2IP1 = 1;
	IPC1bits.T2IP0 = 1; // T2 priority lvl highest so it won't get interrupted
	
	IEC0bits.T2IE = 1;  //enable T2 interrupts
	
	IFS0bits.T2IF = 0;  //clear T2 interrupt flag
	
	//PR2
	
	PR2 = time_ms/(1000 * 0.0000625 * 1); 
    // time_ms = required delay in ms, 0.0000625 = 2/32kHz, 1 = prescaler
    // With 32kHz clock, will result in a whole number PR2 that can fit
    // 32 bit clock but not 16 bit clock for 3s. 1s and 2s also fit.

    return;
}