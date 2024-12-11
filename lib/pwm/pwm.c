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


/* Includes ----------------------------------------------------------*/
#include "pwm.h"


/* Function definitions ----------------------------------------------*/
/*************************************************************************
*  Function:    TIM1_pwm_init()
*  Purpose:     Initialize Timer 1 for Fast PWM with frequency 50Hz.
*  Returns:     none
*************************************************************************/
void TIM1_pwm_init(void){
    /*
    *   Compare Output Mode, Fast PWM Mode - Clear OC1A on Compare Match, set OC1A at BOTTOM (non-inverting mode)
    */
    TCCR1A &= ~(1 << COM1A0);
    TCCR1A |= (1 << COM1A1);

    /*
    *   Compare Output Mode, Fast PWM Mode - Clear OC1B on Compare Match, set OC1B at BOTTOM (non-inverting mode)
    */

    TCCR1A &= ~(1 << COM1B0);
    TCCR1A |= (1 << COM1B1);


    /*
    *   Configure Fast PWM Mode
    */
    TCCR1A &= ~(1 << WGM10);
    TCCR1A |= (1 << WGM11);                      
    TCCR1B |= (1 << WGM13) | (1 << WGM12);


    /*
    *   Clock selection with prescaler
    */
    TCCR1B &= ~((1<<CS12) | (1<<CS10));
    TCCR1B |= (1 << CS11);

    /*
    *   TOP of counter
    */
    ICR1=39999;                                
    
    /*
    *   Default servo´s angle
    */
    OCR1A = 2999;
    OCR1B = 2999;

}


/**********************************************************************
 * Function: TIM1_pwm_compA_value()
 * Purpose:  Set pulse width to specific value by Comparator 0 of Timer 1.
 * Input(s): val - Specific number between 0 and 3999 where increse by 1 represents 0,5 us.
 * Returns:  none
 **********************************************************************/
void TIM1_pwm_compA_value(uint16_t val){          

    OCR0A = val;

}


/**********************************************************************
 * Function: TIM1_pwm_compB_value()
 * Purpose:  Set pulse width to specific value by Comparator 0 of Timer 1.
 * Input(s): val - Specific number between 0 and 3999 where increse by 1 represents 0,5 us.
 * Returns:  none
 **********************************************************************/
void TIM1_pwm_compB_value(uint16_t val){          

    OCR0B = val;

}










