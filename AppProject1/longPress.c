#include "xc.h"
#include "longPress.h"


uint8_t longPress(uint16_t time_ms)
{
    delay_ms(time_ms); //timer to put system to delay
    // Figure out what caused us to leave Idle() of the delay_ms()
    
    //case if watchdog timer reset occurred
    if (0) 
    {
        return 1;
    }
    //case if CNinterrupt occurred
    else if (inputChangeFlag)
    {
        inputChangeFlag = 0;    //clear inputChangeFlag
        T2CONbits.TON = 0; // Stops T2 clock. (as no longer need the timer)
        return 0;
    }
    //case if timer2 interrupt occurred
    else if (T2flag)
    {
        T2flag = 0; //clear T2 flag
        return 1;
    }
    //in odd case if none of the above occurs, by default consider long press
    else  
        return 1;
}
