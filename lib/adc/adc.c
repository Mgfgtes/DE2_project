/***********************************************************************
 * 
 * ADC library for AVR-GCC.
 * 
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2024 Vojtech Larva
 * 
 * This work is licensed under the terms of the MIT license.
 *
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <adc.h>


/* Function definitions ----------------------------------------------*/
/*************************************************************************
*  Function:    adc_init()
*  Purpose:     Initialize Analog-digital converter.
*  Returns:     none
*************************************************************************/
void adc_init(void) {
  ADCSRA = (1 <<ADEN) | (1 <<ADPS2) | (1 <<ADPS1) | (1 <<ADPS0);
}


/**********************************************************************
 * Function: adc_read()
 * Purpose:  Measure and convert to digital representation value from specific analog pin.
 * Input(s): channel-Pin for MUX of ADC (0-5 stand for PC0-PC5)
 * Returns:  16-bit integer value representation of voltage connected to selected pin
 **********************************************************************/
uint16_t adc_read(uint8_t channel) {
  /*
  * MUX register selection
  */
  ADMUX = (1 <<REFS0) | (channel & 0x07);
  ADCSRA |= (1 <<ADSC);

  /*
  * Waiting for ADC to finish
  */
  while (ADCSRA & (1 <<ADSC));


  return ADC;
}