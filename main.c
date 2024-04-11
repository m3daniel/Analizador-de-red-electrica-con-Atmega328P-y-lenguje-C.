#include <stdio.h>
#include "adc.h"
#include "uart.h"

int main(void){
	int adcv;
	char store[20];
	//DDRB |= (1<<DDB1)|(1<<DDB2)|(1<<DDB3);
	DDRC &= ~(_BV(1));
	adc_starter();
	UART_init();
	
	//PORTB = 0b00000000;
	
	while (1) {
		adcv = adcread(1);
		adcv = ((adcv*5.0)/1024);
		sprintf(store, "%d",adcv);
		UART_write_txt(store);
		UART_write_txt("\n\r");
		
		
		/*if(adcv>=0 && adcv<400){
		PORTB |= (1<<PORTB3);
		}else{
		PORTB &= ~(1<<PORTB3);}
		
		if(adcv>=400 && adcv<800){
		PORTB |= (1<<PORTB2);
		}else{
		PORTB &= ~(1<<PORTB2);}
		
		if(adcv>=800){
		PORTB |= (1<<PORTB1);
		}else{
		PORTB &= ~(1<<PORTB1);}*/
		
		_delay_ms(1000);
	}
}


