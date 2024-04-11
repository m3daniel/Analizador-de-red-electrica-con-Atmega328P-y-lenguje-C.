#ifndef adc_h_
#define adc_h_

#include <avr/io.h>
#include <util/delay.h>

void adc_starter(void);
int adcread(uint8_t canal);

#endif
