#include "app.h"

#if 0
char* allpbs = "All PBs pressed\r\n";         // 8 bits * 4clkpbit * 17
char* nopbs =  "No PBs pressed\r\n";          // 8 bits * 4clkpbit * 16
char* pb1_pressed = "PB1 is pressed\r\n";     // 8 bits * 4clkpbit * 16
char* pb2_pressed = "PB2 is pressed\r\n";     // 8 bits * 4clkpbit * 16
char* pb3_pressed = "PB3 is pressed\r\n";     // 8 bits * 4clkpbit * 16
char* pb12_pressed = "PB1 and PB2 are pressed\r\n"; // 8 bits * 4clkpbit * 25
char* pb13_pressed = "PB1 and PB3 are pressed\r\n"; // 8 bits * 4clkpbit * 25
char* pb23_pressed = "PB2 and PB3 are pressed\r\n"; // 8 bits * 4clkpbit * 25
#endif

const uint16_t ONE_SEC = 1000;    // parameter for 1s delay
const uint16_t TWO_SEC = 2000;    // parameter for 2s delay
const uint16_t THREE_SEC = 3000;  // parameter for 3s delay

// Initialize all output level states to be OFF
State l1 = {1, -1, 0};  //stores state for RB7
State l2 = {2, -1, 0};  // stores state for RB8
State l3 = {3, -1, 0};  // stores state for RB9

void app2() 
{
    uint8_t input = 0;
    
    while(1)
    { 
        // first check for a button to be pressed,
        // as this indicates the start of wanting 
        //  to change a lighting configuration
        if(inputChangeFlag) {
            inputChangeFlag = 0;
            input = 0;
            if(!PORTAbits.RA2)
                input |= 0b0001;
            if(!PORTBbits.RB4)
                input |= 0b0010;
            if(!PORTAbits.RA4)
                input |= 0b0100;

            switch(input) {
            case 0b0001: // lighting level 1 will be set
                setLighting(&l1);    
                break;

            case 0b0010: // lighting level 2 will be set
                setLighting(&l2);
                break;

            case 0b0100: // lighting level 3 will be set
                setLighting(&l3);
                break;
               
            default:    // do nothing
                break;
            }
        }
        // Now having set the configuration, 
        // can do the lights
        doLighting(&l1);
        doLighting(&l2);
        doLighting(&l3);
        
        // 1s delay
        delay_ms(ONE_SEC);  
        // due to time of rest of loop, 
        //  might need to change this value to a bit less than 1s
        
        // update the states
        updateState(&l1);
        updateState(&l2);
        updateState(&l3);
        
        // go back to begining to check for input and come back for next second 
    }   
}

void setLighting(State* l)
{
    // configure output depending on RxChar
    switch(RxChar)
    {
        case 'O':   // turn on lights
            l->blinkInterval = 0;
            l->secToBlink = -1;
            break;
        
        case 'F':   // turn off lights
            l->blinkInterval = -1;
            l->secToBlink = -1;
            break;
            
        case '1':   // lights blink every 1s
            l->blinkInterval = 1;
            l->secToBlink = 1;
            break;
            
        case '2':   // lights blink every 2s
            l->blinkInterval = 2;
            l->secToBlink = 2;
            break;
            
        case '3':   // lights blink every 3s
            l->blinkInterval = 3;
            l->secToBlink = 3;
            break;
            
        default:
            // do nothing as have unexpected RxChar value
            break;
    }
    return;
}

void doLighting(State* l)
{
   switch(l->blinkInterval)
   {
       case -1:
           // turn off LED
           led_off(l->level);
           break;
           
       case 0:
           // turn on LED
           led_on(l->level);
           break;
           
       default:
           // blinking LED
           // now need to check if need to change output
           if (l->secToBlink == 0)
           {
              led_switch(l->level); 
           }
           break;
   }
}

void updateState(State* l)
{
    switch(l->secToBlink)
    {
        case -1:
            // no need to count down seconds
            // doing nothing
            break;
            
        case 0:
            // Need to start counting again as just switched output
            l->secToBlink = l->blinkInterval;
            break;
            
        default:
            // Count seconds down as 1 seconds past
            (l->secToBlink)--;
    }
    return;
}

void led_on(uint8_t level)
{
    switch(level)
    {
        case 1: // RB7
            LED7_ON;
            break;
            
        case 2: // RB8
            LED8_ON;
            break;
            
        case 3: // RB9
            LED9_ON;
            break;
            
    }
}

void led_off(uint8_t level)
{
    switch(level)
    {
        case 1: // RB7
            LED7_OFF;
            break;
            
        case 2: // RB8
            LED8_OFF;
            break;
            
        case 3: // RB9
            LED9_OFF;
            break;
            
    }
}

void led_switch(uint8_t level)
{
    switch(level)
    {
        case 1: // RB7
            LED7_SWITCH;
            break;
            
        case 2: // RB8
            LED8_SWITCH;
            break;
            
        case 3: // RB9
            LED9_SWITCH;
            break;
            
    }
}