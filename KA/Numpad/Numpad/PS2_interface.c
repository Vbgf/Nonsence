#include "board.h"
#include "PS2_interface.h"
#include <avr/io.h>
#include <util/delay.h>

#define CLOCK_0() {PS2_DDR |= _BV(PS2_CLOCK); PS2_PORT &= ~_BV(PS2_CLOCK);}
#define CLOCK_1() {PS2_DDR &= ~_BV(PS2_CLOCK); PS2_PORT |= _BV(PS2_CLOCK);}
#define DATA_0() {PS2_DDR |= _BV(PS2_DATA); PS2_PORT &= ~_BV(PS2_DATA);}
#define DATA_1() {PS2_DDR &= ~_BV(PS2_DATA); PS2_PORT |= _BV(PS2_DATA);}

/* half clock initialized for 40us clock */
uint8_t ps2_half_clock = (40/2*F_CPU/1000000/3);

/* Initializes the interface */
void ps2_initialize(void){
	CLOCK_1();
	DATA_1();
}

void ps2_wait_for_host(){
	uint16_t timeout;
	for(timeout=0; timeout<150; timeout++){
		if(PS2_PIN & _BV(PS2_CLOCK)){
			break;
		}
		_delay_us(40);
	}
}

/* Sends 1 byte to host + 1 parity bit */
void ps2_send_byte(uint8_t data){
	uint8_t count;
	uint8_t parity = 1;
	DATA_0();
	_delay_loop_1(ps2_half_clock);
	CLOCK_0();
	_delay_loop_1(ps2_half_clock);
	for(count=0; count<10; count++){
		CLOCK_1();
		if(count == 8){
			data = parity;
		}
		if(count == 9){
			data = 1;
		}
		if(data & 1){
			DATA_1();
			parity^=1;
		}else{
			DATA_0();
		}
		data>>=1;
		_delay_loop_1(ps2_half_clock);
		CLOCK_0();
		_delay_loop_1(ps2_half_clock);
	}
	CLOCK_1();
	ps2_wait_for_host();
}

/* Function reads 1 byte from host + 1 parity bit. It returns data in the LSB and parity in the MSB */
uint16_t ps2_recieve_byte(void){
	uint8_t count;
	uint16_t result = 0;
	_delay_loop_1(ps2_half_clock);
	for(count=0; count<10; count++){
		result>>=1;
		if(PS2_PIN & _BV(PS2_DATA)){
			result |= 1U<<15;
		}
		CLOCK_0();
		_delay_loop_1(ps2_half_clock);
		CLOCK_1();
		_delay_loop_1(ps2_half_clock);
	}
	result >>= 7;
	
	/* Waiting for stop bit (data line idle) */
	for(count=0; count<8; count++){
		if(PS2_PIN & _BV(PS2_DATA)){
			break;
		}
		CLOCK_0();
		_delay_loop_1(ps2_half_clock);
		CLOCK_1();
		_delay_loop_1(ps2_half_clock);
	} /* If count == 8 can be signaled for error */

	/* Sending acknowledge bit */
	CLOCK_0();
	_delay_loop_1(ps2_half_clock);
	CLOCK_1();
	DATA_0();
	_delay_loop_1(ps2_half_clock);
	CLOCK_0();
	_delay_loop_1(ps2_half_clock);
	CLOCK_1();
	DATA_1();
	ps2_wait_for_host();
	return result;
}

//Checks if the clock line is low for at least 100us
//Meaning host wants to transfer something
// returns 1 if host wants to send something, else 0
uint8_t ps2_check_host(void){
	uint16_t i;
	if(!(PS2_PIN & _BV(PS2_CLOCK))){
		for(i = 0; i<(300*(F_CPU/1000000)/16); i++){
			if((PS2_PIN & (_BV(PS2_DATA) | _BV(PS2_CLOCK))) == _BV(PS2_CLOCK)){
				return 1;
			}
		}
	}
	return 0;
}