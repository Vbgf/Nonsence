#include <i2c.h>

i2c bus = i2c(CLOCK_PIN, DATA_PIN);

void setup() {
  bus.init(CLOCK_PIN, DATA_PIN);
  Serial.begin(9600);
}

void loop() {
  uint8_t data = 45;
  uint8_t result = 0;
  uint8_t i;
  for(i=START_ADDRESS; i<MAX_ADDRESS; i++){
    if (bus.checkSlave(i)){
      Serial.print(F("There is a device on: ")); 
      Serial.println(i);
      Serial.print(F("Sending data ")); 
      Serial.print(data);
      Serial.print(F(" to device "));
      Serial.println(i);
      bus.sendData(i, data);
  
      result = bus.recieveData(i);
      Serial.print(F("Recieved data ")); 
      Serial.print(result);
      Serial.print(F(" from device "));
      Serial.println(i);
    }else{
      Serial.print(F("There is no device on: ")); 
      Serial.println(i);
    }
  }
}
