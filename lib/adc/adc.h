#ifndef ADC_H
# define ADC_H

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

/**
 * @file 
 * @defgroup adc ADC Library <adc.h>
 * @code #include <adc.h> @endcode
 *
 * @brief ADC library for AVR-GCC.
 *
 * The library contains functions for controlling Analog-digital converter.
 *
 * @note Based on AVR Libc Reference Manual. Tested on ATmega328P 
 *       (Arduino Uno), 16 MHz, AVR 8-bit
 * @author Vojtech Larva, Brno University of Technology, Czechia
 * @copyright (c) 2024 Vojtech Larva, This work is licensed under 
 *                the terms of the MIT license
 * @{
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>

/* Function prototypes -----------------------------------------------*/
/**
 * @brief  Initialize Analog-digital converter.
 * @return none
 */
void adc_init(void);

/**
 * @brief    Measure and convert to digital representation value from specific analog pin.
 *
 * @param    channel Definition of pin for MUX of ADC (0-5 stand for PC0-PC5)
 * @return   16-bit integer value representation of voltage connected to selected pin
 */
uint16_t adc_read(uint8_t channel);

#endif