#ifndef APP_H
#define	APP_H

#include "IO.h"
#include "timer.h"
#include "cn_irq.h"
#include "UART2.h"
#include "HLVD.h"

extern uint8_t inputChangeFlag; // Extern global var.
extern uint8_t T2flag;
extern char RxChar;

struct levelState
{
    uint8_t level;  //level whose state we track
    
    signed int blinkInterval;
    // -1 means off, 0 means stays on, 
    // 1,2,3 are blinking interval
    
    signed int secToBlink;
    // counts number of seconds till LED switches
    // when 0, should call LED#_SWITCH
    // if -1, means no need to count down as no need to blink
};

typedef struct levelState State;

void app2();
// PROMISES:
// When a button is pressed, change the lighting configuration of that level.
// Reads lighting configuration from UART Rx.
// Also properly outputs all 3 levels of lights at once 
//  depending on configurations made.

void setLighting(State* l);
// REQUIRE:
// A pointer to a state of a level.
// PROMISES:
// Sets the state of the level depending on RxChar

void doLighting(State* l);
// REQUIRES:
//  A pointer to a state of a level.
// PROMISES:
// Depending on state of the level, 
// appropriately turn on or off the level 

void updateState(State* l);
// REQUIRES:
// A pointer to a state of a level.
// To be called after a 1s delay has been called.
// PROMISES:
// Properly update the secToBlink field.

void led_on(uint8_t level);
// REQUIRES: 
// level, either 1,2 or 3
// PROMISES:
// Outputs a 1 on level passed.
// 1 = RB7, 2 = RB8, 3 = RB9

void led_off(uint8_t level);
// REQUIRES: 
// level, either 1,2 or 3
// PROMISES:
// Outputs a 0  on level passed.
// 1 = RB7, 2 = RB8, 3 = RB9

void led_switch(uint8_t level);
// REQUIRES: 
// level, either 1,2 or 3
// PROMISES:
// Outputs is opposite to what is currently on level passed.
// 1 = RB7, 2 = RB8, 3 = RB9

#endif	/* APP_H */

