#ifndef APP_H
#define	APP_H

#include "IO.h"
#include "timer.h"
#include "cn_irq.h"
#include "UART2.h"
#include "longpress.h"

extern uint8_t inputChangeFlag; // Extern global var.


void app1();
// PROMISES:
// Read 3 bit input from the 3 input ports, RA2, RA4, RB4.
// RA2 input adjust the timer time of minutes, RA4 adjust the timer time of seconds and RB4 either resets the timer or starts the timer

#endif	/* APP_H */

