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
  i2c(uint8_t SCL, uint8_t SDA, uint16_t speed = I2C_SPEED_KHZ){
    SCL_ = SCL;
    SDA_ = SDA;
    clock_ = speed/10;
  }

  void init(uint8_t SCL, uint8_t SDA){
    pinMode(SCL_, INPUT);
    pinMode(SDA_, INPUT);
    SCL_ = SCL;
    SDA_ = SDA;
    pinMode(SCL_, OUTPUT);
    pinMode(SDA_, OUTPUT);
    digitalWrite(SCL, HIGH);
    digitalWrite(SDA, HIGH);   
  }

  void start(){
    digitalWrite(SDA_, LOW);
    delayMicroseconds(clock_/2);
    digitalWrite(SCL_, LOW);
    delayMicroseconds(clock_/2);
  }

  void stop(){
    delayMicroseconds(clock_/2);
    digitalWrite(SCL_, HIGH);
    delayMicroseconds(clock_/2);
    digitalWrite(SDA_, HIGH);
    delayMicroseconds(20*clock_);
  }

  void ACK(){
    digitalWrite(SDA_, HIGH);
    delayMicroseconds(clock_/2);
    digitalWrite(SCL_, HIGH);
    delayMicroseconds(clock_);
    digitalWrite(SCL_, LOW);
    delayMicroseconds(clock_/2);
  }

  bool wait_ACK(){  
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

  void send_bit(bool b){
    digitalWrite(SDA_, b);
    delayMicroseconds(clock_/2);
    digitalWrite(SCL_, HIGH);
    delayMicroseconds(clock_);
    digitalWrite(SCL_, LOW);
    delayMicroseconds(clock_/2);
  }

  void send_address(uint8_t adr){
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

  void send_byte(uint8_t B){
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

  uint8_t recieve_byte(){
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

  bool checkSlave(uint8_t adr){
    bool result;
    start();
    send_address(adr);
    send_bit(0);
    result = wait_ACK();
    send_byte(0);
    stop();
    return result;
  }

  void sendData(uint8_t adr, uint8_t data){
    start();
    send_address(adr);
    send_bit(0);
    wait_ACK();
    send_byte(data);
    wait_ACK();
    stop();
  }

  uint8_t recieveData(uint8_t adr){
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
};

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
