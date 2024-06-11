#include "uart.h"
#include "servo.h"
#include "command_decoder.h"
#include "string.h"
#include "ad_converter.h"

#define NULL			'\0'

void ADC_Display(unsigned int uiValueBufor){
	char cStringToSend[13] = "";

	AppendUIntToString(uiValueBufor,cStringToSend);
	AppendString("\n", cStringToSend);
	Transmiter_SendString(cStringToSend);
}






int main(){
	unsigned int uiValueBufor;
	UART_InitWithInt(9600);
	ServoInit(50);
	ADC_Init();
	
	while(1){
		if(Transmiter_GetStatus() == FREE){
			uiValueBufor = ADC_Read(0);
			ADC_Display(uiValueBufor);
			ServoGoTo(uiValueBufor/21);
		}
	}
}
