#include <LPC21xx.H>
#include "ad_converter.h"

//-----------Setup------------------------
#define mAIN0_ON_P0_27					0x00400000
#define mADC_Operational				0x00200000
#define mClockRate_11						0x00000400
//-----------Reading----------------------
#define mConvertion_Done 				0x80000000
#define mConvertion_Start_Now 	0x01000000
#define mFirst_Ten_Bits					0x000003FF


void ADC_Init(){
	PINSEL1 = PINSEL1 | mAIN0_ON_P0_27;  // AIN set on P0.27
	ADCR = mADC_Operational | mClockRate_11; // ADC is operational and clockrate is set to 11
}

unsigned int ADC_Read(unsigned char ucChannelNumber){

	unsigned int uiResult = 0;
	
	ADCR |= (1<<ucChannelNumber); // selecting channel
	ADCR |= mConvertion_Start_Now; //starting convertion
	
	while((ADDR & mConvertion_Done) == 0){ // blocking loop, waits for convertion to complete
	}
	
	ADCR ^= ((1<<ucChannelNumber) | mConvertion_Start_Now); // ADC is "not started", clearing channel
	uiResult = ((ADDR >> 6) & mFirst_Ten_Bits);
	return uiResult;
}
