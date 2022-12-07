#include "xc.h"
#include "IO.h"

void IOinit()
{
   TRISAbits.TRISA3 = 1;
   // set AN5 to be an analog port, rest as digital
    AD1PCFG = 0xFFDF;
}