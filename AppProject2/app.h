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

void app2();
// PROMISES:
// When a button is pressed, change the lighting configuration of that level.
// Reads lighting configuration from UART Rx

void setLighting1();
// PROMISES:
// Using RxChar, sets the lighting configuration of level 1

void setLighting2();
// PROMISES:
// Using RxChar, sets the lighting configuration of level 2

void setLighting3();
// PROMISES:
// Using RxChar, sets the lighting configuration of level 3

#endif	/* APP_H */

