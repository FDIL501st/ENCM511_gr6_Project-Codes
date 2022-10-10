#include "xc.h"
#include "IO.h"


void IOinit()   //Works as intended
{
    // Make ports RA2, RB4 and RA4 digital input
    TRISAbits.TRISA2  = 1;
	AD1PCFG = 0xFFFF; // Turn all analog pins as digital // According to the project document
    // AD1PCFGbits.PCFG4 = 1; // Disable Analog input for RA2.
    
    TRISBbits.TRISB4  = 1;
    TRISAbits.TRISA4  = 1;
    
    // Enable CNPU for pins used as input(pins 7,9,10)
    CNPU2bits.CN30PUE = 1;  //pin 7
    CNPU1bits.CN1PUE  = 1;  //pin 9
    CNPU1bits.CN0PUE  = 1;  //pin 10
    
    // Make port RB8 output
    TRISBbits.TRISB8 = 0;
	
	return;
}

void IOcheck()
{
	//New clock configuration
	NewClk(32);
    
    // read input. If button pressed OR with input variable. 
    while(!PORTAbits.RA2)
	{
		delay_ms(1000); // Delay 1s
		LATBbits.LATB8 = 1; // LED on
	}
    while(!PORTBbits.RB4)
	{
        delay_ms(2000) // Delay 2s
		LATBbits.LATB8 = 1; // LED on
	}
    while(!PORTAbits.RA4)
	{
        delay_ms(3000); // Delay 3s
		LATBbits.LATB8 = 1; // LED on
	}
	while(!PORTAbits.RA2 && !PORTAbits.RB4 &&)
	{
        delay_ms(1); // Delay 1ms
		LATBbits.LATB8 = 1; // LED on
	}
	
	LATBbits.LATB8 = 0; // else led off
	
	return;
}

void NewClk (unsigned int clkval)
{
	char COSCNOSC;
	if (clkval == 8) //8MHZ
	{
		COSCNOSC = 0x70;
	}
	else if (clkval == 500) //500 kHz
	{
		COSCNOSC = 0x76;
	}
	else if (clkval== 32) //32 kHz
	{
		COSCNOSC = 0x75;
	}
	else // default 32 kHz
	{
		COSCNOSC = 0x75;
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

void _T2Interrupt(_attribute_((interrupt, no_auto_psv)))
{
	IFS0bits.T2IF = 0; //Clear timer 2 interrupt flag
	T2CONbits.TON = 0;
	TMR2 = 0;
	// TMR2flag = 1; // global variable created by user
}

void delay_ms(uint16_t time_ms)
{	
	//T2CON Configuration
	T2CONbits.TON = 1;
	T2CONbits.TSIDL = 0;
	T2CONbits.T32 = 0;
	T2CONbits.TCS = 0;
	
	//Timer 2 Interrupt Operation
	
	//Priority level 7
	IPC1bits.T2IP2 = 1;
	IPC1bits.T2IP1 = 1;
	IPC1bits.T2IP0 = 1;
	
	IEC0bits.T2IE = 0;
	
	IFS0bits.T2IF = 0;
	
	//PR2
	
	PR2 = time_ms/(1000 * 0.0000625 * 2) // 0.0000625 = 2/flk, 2 = prescaler	
}