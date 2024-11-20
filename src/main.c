#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>
#include <uart.h>
#include <timer.h>

#define ADC_CHANNEL 0

uint16_t ldr_light_detect;
char string[8];

void adc_init(void) {
  ADMUX = (1 <<REFS0) | (ADC_CHANNEL & 0x07);
  ADCSRA = (1 <<ADEN) | (1 <<ADPS2) | (1 <<ADPS1) | (1 <<ADPS0);
}

uint16_t adc_read(void) {
  ADCSRA |= (1 <<ADSC);
  while (ADCSRA & (1 <<ADSC));
  return ADC;
}

int main(void) {
  
  
  uart_init(UART_BAUD_SELECT(9600, F_CPU));
  TIM0_ovf_enable();
  TIM0_ovf_16ms();
  sei();

  
  adc_init();
  DDRB |= (1<<PB0);

  while (1) {
    
  }
  return 0;
}

ISR(TIMER0_OVF_vect)
{
    static uint8_t n_ovfs = 0;

    n_ovfs++;
    if (n_ovfs >= 200) {
    
    ldr_light_detect = adc_read();
    uart_puts(itoa(ldr_light_detect, string, 10));
    uart_puts("\n");
    //uart_puts("ahoj");
    }
}

