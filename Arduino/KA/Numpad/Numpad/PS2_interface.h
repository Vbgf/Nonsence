#ifndef PS2_INTERFACE_H_
#define PS2_INTERFACE_H_

#include <avr/io.h>

#ifndef PS2_PORT
#define PS2_PORT PORTC
#define PS2_DDR DDRC
#define PS2_PIN PINC
#endif
#ifndef PS2_CLOCK
#define PS2_CLOCK PORTC2
#endif
#ifndef PS2_DATA
#define PS2_DATA PORTC3
#endif

extern uint8_t ps2_half_clock;

void ps2_initialize(void);
void ps2_send_byte(uint8_t data);
uint16_t ps2_recieve_byte(void);
uint8_t ps2_check_host(void);

#endif