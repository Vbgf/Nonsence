#include <Wire.h>

#define DELAY 10
#define SHOW_SEARCH 0
#define SHOW_FOUND 1
#define SHOW_SENSOR_DATA 1
#define SHOW_ERROR 1

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  int found = 0;
  for(int address = 10;address<128;address++){
    Wire.beginTransmission(address);

    if(SHOW_SEARCH){
      Serial.print(F("Checking address: "));
      Serial.println(address);      
    }
    
    if(Wire.endTransmission() == 0){
      if(SHOW_FOUND){
        Serial.print(F("Found device on address: "));
        Serial.println(address);        
      }
      
      found++;
      Wire.requestFrom(address, 1);

      if(SHOW_SENSOR_DATA){
        Serial.print(F("Sensor data returned from address "));
        Serial.print(address);
        Serial.print(F(": "));
        Serial.println(Wire.read());
      }
    }

    delay(DELAY);
  }

  if(found == 0 and SHOW_ERROR){
    Serial.println(F("No devices found!"));
  }
}
