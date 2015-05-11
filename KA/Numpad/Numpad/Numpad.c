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
		_delay_ms(50);
		PORTB &= ~_BV(PORTB5);
		_delay_ms(50);
	}while(--count);
}

uint8_t bit_key_to_scancode(uint8_t bit){
	static const uint8_t scancode[16] = {
		0x16, //BIT_KEY_1 0
		0x25, //BIT_KEY_4 1
		0x3D, //BIT_KEY_7 2
		0x5A, //BIT_KEY_STAR 3
		0x1E, //BIT_KEY_2 4
		0x2E, //BIT_KEY_5 5
		0x3E, //BIT_KEY_8 6
		0x45, //BIT_KEY_0 7
		0x26, //BIT_KEY_3 8
		0x36, //BIT_KEY_6 9
		0x46, //BIT_KEY_9 0xA
		0x49, //BIT_KEY_HASH 0xB
		0x79, //BIT_KEY_A 0xC
		0x7B, //BIT_KEY_B 0xD
		0x7C, //BIT_KEY_C 0xE
		0x4A //BIT_KEY_D 0xF
	};
	if(bit<16){
		return scancode[bit];
	}else{
		return 0;
	}
}

int main(void){
	uint16_t keys = 0;
	uint16_t recieved;
	uint16_t last_keys_state = 0;
	uint8_t last_change = 0;
	uint8_t scancode = 0x02;
	uint8_t TRR;
	uint8_t enabled = 1;
	uint8_t LED;
	uint16_t timeout;
	
	ps2_initialize();
	keyboard_initialize();
	DDRB |= _BV(PORTB5);

	while (1){
		if(ps2_check_host()){
			recieved = ps2_recieve_byte();
			//TODO check parity
			switch (recieved & 0xFF){
				// LED
				case 0xED:
					last_change = 0xFA;
					ps2_send_byte(0xFA);
					for(timeout=0; timeout<500; timeout++){
						if(ps2_check_host()){
							LED = ps2_recieve_byte();
							break;
						}
						_delay_us(40);
					}
					break;
				// echo
				case 0xEE:
					last_change = 0xEE;
					ps2_send_byte(0xEE);
					break;
				// set scan code set
				case 0xF0:
					last_change = 0xFA;
					ps2_send_byte(0xFA);
					for(timeout=0; timeout<500; timeout++){
						if(ps2_check_host()){
							recieved = ps2_recieve_byte();
							if(recieved==0x00){
								ps2_send_byte(scancode);
							}else{
								scancode = recieved;
							}
							break;
						}
						_delay_us(40);				
					}
					break;
				// read keyboard ID
				case 0xF2:
					ps2_send_byte(0xFA);
					ps2_send_byte(0xAB);
					ps2_send_byte(0x83);
					last_change = 0x83;
					break;
				// set typematic repeat rate or TRR
				case 0xF3:
					last_change = 0xFA;
					ps2_send_byte(0xFA);
					for(timeout=0; timeout<500; timeout++){
						if(ps2_check_host()){
							TRR = ps2_recieve_byte();
							break;
						}
						_delay_us(40);
					}
					last_change = 0xFA;
					ps2_send_byte(0xFA);
					break;
				// keyboard enable
				case 0xF4:
					keys = 0;
					last_keys_state = 0;
					enabled = 1;
					last_change = 0xFA;
					ps2_send_byte(0xFA);
					break;
				// keyboard disable
				case 0xF5:
					keys = 0;
					recieved = 0;
					last_keys_state = 0;
					scancode = 0x02;
					TRR = 0;
					enabled = 0;
					LED = 0;
					last_change = 0xFA;
					ps2_send_byte(0xFA);			
					break;
				// resend
				case 0xFE:
					ps2_send_byte(0xFA);
					ps2_send_byte(last_change);
					break;
				// reset				
				case 0xFF:
					ps2_send_byte(0xFA);
					keys = 0;
					recieved = 0;
					last_keys_state = 0;
					last_change = 0;
					scancode = 0x02;
					TRR = 0;
					enabled = 1;
					LED = 0;
					last_change = 0xAA;
					ps2_send_byte(0xAA);
					break;
				default:
					last_change = 0x00;
					ps2_send_byte(0x00);
			}
		}
		if(enabled){
			keys = keyboard_read();
			if(keys != last_keys_state){
				uint8_t key;
				uint16_t mask = 1;
				last_keys_state = keys ^ last_keys_state;
				for(key=0; key<16; key++){
					if(last_keys_state & mask){
						//change
						if(!(keys & mask)){
							ps2_send_byte(0xF0);
							PORTB &= ~_BV(PORTB5);
						}else{
							PORTB |= _BV(PORTB5);
						}
						ps2_send_byte(bit_key_to_scancode(key));
					}
					mask <<= 1;
				}
				last_keys_state = keys;
			}
		}
	}	
}