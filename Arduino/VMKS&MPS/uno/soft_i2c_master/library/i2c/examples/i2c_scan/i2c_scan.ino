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
  
  Serial.println(F("Scanning available i2c addresses..."));
  
  for(i=START_ADDRESS; i<MAX_ADDRESS; i++){
    if (bus.checkSlave(i)){
      Serial.print(F("Device found on address: ")); 
      Serial.println(i);
    }else{
      Serial.print(F("There is no device on address: ")); 
      Serial.println(i);
    }
    delay(100);
  }
  
  Serial.println(F("Scanning complete!\n"));

}

