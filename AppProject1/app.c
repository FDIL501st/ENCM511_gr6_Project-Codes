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

const uint16_t ONE_SEC;    // parameter for 1s delay
const uint16_t TWO_SEC;    // parameter for 2s delay
const uint16_t THREE_SEC;  // parameter for 3s delay

void app1()
{
    uint8_t input = 0;
    uint8_t time_minutes = 00;
	uint8_t time_seconds = 00;
    //char msg[128];
    
    while(1)
    { 
        // detect change in input before trying anything
        if(inputChangeFlag) {
            inputChangeFlag = 0;    //clear inputChangeflag
            input = 0;  //reset input to 0 so can read new input
            // read new input
            if(!PORTAbits.RA2)
                input |= 0b0001;
            if(!PORTBbits.RB4)
                input |= 0b0010;
            if(!PORTAbits.RA4)
                input |= 0b0100;

            switch(input) {
 
            case 0b001: // adjusting the time of minutes
//					while(time_minutes<59)
//					{
//						time_minutes++;
//						LED_SWITCH;	
//					}						
//					Disp2String(time_minutes + ":" + time_seconds);
//					break;
                while(time_minutes <= 59)
                {
                    // move to next minute option
                    if (time_minutes == 59)
                        time_minutes = 0;
                    else
                        time_minutes++;

                    // display current time option
                    Disp2String(time_minutes + ":" + time_seconds);

                    delay_ms(ONE_SEC); //1s delay between change of minute choice
                    
                    //if change input detected(eg// stop pressing button),
                    //  need to get out of loop and stop timer
                    if (inputChangeFlag)
                    {
                        T2CONbits.TON = 0; // Stops T2 clock.
                        T2flag = 10; //Clear T2flag 
                        inputChangeFlag = 0;    //clear inputChangeflag
                        break;
                    }
                }
                break;

            case 0b010: // adjusting the time of seconds
//					while(time_seconds<59)
//					{
//						time_seconds++;
//						LED_SWITCH;
//					}
//					Disp2String(time_minutes + ":" + time_seconds);
//					break;
                while(time_seconds <= 59)
                {
                    //move to next second option
                    if (time_seconds == 59)
                        time_seconds = 0;
                    else
                        time_seconds++;

                    // display current time option
                    Disp2String(time_minutes + ":" + time_seconds);

                    delay_ms(ONE_SEC); //1s delay between change of second choice
                    
                    //if change input detected(eg// stop pressing button),
                    //  need to get out of loop and stop timer
                    if (inputChangeFlag)
                    {
                        T2CONbits.TON = 0; // Stops T2 clock.
                        T2flag = 10; //Clear T2flag 
                        inputChangeFlag = 0;    //clear inputChangeflag
                        break;
                    }
                }
                break;

            case 0b100: // if a long press of 3s+ occurred, reset the timer and return, else start the timer counting 
                if(longPress(THREE_SEC) == 1)
                {
                    time_minutes = 00;
                    time_seconds = 00;
                    break;
                }
                while(time_minutes > 0)
                {
                    while(time_seconds > 0)
                    {
                        time_seconds--;
                        Disp2String(time_minutes + ":" + time_seconds);
                        LED_SWITCH;
                        delay_ms(ONE_SEC);
                    }
                    time_minutes--;
                    time_seconds = 59;
                }
                LED_ON;
                delay_ms(THREE_SEC);
                break;
            
            // turn off LED for any other inputs
            default:
                LED_OFF;
                break;
            }
        }
    }
}
