#include "xc.h"
#include "driver7.h"
#include "UART2.h"

void driver7()
{
    unsigned int chargeStatus;
    
    decideHLVD(3);  // initialize HLVD trip point to be 3V
    while (1)
    {
        // 1. enable HLVD as the ISR turns it off
        HLVDCONbits.HLVDEN = 1;
        
        // 2. Check HLVD flag so can know if over-charge or not
        if (HLVDflag)
        {
            chargeStatus = 1;   //indicate over-charge
        }
        else
        {
            chargeStatus = 0; // indicate normal charge
        }
        
        // 3. Send correct number to indicate what was found from HLVDflag
        Disp2Dec(chargeStatus);
        
        // 4. delay for 1000ms before next transmit
        //  This lets us check battery at ~1000ms time interval
        delay_ms(1000);
    }
}