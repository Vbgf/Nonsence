#include "board.h"
#include <avr/io.h>
#include <avr/cpufunc.h>
#include <util/delay.h>
#include "keyboard.h"

/* Keyboard layout:     bits in the scan code (result):
 1   2   3   A  - PD2   =>  0  4  8  C
 4   5   6   B  - PD3   =>  1  5  9  D   
 7   8   9   C  - PD4   =>  2  6  A  E
 *   0   #   D  - PD5   =>  3  7  B  F
 |   |   |   |
PD6 PD7 PB0 PB1
*/

/* result

*/

/* Initializes the ports for the keyboard */
void keyboard_initialize(void){
	/* Rows will be input with pull-up*/
	DDRD &= ~(_BV(PORTD2) | _BV(PORTD3) | _BV(PORTD4) | _BV(PORTD5));
	PORTD |= (_BV(PORTD2) | _BV(PORTD3) | _BV(PORTD4) | _BV(PORTD5));
	
	/* Columns will be input without pull-up*/
	DDRD &= ~(_BV(PORTD6) | _BV(PORTD7));
	PORTD &= ~(_BV(PORTD6) | _BV(PORTD7));
	DDRB &= ~(_BV(PORTB0) | _BV(PORTB1));
	PORTB &= ~(_BV(PORTB0) | _BV(PORTB1));
}

/* Reads all 16 keys from the keyboard and returns a uint16_t */
uint16_t keyboard_read(void){
	uint16_t result;
	uint8_t scan;
	DDRD |= _BV(PORTD6);
	_delay_loop_1(16);
	scan = PIND;
	result = (uint16_t)((scan >> 2) & 0b00001111);
	DDRD &= ~(_BV(PORTD6));
	
	DDRD |= _BV(PORTD7);
	_delay_loop_1(16);
	scan = PIND;
	result |= (uint16_t)((scan << 2) & 0b11110000);
	DDRD &= ~(_BV(PORTD7));
	
	DDRB |= _BV(PORTB0);
	_delay_loop_1(16);
	scan = PIND;
	result |= (uint16_t)((scan >> 2) & 0b00001111) << 8;
	DDRB &= ~(_BV(PORTB0));
	
	DDRB |= _BV(PORTB1);
	_delay_loop_1(16);
	scan = PIND;
	result |= (uint16_t)((scan << 2) & 0b11110000) << 8;
	DDRB &= ~(_BV(PORTB1));
	
	result ^= 0xFFFF; //inverts the result
	return result;
}