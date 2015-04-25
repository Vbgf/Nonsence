#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#define BIT_KEY_1 0
#define BIT_KEY_2 4
#define BIT_KEY_3 8
#define BIT_KEY_4 1
#define BIT_KEY_5 5
#define BIT_KEY_6 9
#define BIT_KEY_7 2
#define BIT_KEY_8 6
#define BIT_KEY_9 0xA
#define BIT_KEY_0 7
#define BIT_KEY_A 0xC
#define BIT_KEY_B 0xD
#define BIT_KEY_C 0xE
#define BIT_KEY_D 0xF
#define BIT_KEY_STAR 3
#define BIT_KEY_HASH 0xB

void keyboard_initialize(void);
uint16_t keyboard_read(void);

#endif