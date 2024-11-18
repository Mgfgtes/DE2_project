#include "pwm.h"

void pwm_init(void){

    DDRD |= (1 << DDD5);        //configure pin PD5 as output
    DDRD |= (1 << DDD6);        //configure pin PD6 as output

    TCCR0A &= ~(1 << COM0A0);       //Compare Output Mode, Fast PWM Mode - Clear OC0A on Compare Match, set OC0A at BOTTOM (non-inverting mode)
    TCCR0A |= (1 << COM0A1);

    TCCR0A &= ~(1 << COM0B0);       //Compare Output Mode, Fast PWM Mode - Clear OC0B on Compare Match, set OC0B at BOTTOM (non-inverting mode)
    TCCR0A |= (1 << COM0B1);

    TCCR0A |= (1 << WGM01) | (1 << WGM00);       //configure Fast PWM Mode 

    TCCR0B |= (1 << CS02) | (1 << CS00);        //clock selection
    TCCR0B &= ~(1 << CS01);

    OCR0A = 19;         //default servo angle 
    OCR0B = 19;

}

void pwm_compA_value(uint8_t val){          

    OCR0A = val;

}

void pwm_compB_value(uint8_t val){          

    OCR0B = val;

}










