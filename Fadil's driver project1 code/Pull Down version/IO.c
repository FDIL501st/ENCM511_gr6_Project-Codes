/*
 * File:   IO.c
 * Author: fdilf
 * All the IO related functions that main.c will be using.
 * Created on September 28, 2022, 1:00 PM
 */


#include <p24F16KA101.h>

#include "xc.h"
#include "IO.h"

void IOinit()   //Works as intended
{
    // Make ports RA2, RB4 and RA4 input
    TRISAbits.TRISA2 = 1;
    TRISBbits.TRISB4 = 1;
    TRISAbits.TRISA4 = 1;
    
    // Enable CNPU for pins used as input(pins 7,9,10)
    CNPD2bits.CN30PDE = 1;  //pin 7
    CNPD1bits.CN1PDE = 1;   //pin 9
    CNPD1bits.CN0PDE = 1;   //pin 10
    
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

void PB1_pressed(uint8_t input)
{
    uint8_t newInput = 0;
    uint32_t counter = 120000;
    
    LED_on();
    /* stall for ~1s by repeatedly checking for change in input. */
    while (counter != 0)
    {
        newInput = read_input();
    
        if (newInput != input)
            return;
        
        counter--;
    }
    
    LED_off();
    /* stall for ~1s by repeatedly checking for change in input. */
    counter = 120000;   // Reset counter
    while (counter != 0)
    {
        newInput = read_input();
    
        if (newInput != input)
            return;
        
        counter--;
    }
    
    return;
}

void PB2_pressed(uint8_t input)
{
    uint8_t newInput = 0;
    uint32_t counter = 240000;
    
    LED_on();
    /* stall for ~2s by repeatedly checking for change in input. */
    while (counter != 0)
    {
        newInput = read_input();
    
        if (newInput != input)
            return;
        
        counter--;
    }
    
    LED_off();
    /* stall for ~2s by repeatedly checking for change in input. */
    counter = 240000;   // Reset counter
    while (counter != 0)
    {
        newInput = read_input();
    
        if (newInput != input)
            return;
        
        counter--;
    }
    
    return;
}

void PB3_pressed(uint8_t input)
{
    uint8_t newInput = 0;
    uint32_t counter = 360000;
    
    LED_on();
    /* stall for ~3s by repeatedly checking for change in input. */
    while (counter != 0)
    {
        newInput = read_input();
    
        if (newInput != input)
            return;
        
        counter--;
    }
    
    LED_off();
    /* stall for ~3s by repeatedly checking for change in input. */
    counter = 360000;   // Reset counter
    while (counter != 0)
    {
        newInput = read_input();
    
        if (newInput != input)
            return;
        
        counter--;
    }
    
    return;
}

uint8_t choose_output_func(uint8_t input)
{
    switch (input)
    {
        case 0b100:
            PB1_pressed(input);
            break;
        
        case 0b010:
            PB2_pressed(input);
            break;
            
        case 0b001:
            PB3_pressed(input);
            break;
            
        case 0b000:
            LED_off();
            break;
        
        // rest cases are when more than 1 PB pressed
        default:
            LED_on();
            break;
    }
    return read_input();
}