#include "adc.h"

void adc_starter(void){
	ADMUX &= ~(1<<REFS1);
	ADMUX |= (1<<REFS0);
	ADMUX &= ~(1<<ADLAR);
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
}

int adcread(uint8_t channel){
	uint8_t hvalue, lvalue;
	
	if(channel <= 7) {ADMUX |= channel & 0x07;}
	
#if defined(ADCSRA) && defined(ADCL)
	ADCSRA |= (1<<ADSC);
	while(bit_is_set(ADCSRA, ADSC));
	lvalue = ADCL;
	hvalue = ADCH;
#else
lvalue = 0;
hvalue = 0;
#endif

	return ((hvalue<<8)|lvalue); //0-1023
}