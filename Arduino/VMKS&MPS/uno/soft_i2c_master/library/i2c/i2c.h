#ifndef i2c_h
#define i2c_h

#include "Arduino.h"

#define CLOCK_PIN     4
#define DATA_PIN      5
#define START_ADDRESS 10
#define I2C_SPEED_KHZ 100
#define MAX_ADDRESS   120

class i2c{
private:
	uint8_t SCL_;
	uint8_t SDA_;
	uint8_t clock_;
  
public:
	// Constructor, initializes class with clock, data and bus speed
	i2c(uint8_t SCL, uint8_t SDA, uint16_t speed = I2C_SPEED_KHZ);

	// Starts the master on the bus, must be called in addition to the constructor.
	void init(uint8_t SCL, uint8_t SDA);

	// Low level functions
	// Marks start sequence
	void start();
	
	// Marks stop/end sequence
	void stop();

	// Sends master acknoledge
	void ACK();

	// Waits for slave acknoledge
	bool wait_ACK();

	// Mid level functions
	// Sends one bit on the bus
	void send_bit(bool b);

	// Sends the 7bit address
	void send_address(uint8_t adr);

	// Sends 8 bits/1 byte of information
	void send_byte(uint8_t B);

	// Recieves 8 bits/1 byte of information
	uint8_t recieve_byte();

	// High level functions
	// Check if slave address is occupied
	bool checkSlave(uint8_t adr);

	// Send one byte (data) to the given address (adr)
	void sendData(uint8_t adr, uint8_t data);

	// Recieve one byte from the given address (adr)
	uint8_t recieveData(uint8_t adr);
};

#endif