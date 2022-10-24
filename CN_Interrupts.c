/*
 * File:   CN_Interrupts.c
 * Author: fdilf
 *
 * Created on October 24, 2022, 8:46 AM
 */


#include "xc.h"
#include "CN_Interrupts.h"

void CNinit()
{
    //Configure CN on RA2
    CNEN2bits.CN30IE = 1; // Enable CN30
    
    //Configure CN on RA4
    CNEN1bits.CN0IE = 1; // Enable CN0
    
    //Configure CN on RB4
    CNEN1bits.CN1IE = 1; // Enable CN1
    
    //Configure CN Interrupts
    IPC4bits.CNIP = 6;  //Second highest priority level 
                        // when detecting change of input
    
    IFS1bits.CNIF = 0;  //Clear CN interrupt flag
    
    IEC1bits.CNIE = 1;  //Enable CN interrupts
    
}

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void)
{
    IFS1bits.CNIF = 0;  //Clear CN interrupt flag
    
    inputChanged = 1;   //sets inputChanged flag
    // This allows rest of programs to know that the input has changed
}
