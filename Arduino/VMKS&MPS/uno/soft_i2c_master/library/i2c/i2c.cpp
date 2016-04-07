#include "Arduino.h"
#include "i2c.h"

i2c::i2c(uint8_t SCL, uint8_t SDA, uint16_t speed){
	SCL_ = SCL;
	SDA_ = SDA;
	clock_ = speed/10;
}

  void i2c::init(uint8_t SCL, uint8_t SDA){
    pinMode(SCL_, INPUT);
    pinMode(SDA_, INPUT);
    SCL_ = SCL;
    SDA_ = SDA;
    pinMode(SCL_, OUTPUT);
    pinMode(SDA_, OUTPUT);
    digitalWrite(SCL, HIGH);
    digitalWrite(SDA, HIGH);   
  }

  void i2c::start(){
    digitalWrite(SDA_, LOW);
    delayMicroseconds(clock_/2);
    digitalWrite(SCL_, LOW);
    delayMicroseconds(clock_/2);
  }

  void i2c::stop(){
    delayMicroseconds(clock_/2);
    digitalWrite(SCL_, HIGH);
    delayMicroseconds(clock_/2);
    digitalWrite(SDA_, HIGH);
    delayMicroseconds(20*clock_);
  }

  void i2c::ACK(){
    digitalWrite(SDA_, HIGH);
    delayMicroseconds(clock_/2);
    digitalWrite(SCL_, HIGH);
    delayMicroseconds(clock_);
    digitalWrite(SCL_, LOW);
    delayMicroseconds(clock_/2);
  }

  bool i2c::wait_ACK(){  
    pinMode(SDA_, INPUT);
    delayMicroseconds(clock_/2);
    digitalWrite(SCL_, HIGH);
    delayMicroseconds(clock_/2);
    bool ack = digitalRead(SDA_);
    delayMicroseconds(5*clock_/2);
    digitalWrite(SCL_, LOW);
    pinMode(SDA_, OUTPUT);
    return !ack;
  }

  void i2c::send_bit(bool b){
    digitalWrite(SDA_, b);
    delayMicroseconds(clock_/2);
    digitalWrite(SCL_, HIGH);
    delayMicroseconds(clock_);
    digitalWrite(SCL_, LOW);
    delayMicroseconds(clock_/2);
  }

  void i2c::send_address(uint8_t adr){
    uint8_t b = 1<<6;
    uint8_t i;
    for(i=0; i<7; i++){
      digitalWrite(SDA_, (adr&b));
      b = b >> 1;
      delayMicroseconds(clock_/2);
      digitalWrite(SCL_, HIGH);
      delayMicroseconds(clock_);
      digitalWrite(SCL_, LOW);
      delayMicroseconds(clock_/2);
    }
  }

  void i2c::send_byte(uint8_t B){
    uint8_t b = 1<<7;
    uint8_t i;
    for(i=0; i<8; i++){
      digitalWrite(SDA_, (B&b));
      b = b >> 1;
      delayMicroseconds(clock_/2);
      digitalWrite(SCL_, HIGH);
      delayMicroseconds(clock_);
      digitalWrite(SCL_, LOW);
      delayMicroseconds(clock_/2);
    }
  }

  uint8_t i2c::recieve_byte(){
    uint8_t result = 0;
    uint8_t b = 0;
    uint8_t i;
    pinMode(SDA_, INPUT);
    for(i=0; i<8; i++){
      delayMicroseconds(clock_/2);
      digitalWrite(SCL_, HIGH);
      delayMicroseconds(clock_/2);
      
      b = digitalRead(SDA_);
      result = result << 1;
      result = result|b;
      
      delayMicroseconds(clock_/2);
      digitalWrite(SCL_, LOW);
      delayMicroseconds(clock_/2);
    }
    pinMode(SDA_, OUTPUT);
    return result;  
  }

  bool i2c::checkSlave(uint8_t adr){
    bool result;
    start();
    send_address(adr);
    send_bit(0);
    result = wait_ACK();
    send_byte(0);
    stop();
    return result;
  }

  void i2c::sendData(uint8_t adr, uint8_t data){
    start();
    send_address(adr);
    send_bit(0);
    wait_ACK();
    send_byte(data);
    wait_ACK();
    stop();
  }

  uint8_t i2c::recieveData(uint8_t adr){
    uint8_t result = 0;
    start();
    send_address(adr);
    send_bit(1);
    wait_ACK();
    result = recieve_byte();
    ACK();
    stop();
    return result;
  }
