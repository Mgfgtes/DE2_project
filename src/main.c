// -- Includes -------------------------------------------------------
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
// #include <twi.h>            // I2C/TWI library for AVR-GCC
#include <stdio.h>          // C library. Needed for `sprintf`


// -- Function definitions -------------------------------------------
/*
 * Function: Main function where the program execution begins
 * Purpose:  
 * Returns:  none
 */
int main(void)
{
    twi_init();

    sei();  // Needed for UART


    // Infinite empty loop
    while (1)
    {
    }

    // Will never reach this
    return 0;
}