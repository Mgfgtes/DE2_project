#ifndef ADC_H
# define ADC_H

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>


#include <avr/io.h>

void adc_init(void);

uint16_t adc_read(uint8_t channel);

#endif