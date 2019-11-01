/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-09-27
 * Last update: 2019-09-26
 * Platform:    ATmega328P, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description: Blink a LED with delay function.
 * TODO: Verify functionality of LED blinker.
 * NOTE: Macro _BV converts a bit number into a byte value (see AVR Libc
 * Reference Manual).
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define SEGMENT_DATA    PB0
#define SEGMENT_CLOCK    PD7
#define SEGMENT_LATCH    PD4  

/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
  * Brief:  Main program. Blink a LED with delay function.
  * Input:  None
  * Return: None
  */
int main(void)
{

    DDRB |= _BV(SEGMENT_DATA);
    DDRD |= _BV(SEGMENT_CLOCK) | _BV(SEGMENT_LATCH);

  uint8_t digit = 0b11000000; //DP
  uint8_t position = 0b00000100; // xxxx0123
  uint8_t temp;

  for(uint8_t i = 0; i < 8; i++){
    //set segment
    temp = digit & (1<<(7-i));
    if (temp == 0)
      PORTB &= ~_BV(SEGMENT_DATA);
    else 
      PORTB |= _BV(SEGMENT_DATA);

    PORTD &= ~_BV(SEGMENT_CLOCK); 
    _delay_us(1);
    PORTD |= _BV(SEGMENT_CLOCK); 
    _delay_us(1);
  }

    for(uint8_t i = 0; i < 8; i++){
    //set position
    temp = position & (1<<(7-i));
    if (temp == 0)
      PORTB &= ~_BV(SEGMENT_DATA);
    else 
      PORTB |= _BV(SEGMENT_DATA);

    PORTD &= ~_BV(SEGMENT_CLOCK); 
    _delay_us(1);
    PORTD |= _BV(SEGMENT_CLOCK); 
    _delay_us(1);
  }

    PORTD &= ~_BV(SEGMENT_LATCH); 
    _delay_us(1);
    PORTD |= _BV(SEGMENT_LATCH); 
    _delay_us(1);

    return (0);
}
