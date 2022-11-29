/*
 * File:   CN_Interrupts.c
 * Author: fdilf
 *
 * Created on October 24, 2022, 8:46 AM
 */

#include "xc.h"
#include "cn_irq.h"

uint8_t inputChangeFlag = 0;

void CNinit()
{
    //Configure CN on RA2
    CNEN2bits.CN30IE = 1; // Enable CN30
    
    //Configure CN on RA4
    CNEN1bits.CN0IE = 1; // Enable CN0
    
    //Configure CN on RB4
    CNEN1bits.CN1IE = 1; // Enable CN1
    
    //Configure CN Interrupts
    IPC4bits.CNIP = 6;  // Highest priority level 
                        // when detecting change of input
    
    IFS1bits.CNIF = 0;  // Clear CN interrupt flag
    
    IEC1bits.CNIE = 1;  // Enable CN interrupts
    
}

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void)
{
    inputChangeFlag = 1;   // Sets inputChanged_Flag
    delay_ms(250); // Delay for 10ms to filter out debounce.
    //To trigger the timer interrupt above, 
    // T2 interrupt must have higher priority than CN interrupt
    T2flag = 0;     // clear T2flag
    IFS1bits.CNIF   = 0;   // Clear CN interrupt flag
    // This allows rest of programs to know that the input has changed
}
