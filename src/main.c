#include <Arduino.h>
#include <avr/io.h>
#include <uart.h>
#include <timer.h>
#include <pwm.h>
#include <adc.h>
#include <lcd.h>
#include <gpio.h>
#include <util/delay.h>

#define UP_LDR_PIN 0
#define DOWN_LDR_PIN 1
#define LEFT_LDR_PIN 2
#define RIGHT_LDR_PIN 3
#define BATTERY_VOLTAGE 4

#define TOP 5199
#define BOTTOM 99

float voltage_battery = 0;
uint16_t ldr_light_detect;
char string[3];                             //string for lcd

volatile uint8_t flag_interrupt = 0;

void battery_voltage_uart(){

  voltage_battery = (adc_read(BATTERY_VOLTAGE)*0.0048828125);
  uart_puts("\nvoltage battery:");
  uint8_t whole_part = voltage_battery;
  uart_puts(itoa(whole_part, string, 10));
  uart_puts(".");
  uart_puts(itoa((voltage_battery - whole_part)*100, string, 10));
  uart_puts("V\n");

}


void position_adjust(){

  if ((adc_read(UP_LDR_PIN) < adc_read(DOWN_LDR_PIN)) && (OCR1B < TOP)) {
    OCR1B += 100;
  }
  
  if (adc_read(UP_LDR_PIN) > adc_read(DOWN_LDR_PIN) && (OCR1B > BOTTOM)) {
    OCR1B-=100;
  }

  if (adc_read(LEFT_LDR_PIN) < adc_read(RIGHT_LDR_PIN) && (OCR1A < TOP)) {
    OCR1A+=100;
  }

  if (adc_read(LEFT_LDR_PIN) > adc_read(RIGHT_LDR_PIN) && (OCR1A > BOTTOM)) {
    OCR1A-=100;
  }

}

void LCD_print_info(){
  lcd_gotoxy(0,0);
  ldr_light_detect = adc_read(UP_LDR_PIN);
  lcd_puts("U:");
  lcd_puts(itoa(ldr_light_detect, string, 10));
  
  lcd_gotoxy(5,0);
  ldr_light_detect = adc_read(DOWN_LDR_PIN);
  lcd_puts("D:");
  lcd_puts(itoa(ldr_light_detect, string, 10));

  lcd_gotoxy(0,1);
  ldr_light_detect = adc_read(LEFT_LDR_PIN);
  lcd_puts("L:");
  lcd_puts(itoa(ldr_light_detect, string, 10));

  lcd_gotoxy(5,1);
  ldr_light_detect = adc_read(RIGHT_LDR_PIN);
  lcd_puts("R:");
  lcd_puts(itoa(ldr_light_detect, string, 10));
  
  lcd_gotoxy(11,0);
  lcd_puts("BatV:");
  lcd_gotoxy(12,1);
  voltage_battery = (adc_read(BATTERY_VOLTAGE)*0.0048828125);
  uint8_t whole_part = voltage_battery;
  lcd_puts(itoa(whole_part, string, 10));
  lcd_puts(".");
  lcd_puts(itoa((voltage_battery - whole_part)*100, string, 10));
}

int main(void) {
  DDRB |= (1 << DDB2) | (1 << DDB1);          //configure pin PB1 and PB2  as output for PWM
  
  uart_init(UART_BAUD_SELECT(9600, F_CPU));
  lcd_init(LCD_DISP_ON);
  TIM1_pwm_init();

  GPIO_mode_output(&DDRB, PB3);
  GPIO_write_low(&PORTB, PB3);

  TIM0_ovf_enable();
  TIM0_ovf_16ms();
  sei();

  adc_init();
  
  while (1) {

    if (flag_interrupt==1)
    {
      LCD_print_info();
      battery_voltage_uart();
      position_adjust();

      flag_interrupt = 0;
    }
    
  }
  return 0;
}

ISR(TIMER0_OVF_vect)
{
    static uint8_t n_ovfs = 0;

    if (n_ovfs >= 30) {
      flag_interrupt = 1;
      n_ovfs = 0; 
    }

    n_ovfs++;
}

