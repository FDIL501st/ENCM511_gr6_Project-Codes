#include "test.h"

uint16_t sample_voltage;

void test()
{
    while(1)
    {
        sample_voltage = do_ADC();
        displayBarPercent(sample_voltage);
        //displayBar16Box(sample_voltage); //alternative option of bar
        Disp2Hex(sample_voltage);
        XmitUART2('\n', 1);
    }
}

void displayBarPercent(uint16_t voltage)
{
    // First calculate percent
    unsigned int percent = voltage/1023*100;
    XmitUART2(219, percent);
}

void displayBar16Box(uint16_t voltage)
{
    // First divide voltage into 16 parts
    unsigned int percent = voltage/1023*16;
    XmitUART2(219, percent);
}