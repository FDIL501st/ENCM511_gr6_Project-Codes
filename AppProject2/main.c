//// CONFIGURATION BITS - PRE-PROCESSOR DIRECTIVES ////

// Code protection 
#pragma config BSS  = OFF // Boot segment code protect disabled
#pragma config BWRP = OFF // Boot sengment flash write protection off
#pragma config GCP  = OFF // general segment code protecion off
#pragma config GWRP = OFF

// CLOCK CONTROL 
#pragma config IESO     = OFF    // 2 Speed Startup disabled
#pragma config FNOSC    = FRC    // Start up CLK = 8 MHz
#pragma config FCKSM    = CSECMD // Clock switching is enabled, clock monitor disabled
#pragma config SOSCSEL  = SOSCLP // Secondary oscillator for Low Power Operation
#pragma config POSCFREQ = MS     // Primary Oscillator/External clk freq betwn 100kHz and 8 MHz. Options: LS, MS, HS
#pragma config OSCIOFNC = ON     // CLKO output disabled on pin 8, use as IO. 
#pragma config POSCMOD  = NONE   // Primary oscillator mode is disabled

// WDT
#pragma config FWDTEN = OFF  // WDT is off, use SWDTEN bit to turn DWT on
#pragma config WINDIS = OFF  // STANDARD WDT/. Applicable if WDT is on
#pragma config FWPSA  = PR32 // WDT is selected uses prescaler of 32
#pragma config WDTPS  = PS4096  // WDT postscler is 4096 if WDT selected
//Combined result is whenever SWDTEN bit is 1, WDT ~4s enabled.


//MCLR/RA5 CONTROL
#pragma config MCLRE = OFF // RA5 pin configured as input, MCLR reset on RA5 diabled

//BOR  - FPOR Register
#pragma config BORV    = V18    // V18 value=1.8V if BOR enabled
#pragma config BOREN   = BOR3  // BOR controlled turned on by hardware
#pragma config PWRTEN  = OFF   // Powerup timer disabled
#pragma config I2C1SEL = PRI   // Default location for SCL1/SDA1 pin

//JTAG FICD Register
#pragma config BKBUG = OFF  // Background Debugger functions disabled
#pragma config ICS   = PGx2 // PGC2 (pin2) & PGD2 (pin3) are used to connect PICKIT3 debugger

// Deep Sleep RTCC WDT
#pragma config DSWDTEN  = OFF      // Deep Sleep WDT is disabled
#pragma config DSBOREN  = OFF      // Deep Sleep BOR is disabled
#pragma config RTCOSC   = LPRC     // RTCC uses LPRC 32kHz for clock
#pragma config DSWDTOSC = LPRC     // DeepSleep WDT uses Lo Power RC clk
#pragma config DSWDTPS  = DSWDTPS7 // DSWDT postscaler set to 32768 


// Include files. 
#include <p24F16KA101.h>
#include "xc.h"
#include "IO.h"
#include "timer.h"
#include "cn_irq.h"
#include "UART2.h"
#include "app.h"
#include "HLVD.h"

extern ONE_SEC;

int main(void) 
{
    if (RCONbits.POR)
    {
        RCONbits.POR = 0;   //clear POR flag
        CLKinit(32); // Initialize the timer clock.
        InitUART2(); // Initialize the UART bus.
        IOinit();    // Initialize RA2, RA4, RB4, and RB8 pins. 
        CNinit();    // Initialize the input change notifications. 
        decideHLVD(3.1);    // set HLVD trip point
    }
    if (RCONbits.BOR)
    {
        RCONbits.BOR = 0;   //clear BOR flag
        // blink all lights for a second to indicate a system restart
        LED7_ON;
        LED8_ON;
        LED9_ON;
        delay_ms(ONE_SEC);
        LED7_OFF;
        LED8_OFF;
        LED9_OFF;
    }
    
    // Run the driver project 
    app2();
    
    // Program never gets here. 
    return 0;
}

