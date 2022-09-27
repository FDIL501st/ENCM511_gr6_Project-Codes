/*
 * File:   IO.c
 * Author: fdilf
 * All the IO related functions that main.c will be using.
 * This won't include any of the test functions created that change the input.
 * Created on September 21, 2022, 10:02 PM
 */


#include "xc.h"
#include "IO.h"

void IOinit()   //Works as intended
{
    TRISA = TRISA & 0xFFE0; // Sets RA0, RA1, RA2, RA3, RA4 to output
    TRISB = TRISB & 0xFFE8; // Sets RB0, RB1, RB2, RB4 to output
    // Overall, pins 1-9 have been set as output
    
    TRISA = TRISA | 0x0040; // Sets RA6 to input
    TRISB = TRISB | 0x0380; // Sets RB7, RB8, RB9 to input
    // Overall, pins 11-14 have been set as input
    
    //Turn on CNPU bits for pins 11-14 as well
    // as in hardware, they are connected to a push button to ground
    CNPU1bits.CN8PUE = 1;
    CNPU2bits.CN21PUE = 1;
    CNPU2bits.CN22PUE = 1;
    CNPU2bits.CN23PUE = 1;
    return;
}

void output_zero()  //Works
{
    // Have all output pins 2-10 output a 0
    // This means RA0, RA1, RB0, RB1, RB2, RA2, RA3, RB4, RA4
    LATA = LATA & 0xFFE0;
    LATB = LATB & 0xFFE8;
    
    return;
}

void output_one()   //Works
{
    // Have only RA0 output a 1.
    // To make sure of this, first reset all outputs to 0, then turn one on.
    
    // If only make RA0 output a 1, then other outputs that are also turned on 
    // from before won't be turned off.
    // Same logic applied to rest of outputs.
    
    output_zero();
    LATAbits.LATA0 = 1;
    
    return;
}
    
void output_two()   //Works
{
    //First reset all the outputs to 0.
    output_zero();
    // Now output a 1 in RA0(pin2) and RA1(pin3)
    LATA = LATA | 0b11;
   
    return;
}

void output_three()   //Works
{
    //First reset all the outputs to 0.
    output_zero();
    // Now output a 1 in RA0(pin2), RA1(pin3), RB0(pin4)
    LATA = LATA | 0b11;
    LATB = LATB | 0b1;
    return;
}

void output_four()   //Works
{
    //First reset all the outputs to 0.
    output_zero();
    // Now output a 1 in RA0(pin2), RA1(pin3), RB0(pin4), RB1(pin5)
    LATA = LATA | 0b11;
    LATB = LATB | 0b11;
    return;
}

void output_five()  //Works
{
    //First reset all the outputs to 0.
    output_zero();
    // Now output a 1 in RA0(pin2), RA1(pin3), RB0(pin4), RB1(pin5), RB2(pin6)
    LATA = LATA | 0b11;
    LATB = LATB | 0b111;
    return;
}

void output_six()   //Works
{
    //First reset all the outputs to 0.
    output_zero();
    // Now output a 1 in RA0(pin2), RA1(pin3), RB0(pin4),
    // RB1(pin5), RB2(pin6), RA2(pin7)
    LATA = LATA | 0b111;
    LATB = LATB | 0b111;
    return;
}

void output_seven() //Works
{
   //First reset all the outputs to 0.
    output_zero();
    // Now output a 1 in RA0(pin2), RA1(pin3), RB0(pin4),
    // RB1(pin5), RB2(pin6), RA2(pin7), RA3(pin8)
    LATA = LATA | 0b1111;
    LATB = LATB | 0b111;
    return; 
}

void output_eight() //Works
{
    //First reset all the outputs to 0.
    output_zero();
    // Now output a 1 in RA0(pin2), RA1(pin3), RB0(pin4),
    // RB1(pin5), RB2(pin6), RA2(pin7), RA3(pin8), RB4(pin9)
    LATA = LATA | 0b1111;
    LATB = LATB | 0b10111;
    return; 
}

void output_nine()  //Works
{
    //First reset all the outputs to 0.
    output_zero();
    // Now output a 1 in RA0(pin2), RA1(pin3), RB0(pin4),
    // RB1(pin5), RB2(pin6), RA2(pin7), RA3(pin8), 
    // RB4(pin9), RA4(pin10)
    LATA = LATA | 0b11111;
    LATB = LATB | 0b10111;
    return; 
}

uint8_t read_input()    //Works
{
    uint8_t input = PORTAbits.RA6;
    input <<= 1;
    //Shift all bits to left one place
    // This keep all current bits most significant,
    // so when add the new bit, that is the least significant
    input += PORTBbits.RB9;
    // Repeat process of shifting all bits to left by 1,
    // then adding next lesser significant bit 
    input <<= 1;
    input += PORTBbits.RB8;
    input <<= 1;
    input += PORTBbits.RB7;
    
    return input;
}

void display_UCID_digit(const uint8_t index)
{   //UCID = 30113409
    switch (index)
        {
        case 0b0001:
            output_three();
            break;
            
        // Can skip case 0b0010 as that results in output zero, 
        // so can leave that to default
            
        case 0b0011:
            output_one();
            break;
            
        case 0b0100:
            output_one();
            break;
        
        case 0b0101:
            output_three();
            break;
        
        case 0b0110:
            output_four();
            break;
        
        // Can skip case 0b0111 as that results in output zero, 
        // so can leave that to default
            
        case 0b1000:
            output_nine();
            break;
            
        default:
            output_zero();
            break;
        }
}