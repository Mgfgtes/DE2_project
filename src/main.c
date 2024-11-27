#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>
#include <uart.h>
#include <timer.h>
#include <pwm.h>
#include <gpio.h>

#define UP_LDR_PIN 0
#define DOWN_LDR_PIN 1
#define LEFT_LDR_PIN 2
#define RIGHT_LDR_PIN 3

#define TOP 65400
#define BOTTOM 50

uint16_t ldr_light_detect;
char string[8];

void adc_init(void) {
  
  ADCSRA = (1 <<ADEN) | (1 <<ADPS2) | (1 <<ADPS1) | (1 <<ADPS0);
}

uint16_t adc_read(uint8_t channel) {
  ADMUX = (1 <<REFS0) | (channel & 0x07);


  ADCSRA |= (1 <<ADSC);
  while (ADCSRA & (1 <<ADSC));
  return ADC;
}



int main(void) {
  
  
  uart_init(UART_BAUD_SELECT(9600, F_CPU));

  pwm_init();

  TIM0_ovf_enable();
  TIM0_ovf_16ms();
  sei();

  
  adc_init();
  DDRB |= (1<<PB5);               //???????

  while (1) {
    
  }
  return 0;
}

ISR(TIMER0_OVF_vect)
{
    static uint8_t n_ovfs = 0;

    n_ovfs++;
    if (n_ovfs >= 100) {
      //flag_interrupt = 1;

      ldr_light_detect = adc_read(UP_LDR_PIN);
      uart_puts("UP: ");
      uart_puts(itoa(ldr_light_detect, string, 10));
      uart_puts("\n");

      ldr_light_detect = adc_read(DOWN_LDR_PIN);
      uart_puts("DOWN: ");
      uart_puts(itoa(ldr_light_detect, string, 10));
      uart_puts("\n");

      ldr_light_detect = adc_read(LEFT_LDR_PIN);
      uart_puts("LEFT: ");
      uart_puts(itoa(ldr_light_detect, string, 10));
      uart_puts("\n");

      ldr_light_detect = adc_read(RIGHT_LDR_PIN);
      uart_puts("RIGHT: ");
      uart_puts(itoa(ldr_light_detect, string, 10));
      uart_puts("\n");
      uart_puts("\n");
      GPIO_toggle(&PORTB,PB5);
      n_ovfs = 0;

      if ((adc_read(UP_LDR_PIN) < adc_read(DOWN_LDR_PIN)) && (OCR1B < TOP)) {
        OCR1B += 50;

      }
      if (adc_read(UP_LDR_PIN) > adc_read(DOWN_LDR_PIN) && (OCR1B > BOTTOM)) {
        OCR1B-=50;
      }
      
      if (adc_read(LEFT_LDR_PIN) < adc_read(RIGHT_LDR_PIN) && (OCR1A < TOP)) {
        OCR1A+=50;
      }
      if (adc_read(LEFT_LDR_PIN) > adc_read(RIGHT_LDR_PIN) && (OCR1A > BOTTOM)) {
        OCR1A-=50;
      }
    }

}

