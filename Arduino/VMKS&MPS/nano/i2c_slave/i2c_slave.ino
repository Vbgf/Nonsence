#include <EEPROM.h>               // For working with non-volatile memory
#include <Wire.h>                 // For working with I2C bus
#include <avr/wdt.h>              // For configuring the Watchdog

#define EEPROM_ADDRESS 0          // The address in EEPROM, storing the device address on I2C bus
#define DEFAULT_ADDRESS_VALUE 8   // The default device address on the I2C bus
#define EEPROM_FIRST 1            // Marks if this is the first time that the program is executed
#define TRIG 11                   // PB3 digital output; Used for triggering HC-SR04 sensor
#define ECHO 12                   // PB4 analog input; Used for reading HC-SR04 sensor
#define MAX_RANGE 200             // The minimum measured distance in cm
#define MIN_RANGE 0               // The maximum measured distance in cm
#define TIMEOUT 10000             // Timeout for the sensor reading in us
#define REFRESH_RATE 3            // The refresh rate of the sensor in seconds
#define DELAY (20*REFRESH_RATE)   // Convert time into something useful

#define DEBUG 1                   // Turns on and off Serial (or debug) text

int address;                      // The address of the device on the I2C bus
long duration = 0;                // Time between sending and receiving a response from the sensor
long distance = 0;                // Distance to the object

void requestEvent() {
  Wire.write(distance);
}

void receiveEvent(int len) {
  int x = Wire.read();
  Serial.print(F("Master sent: "));
  Serial.println(x);
  Serial.print(F("Length: "));
  Serial.println(len);
}

void setup() {
  wdt_disable();
  wdt_enable(WDTO_1S);
  
  if(DEBUG){
      Serial.begin(9600);
      Serial.print(F("Did the first time pass? "));
      Serial.println(EEPROM.read(EEPROM_FIRST));
  }
  
  if(EEPROM.read(EEPROM_FIRST) == 0){
    Wire.begin();
    for(int scan=10;scan<127;scan++){
      Wire.beginTransmission(scan);
      
      if(DEBUG){
        Serial.print(F("Checking address "));
        Serial.println(scan);
      }

      if(Wire.endTransmission() != 0){
        EEPROM.write(EEPROM_ADDRESS, scan);
        EEPROM.write(EEPROM_FIRST, 1);

        if(DEBUG){
          Serial.print(F("Found free I2C address: "));
          Serial.println(scan);
        }

        break;
      }
    }
    delay(10000);
  }else{
    address = EEPROM.read(EEPROM_ADDRESS);
    if(address<8 and address > 127){
      address = DEFAULT_ADDRESS_VALUE;
    }
    Wire.begin(address);
    Wire.onRequest(requestEvent);
    Wire.onReceive(receiveEvent);
  }

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  wdt_reset();
}

void loop() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  duration = pulseIn(ECHO, HIGH, TIMEOUT);
  distance = duration/58.2;

  if(DEBUG){
    Serial.println(distance);
  }
  
  delay(DELAY);
  wdt_reset();
}
