#ifndef PWM_H
# define PWM_H

/***********************************************************************
 * 
 * PWM library for AVR-GCC.
 * 
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2024 Matej Matousek
 * 
 * This work is licensed under the terms of the MIT license.
 *
 **********************************************************************/

/**
 * @file 
 * @defgroup pwm PWM Library <pwm.h>
 * @code #include <pwm.h> @endcode
 *
 * @brief PWM library for AVR-GCC.
 *
 * The library contains functions for controlling Timer's 1 pin(s) with PWM.
 *
 * @note Based on AVR Libc Reference Manual. Tested on ATmega328P 
 *       (Arduino Uno), 16 MHz, AVR 8-bit
 * @author Matej Matousek, Brno University of Technology, Czechia
 * @copyright (c) 2024 Matej Matousek, This work is licensed under 
 *                the terms of the MIT license
 * @{
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions


/* Function prototypes -----------------------------------------------*/
/**
 * @brief  Initialize Timer 1 for Fast PWM with frequency 50Hz.
 * @return none
 */
void TIM1_pwm_init(void);

/**
 * @brief    Set pulse width to specific value by Comparator 0 of Timer 1
 *
 * @param    value Specific number between 0 and 3999 where increse by 1 represents 0,5 us.
 * @return   none
 */
void TIM1_pwm_compA_value(uint16_t val);

/**
 * @brief    Set pulse width to specific value by Comparator 1 of Timer 1
 *
 * @param    value Specific number between 0 and 3999 where increse by 1 represents 0,5 us.
 * @return   none
 */
void TIM1_pwm_compB_value(uint16_t val);

#endif











