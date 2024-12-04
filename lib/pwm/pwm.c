#include "pwm.h"

void pwm_init(void){
    TCCR1A &= ~(1 << COM1A0);                   //Compare Output Mode, Fast PWM Mode - Clear OC1A on Compare Match, set OC1A at BOTTOM (non-inverting mode)
    TCCR1A |= (1 << COM1A1);

    TCCR1A &= ~(1 << COM1B0);                   //Compare Output Mode, Fast PWM Mode - Clear OC1B on Compare Match, set OC1B at BOTTOM (non-inverting mode)
    TCCR1A |= (1 << COM1B1);

    TCCR1A &= ~(1 << WGM10);
    TCCR1A |= (1 << WGM11);                     //configure Fast PWM Mode 
    TCCR1B |= (1 << WGM13) | (1 << WGM12);

    TCCR1B &= ~((1<<CS12) | (1<<CS10));         //clock selection
    TCCR1B |= (1 << CS11);

    ICR1=39999;                                 //TOP of counter
    
    OCR1A = 2999;                               //default servo´s angle 
    OCR1B = 2999;

}

void pwm_compA_value(uint8_t val){          

    OCR0A = val;

}

void pwm_compB_value(uint8_t val){          

    OCR0B = val;

}










