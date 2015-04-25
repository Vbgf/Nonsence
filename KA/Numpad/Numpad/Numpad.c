#include "board.h"
#include <avr/io.h>
#include <util/delay.h>
#include "PS2_interface.h"
#include "keyboard.h"

void light_level(uint8_t level){
	if(level!=0){
		PORTB |= _BV(PORTB5);
		_delay_loop_1((uint8_t)level);
	}
	if((255-level)!=0){
		PORTB &= ~_BV(PORTB5);
		_delay_loop_1((uint8_t)(255-level));
	}
}

void light_count(uint8_t count){
	do{
		PORTB |= _BV(PORTB5);
		_delay_ms(500);
		PORTB &= ~_BV(PORTB5);
		_delay_ms(500);
	}while(--count);
}

int main(void){
	uint16_t keys;
	uint8_t i;
	ps2_initialize();
	keyboard_initialize();
	DDRB |= _BV(PORTB5);
	while (1){
		keys = keyboard_read();
		for(i=0; i<16; i++){
			if(keys & 1){
				light_count(i+1);
				_delay_ms(1500);
				//break;
			}
			keys >>= 1;
		}
	}
}