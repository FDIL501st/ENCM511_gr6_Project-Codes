/*
 * File:   UART1.c
 * Author: fdilf
 *
 * Created on December 7, 2022, 8:55 PM
 */


#include "xc.h"
#include "UART1.h"

char RxChar;

void InitUART1(void) 
{

	//TRISBbits.TRISB0=0; // Set U2TX/RB0/pin 4 as UART TX
	TRISBbits.TRISB1=1; // Set U1RX/RB2/pin 6 as UART RX
	//LATBbits.LATB0=1;

	// configure UART mode i.e Parity, char length etc 
    //U2MODE = 0b1000000000001000;
 
	U1MODEbits.UARTEN = 0;	// Bit15 TX, RX DISABLED, ENABLE at end of func
	U1MODEbits.USIDL = 0;	// Bit13 Continue in Idle
	U1MODEbits.IREN = 0;	// Bit12 No IR translation
	U1MODEbits.RTSMD = 0;	// Bit11 Simplex Mode
	U1MODEbits.UEN = 0;		// Bits8,9 TX,RX enabled, CTS,RTS not
	U1MODEbits.WAKE = 0;	// Bit7 Interrupt not generated on U2RX pin in sleep
	U1MODEbits.LPBACK = 0;	// Bit6 No Loop Back
	U1MODEbits.ABAUD = 0;	// Bit5 No Autobaud (would require sending '55')
	U1MODEbits.RXINV = 0;	// Bit4 IdleState = 1
	U1MODEbits.BRGH = 1;	// Bit3 4 clocks per bit period - Hi speed mode
	U1MODEbits.PDSEL = 0;	// Bits1,2 8bit, No Parity
	U1MODEbits.STSEL = 0;	// Bit0 One Stop Bit

    
    //configure baud rate based on sys clock
	if (OSCCONbits.COSC == 0b110)
	{
		U2BRG = 12;	// gives a baud rate of 4807.7 Baud with 500kHz clock; Set Baud to 4800 on realterm
	}
	else if (OSCCONbits.COSC == 0b101)
	{
		U2BRG = 12;	// gives a baud rate of 300 Baud with 32kHz clock; set Baud to 300 on realterm
	}
	else if (OSCCONbits.COSC == 0b000)
	{
		U2BRG=103;	// gives a baud rate of 9600 with 8MHz clock; set Baud to 9600 on real term
	}
	// Initialize UART Status reg - Tx interrupt control
	U1STA = 0b0010000000000000;
    

//    U2STAbits.UTXISEL1 = 1;	//Bit15 Int when Char is transferred (1/2 config!)
//    U2STAbits.UTXISEL0 = 1;	//Generate interrupt with last character shifted out of U2TXREG buffer
//	U2STAbits.UTXINV = 0;	//Bit14 N/A, IRDA config
//	U2STAbits.UTXBRK = 0;	//Bit11 Disabled
//	U2STAbits.UTXEN = 0;	//Bit10 TX pins controlled by periph
//	U2STAbits.UTXBF = 0;	//Bit9 *Read Only Bit*
//	U2STAbits.TRMT = 0;		//Bit8 *Read Only bit*
//	U2STAbits.URXISEL = 0;	//Bits6,7 Int. on character recieved
//	U2STAbits.ADDEN = 0;	//Bit5 Address Detect Disabled
//	U2STAbits.RIDLE = 0;	//Bit4 *Read Only Bit*
//	U2STAbits.PERR = 0;		//Bit3 *Read Only Bit*
//	U2STAbits.FERR = 0;		//Bit2 *Read Only Bit*
//	U2STAbits.OERR = 0;		//Bit1 *Read Only Bit*
//	U2STAbits.URXDA = 0;	//Bit0 *Read Only Bit*

	
//    //Configure Interrupts (for Tx)
//    IFS1bits.U2TXIF = 0;	// Clear the Transmit Interrupt Flag
//    IPC7bits.U2TXIP = 3;    // UART2 TX interrupt has interrupt priority 3-4th highest priority
//    IEC1bits.U2TXIE = 0;	// Disable Transmit Interrupts
	
    //Configure Interrupts (for Rx)
    IFS0bits.U1RXIF = 0;	// Clear the Recieve Interrupt Flag
	IPC2bits.U1RXIP = 4;    //UART1 Rx interrupt has 2nd highest priority
    IEC0bits.U1RXIE = 1;	// Enable Recieve Interrupts

	U1MODEbits.UARTEN = 1;	// And turn the peripheral on

	U1STAbits.UTXEN = 1;
	return;
}

// Interrupt service routine for UART1 RX
void __attribute__ ((interrupt, no_auto_psv)) _U1RXInterrupt(void) {
	IFS0bits.U1RXIF = 0;    //clear UART1 Rx interrupt flag
    //because interrupt occurs at every char received, can just read the char

    RxChar = U1RXREG;   //read Rx buffer
    // implicit type conversion to char will not effect reading of the 
    //  least 8 significant bits where the char is stored
}
