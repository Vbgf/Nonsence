#include <avr/io.h>
#include <avr/delay.h>
#include "board.h"

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

int main(void)
{
	while (1){
		light_level(200);
	}
}