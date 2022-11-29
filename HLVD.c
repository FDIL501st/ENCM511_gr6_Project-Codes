#include "xc.h"
#include "HLVD.h"

void HLVDinit(unsigned int hlvd)
{
	HLVDCON.HLVDEN = 1; //enables HLVD
	
	HLVDCON.HLSIDL = 0;
	HLVDCON.VDIR = 1; //occurs when voltage equals or goes above the trip point
	HLVDCON.BGVST = 1; //indicates the band gap voltage is stable
	HLVDCON.IRVST = 1; // indicates that the internal reference voltage is stable and the 
						//high-voltage detect the logic generates the interrupt flat at the specified voltage range
	HLVDCON.HLVDL = hlvd; // determining the trip point
	
	//HLVD Interrupt Operation
	
	IPC18.HLVDIP = 7;
	IEC4.HLVDIE = 1;
}

void __attribute__ ((interrupt,no_auto_psv)) _HLVDInterrupt(void)
{
	IFS4bits.HLVDIF=0; // Clear interrupt flag
	myflag = 1; //user-defined flag
	IEC4bits.HLVDIE = 0; //disable interrupt. Re-enable elsewhere
	return;
}

void decideHLVD(unsigned float voltageValue)
{
	if(voltageValue < 1.94)
		HLVDinit(0000);
		
	else if(voltageValue > 1.81 && voltageValue < 2.00)
		HLVDinit(0001);
	
	else if(voltageValue > 1.85 && voltageValue < 2.05)
		HLVDinit(0010);
	
	else if(voltageValue > 1.90 && voltageValue < 2.10)
		HLVDinit(0011);
	
	else if(voltageValue > 1.95 && voltageValue < 2.15)
		HLVDinit(0100);
	
	else if(voltageValue > 2.06 && voltageValue < 2.28)
		HLVDinit(0101);
	
	else if(voltageValue > 2.12 && voltageValue < 2.34)
		HLVDinit(0110);
	
	else if(voltageValue > 2.24 && voltageValue < 2.48)
		HLVDinit(0111);
	
	else if(voltageValue > 2.31 && voltageValue < 2.55)
		HLVDinit(1000);
	
	else if(voltageValue > 2.47 && voltageValue < 2.73)
		HLVDinit(1001);
	
	else if(voltageValue > 2.64 && voltageValue < 2.92)
		HLVDinit(1010);
	
	else if(voltageValue > 2.74 && voltageValue < 3.02)
		HLVDinit(1011);
	
	else if(voltageValue > 2.85 && voltageValue < 3.15)
		HLVDinit(1100);
	
	else if(voltageValue > 2.96 && voltageValue < 3.28)
		HLVDinit(1101);
	
	else if(voltageValue > 3.22 && voltageValue < 3.56)
		HLVDinit(1110);
	
	else
		HLVDinit(1111);
}