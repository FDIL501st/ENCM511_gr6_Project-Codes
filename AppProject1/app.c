#include "app.h"

char* allpbs = "All PBs pressed\r\n";         // 8 bits * 4clkpbit * 17
char* nopbs =  "No PBs pressed\r\n";          // 8 bits * 4clkpbit * 16
char* pb1_pressed = "PB1 is pressed\r\n";     // 8 bits * 4clkpbit * 16
char* pb2_pressed = "PB2 is pressed\r\n";     // 8 bits * 4clkpbit * 16
char* pb3_pressed = "PB3 is pressed\r\n";     // 8 bits * 4clkpbit * 16
char* pb12_pressed = "PB1 and PB2 are pressed\r\n"; // 8 bits * 4clkpbit * 25
char* pb13_pressed = "PB1 and PB3 are pressed\r\n"; // 8 bits * 4clkpbit * 25
char* pb23_pressed = "PB2 and PB3 are pressed\r\n"; // 8 bits * 4clkpbit * 25

void app1()
{
    uint8_t input = 0;
    uint8_t time_minutes = 00;
	uint8_t time_seconds = 00;
    char msg[128];
    
    while(1)
    { 
        
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
                case 0b0001: // adjusting the time of minutes
					while(time_minutes<59)
					{
						time_minutes++;
						LED_SWITCH;	
					}						
					Disp2String(time_minutes + ":" + time_seconds);
					break;

				case 0b0010: // adjusting the time of seconds
					while(time_seconds<59)
					{
						time_seconds++;
						LED_SWITCH;
					}
					Disp2String(time_minutes + ":" + time_seconds);
					break;

            case 0b0100: // if a long press of 3s is occured, reset the timer and return, else start the timer counting 
				if(longPress(3000) == 1)
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
						delay_ms(1000);
						Disp2String(time_minutes + ":" + time_seconds);
						LED_SWITCH;
					}
					time_minutes--;
					time_seconds = 59;
				}
				LED_ON;
				delay_ms(3000);
                break;
                   
            case 0b0000:
                LED_OFF;
                break;
            }
        }
    }
}
