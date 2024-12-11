/***********************************************************************
 * 
 * Solar panel rotation with 16x2 alphanumeric display.
 * 
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2024 Matej Matousek
 * 
 * This work is licensed under the terms of the MIT license.
 *
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <Arduino.h>
#include <avr/io.h>
#include <uart.h>
#include <timer.h>
#include <pwm.h>
#include <adc.h>
#include <lcd.h>
#include <gpio.h>
#include <util/delay.h>

/* Pin definitions --------------------------------------------------*/
#define UP_LDR_PIN 0
#define DOWN_LDR_PIN 1
#define LEFT_LDR_PIN 2
#define RIGHT_LDR_PIN 3
#define BATTERY_VOLTAGE 4

/* Definitions of max servo rotation --------------------------------*/
#define TOP 5199
#define BOTTOM 99


/*
* Value for convertion of battery voltage
*/
float voltage_battery = 0;
/*
* Value from ADC for LDR
*/
uint16_t ldr_light_detect;
/*
* String for lcd and UART
*/
char string[3];
/*
* Flag used by interrupt
*/
volatile uint8_t flag_interrupt = 0;

/* Function definitions ----------------------------------------------*/

/*************************************************************************
*  Function:    battery_voltage_uart()
*  Purpose:     Read battery voltage and send value by UART.
*  Returns:     none
*************************************************************************/
void battery_voltage_uart(){
  
  /*
  * Read battery voltage and convert it with constant
  */
  voltage_battery = (adc_read(BATTERY_VOLTAGE)*0.0048828125);

  /*
  * Print battery voltage as two integers
  */
  uart_puts("\nvoltage battery:");
  uint8_t whole_part = voltage_battery;
  uart_puts(itoa(whole_part, string, 10));
  uart_puts(".");
  uart_puts(itoa((voltage_battery - whole_part)*100, string, 10));
  uart_puts("V\n");

}

/*************************************************************************
*  Function:    position_adjust()
*  Purpose:     Check every LDR and adjust position acording to readings.
*  Returns:     none
*************************************************************************/
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

/*************************************************************************
*  Function:    LCD_print_info()
*  Purpose:     Read values from ADC (battery voltage and LDRs) and print it on alphanumeric LCD.
*  Returns:     none
*************************************************************************/
void LCD_print_info(){

  /*
  * LDR values
  */
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
  

  /*
  * Battery voltage
  */
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
  /*
  * Configure pin PB1 and PB2  as output for PWM
  */
  DDRB |= (1 << DDB2) | (1 << DDB1);
  
  /*
  * Enable LCD
  */
  GPIO_mode_output(&DDRB, PB3);
  GPIO_write_low(&PORTB, PB3);

  /*
  * Initialize UART
  */
  uart_init(UART_BAUD_SELECT(9600, F_CPU));

  /*
  * Initialize LCD
  */
  lcd_init(LCD_DISP_ON);
  
  /*
  * Initialize PWM on Timer 1
  */
  TIM1_pwm_init();

  
  /*
  * Initialize 16 ms Timer 0 overflow
  */
  TIM0_ovf_enable();
  TIM0_ovf_16ms();
  sei();

  /*
  * Initialize ADC
  */
  adc_init();
  
  while (1) {

    /*
    * Every cca 0,5 s check battery voltage and solar panel position
    */
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

