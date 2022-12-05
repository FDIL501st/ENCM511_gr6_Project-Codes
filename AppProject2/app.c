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
                setLighting1();    
                break;

            case 0b0010: // lighting level 2 will be set
                setLighting2();
                break;

            case 0b0100: // lighting level 3 will be set
                setLighting3();
                break;
               
            default:    // do nothing
                break;
            }
        }
        // if reach here and inputChangeFlag is not set, put system to Idle
        //  as if inputChangeFlag is not set, will end up back here.
        // So save power instead of CPU just running entire time 
        //  polling for that flag
        if (!inputChangeFlag)
            Idle();
            // Question, will digital output still occur when in Idle()?
            // Hopefully all Idle does not affect digital IO outputs
        
            //no WDT enabling as it is fine for system to stay in Idle if no changes to input
            
        // Sure, any interrupt can move us back to beginning of loop, not just CN interrupt
        // however will still reduce CPU runtime overall
    }   
}

void setLighting1()
{
    // will be configuring output of RB7
    switch(RxChar)
    {
        case 'O':   // turn on lights
            LED7_ON;
            break;
        
        case 'F':   // turn off lights
            LED7_OFF;
            break;
            
        case '1':   // lights blink every 1s
            // stay here blinking every 1s until a button is pressed
            while (!inputChangeFlag)
            {
                LED7_SWITCH;
                delay_ms(ONE_SEC);
            }
            // no need to clear inputChangeFlag as that will be cleared 
            //  when leave this and start super loop again
            break;
            
        case '2':   // lights blink every 2s
            // stay here blinking every 1s until a button is pressed
            while (!inputChangeFlag)
            {
                LED7_SWITCH;
                delay_ms(TWO_SEC);
            }
            // no need to clear inputChangeFlag as that will be cleared 
            //  when leave this and start super loop again
            break;
            
        case '3':   // lights blink every 3s
            // stay here blinking every 1s until a button is pressed
            while (!inputChangeFlag)
            {
                LED7_SWITCH;
                delay_ms(THREE_SEC);
            }
            // no need to clear inputChangeFlag as that will be cleared 
            //  when leave this and start super loop again
            break;
            
        default:
            // do nothing as have unexpected RxChar value
            break;
    }
}

void setLighting2()
{
    // will be configuring output of RB8
    switch(RxChar)
    {
        case 'O':   // turn on lights
            LED8_ON;
            break;
        
        case 'F':   // turn off lights
            LED8_OFF;
            break;
            
        case '1':   // lights blink every 1s
            // stay here blinking every 1s until a button is pressed
            while (!inputChangeFlag)
            {
                LED8_SWITCH;
                delay_ms(ONE_SEC);
            }
            // no need to clear inputChangeFlag as that will be cleared 
            //  when leave this and start super loop again
            break;
            
        case '2':   // lights blink every 2s
            // stay here blinking every 1s until a button is pressed
            while (!inputChangeFlag)
            {
                LED8_SWITCH;
                delay_ms(TWO_SEC);
            }
            // no need to clear inputChangeFlag as that will be cleared 
            //  when leave this and start super loop again
            break;
            
        case '3':   // lights blink every 3s
            // stay here blinking every 1s until a button is pressed
            while (!inputChangeFlag)
            {
                LED8_SWITCH;
                delay_ms(THREE_SEC);
            }
            // no need to clear inputChangeFlag as that will be cleared 
            //  when leave this and start super loop again
            break;
            
        default:
            // do nothing as have unexpected RxChar value
            break;
    }
}

void setLighting3()
{
    // will be configuring output of RB9
    switch(RxChar)
    {
        case 'O':   // turn on lights
            LED9_ON;
            break;
        
        case 'F':   // turn off lights
            LED9_OFF;
            break;
            
        case '1':   // lights blink every 1s
            // stay here blinking every 1s until a button is pressed
            while (!inputChangeFlag)
            {
                LED9_SWITCH;
                delay_ms(ONE_SEC);
            }
            // no need to clear inputChangeFlag as that will be cleared 
            //  when leave this and start super loop again
            break;
            
        case '2':   // lights blink every 2s
            // stay here blinking every 1s until a button is pressed
            while (!inputChangeFlag)
            {
                LED9_SWITCH;
                delay_ms(TWO_SEC);
            }
            // no need to clear inputChangeFlag as that will be cleared 
            //  when leave this and start super loop again
            break;
            
        case '3':   // lights blink every 3s
            // stay here blinking every 1s until a button is pressed
            while (!inputChangeFlag)
            {
                LED9_SWITCH;
                delay_ms(THREE_SEC);
            }
            // no need to clear inputChangeFlag as that will be cleared 
            //  when leave this and start super loop again
            break;
            
        default:
            // do nothing as have unexpected RxChar value
            break;
    }
}
