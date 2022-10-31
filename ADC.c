#include "xc.h"
#include "ADC.h"

void ADC_init()
{
    /* -------------ADC INITIALIZATION ------------------*/
    // Configure AD1CON1 register
    AD1CON1bits.ADON = 1; // turn on ADC module
    AD1CON1bits.ADSIDL = 0; // ADC keeps operating during idle
    AD1CON1bits.FORM = 0;   // ADC output is read as an integer
    AD1CON1bits.SSRC = 0b111; //ADC auto-converts analog signal
    AD1CON1bits.ASAM = 0;   //ADC sampling starts when SAMP bit is set
    AD1CON1bits.SAMP = 0;   //sampling is off, needs to be turned on later 
    
    // Configure AD1CON2 register
    AD1CON2bits.VCFG = 0b000; // Selects AVDD, AVSS (supply voltage to PIC) as Vref
    AD1CON2bits.OFFCAL = 0; // offset calibration bit set to off
    AD1CON2bits.CSCNA = 0;
    AD1CON2bits.SMPI = 0;   // interrupt triggered for every sample converted
    AD1CON2bits.BUFM = 0;   // buffer is one 16-word buffer
    AD1CON2bits.ALTS = 0;   // always use mux A
    
    // Configure AD1CON23 register
    AD1CON3bits.ADRC = 0; // Use system clock(allow for ADC to work while sleeping)
    //Configure the ADC?s sample time by setting bits in AD1CON3 showninslide 17
    // Ensure sample time is 1/10 the
    //  of signal being sampled or as per application?s speed and needs
    AD1CON3bits.SAMC = 0b1111;  //slowest sampling time
    AD1CON3bits.ADCS = 0;   // don't care bits as using system clock 
    // bits to be changed when actual sample time figured out
    // sample_time = 2/fclk*SAMC
    // Assuming fclk = 32kHz
    
    // set AN5 to be an analog port, rest as digital
    AD1PCFG = 0xFFDF;
    
    // ADC input selection
    AD1CHSbits.CH0NA = 0;
    AD1CHSbits.CH0SA = 0b0101;  // analog input coming from AN5(pin8/RA3)
    
    // Omit ADC for input scans
    AD1CSSL = 0;
    
    /* -------------ADC INTERRUPT ROUTINE INITIALIZATION ------------------*/
    IPC3bits.AD1IP = 5; // ADC conversion completion interrupt priority(1-7)
    IEC0bits.AD1IE = 1; // ADC conversion completion interrupts enabled
}

uint16_t do_ADC(void)
{
    uint16_t ADCvalue; // 16 bit register used to hold ADC converted digital output ADC1BUF0
    
    ADC_init();
    
    /* ------------- ADC SAMPLING AND CONVERSION ? CAN BE A DIFFERENT FUNCTION ------------------*/
    AD1CON1bits.SAMP=1; //Start Sampling, Conversion starts automatically after SSRC and SAMC settings
    //while(AD1CON1bits.DONE==0)
    //{}//stalling for first conversion to be done, can be replaced following into the interrupt routine
    // will be doing the following using an interrupt instead of stalling
    Idle();
    //Hopefully reach here due to ADC interrupt getting out of idle
    if (ADCflag)
    {
        ADCflag = 0;    //clear user defined ADC flag
        ADCvalue= ADC1BUF0; // ADC output is stored in ADC1BUF0 as this point
        AD1CON1bits.SAMP=0; //Stop sampling
        AD1CON1bits.ADON=0; //Turn off ADC, ADC value stored in ADC1BUF0;
        return (ADCvalue); //returns 10 bit ADC output stored in ADC1BIF0 to calling function
    }
    
    // In case ADC interrupt did not occur, return 0
    return 0;
}

///// ADC interrupt subroutine
void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void)
{
    IFS0bits.AD1IF = 0; // Clear the ADC1 Interrupt Flag
    ADCflag = 1;    //set the user defined ADC flag
}
