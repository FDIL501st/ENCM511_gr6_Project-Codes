/*
 * File:   IO.c
 * Author: fdilf
 * All the IO related functions that main.c will be using.
 * Created on September 28, 2022, 1:00 PM
 */


#include "xc.h"
#include "IO.h"

void IOinit()   //Works as intended
{
    // Make ports RA2, RB4 and RA4 input
    TRISAbits.TRISA2 = 1;
    TRISBbits.TRISB4 = 1;
    TRISAbits.TRISA4 = 1;
    
    // Enable CNPU for pins used as input(pins 7,9,10)
    CNPU2bits.CN30PUE = 1;  //pin 7
    CNPU1bits.CN1PUE = 1;   //pin 9
    CNPU1bits.CN0PUE = 1;   //pin 10
    
    // Make port RB8 output
    TRISBbits.TRISB8 = 0;
    
    return;
}

uint8_t read_input()    //Works
{
    uint8_t input = PORTAbits.RA2;
    input <<= 1;
    //Shift all bits to left one place
    // This keep all current bits most significant,
    // so when add the new bit, that is the least significant
    input += PORTBbits.RB4;
    // Repeat process of shifting all bits to left by 1,
    // then adding next lesser significant bit 
    input <<= 1;
    input += PORTAbits.RA4;
    
    return input;
}

void LED_off() { LATBbits.LATB8 = 0; }

void LED_on() { LATBbits.LATB8 = 1; }

uint8_t PB1_pressed(uint8_t input)
{
    LED_on();
    /* Somehow stall for ~1s. */
    
    uint8_t newInput = read_input();
    
    if (newInput != input)
        return;
    
    LED_off();
    /* Somehow stall for ~1s. */
    
    return;
}

uint8_t PB2_pressed(uint8_t input)
{
    LED_on();
    /* Somehow stall for ~2s. */
    
    uint8_t newInput = read_input();
    
    if (newInput != input)
        return;
    
    LED_off();
    /* Somehow stall for ~2s. */
    
    return;
}

void PB3_pressed(uint8_t input)
{
    LED_on();
    /* Somehow stall for ~3s. */
    
    uint8_t newInput = read_input();
    
    if (newInput != input)
        return;
    
    LED_off();
    /* Somehow stall for ~3s. */
    
    return;
}

uint8_t choose_output_func(uint8_t input)
{
    switch (input)
    {
        case 011:
            PB1_pressed();
            break;
        
        case 101:
            PB2_pressed();
            break;
            
        case 110:
            PB3_pressed();
            break;
            
        case 111:
            LED_off();
            break;
        
        // rest cases are when more than 1 PB pressed
        default:
            LED_on();
            break;
    }
    return read_input();
}