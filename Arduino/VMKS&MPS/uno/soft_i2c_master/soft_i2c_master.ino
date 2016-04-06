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
    pinMode(SCL, OUTPUT);
    pinMode(SDA, OUTPUT);
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
    delayMicroseconds(clock_);
  }

  bool wait_ACK(){  
    pinMode(SDA_, INPUT);
    delayMicroseconds(clock_/2);
    digitalWrite(SCL_, HIGH);
    delayMicroseconds(clock_/2);
    bool ack = digitalRead(SDA_);
    delayMicroseconds(clock_/2);
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
    for(uint8_t i=0; i<7;i++){
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
    for(uint8_t i=0; i<7;i++){
      digitalWrite(SDA_, (B&b));
      b = b >> 1;
      // Remove print later
      Serial.println(B&b);
      delayMicroseconds(clock_/2);
      digitalWrite(SCL_, HIGH);
      delayMicroseconds(clock_);
      digitalWrite(SCL_, LOW);
      delayMicroseconds(clock_/2);
    }
  }

  uint8_t recieve_byte(){
    uint8_t result = 0;
    pinMode(SDA_, INPUT);
    for(uint8_t i=0; i<8; i++){
      result = result<<1;
      delayMicroseconds(clock_/2);
      digitalWrite(SCL_, HIGH);
      delayMicroseconds(clock_/2);
      result = result&digitalRead(SDA_);
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
    stop();
    return result;
  }

  void sendData(uint8_t adr, uint8_t data){
    start();
    send_address(adr);
    send_bit(0);
    if(wait_ACK()){
      //resend if needed
      stop();
    }
    send_byte(data);
    if(wait_ACK()){
      //resend if needed
      stop();
    }
    stop();
  }

  uint8_t recieveData(uint8_t adr){
    start();
    send_address(adr);
    send_bit(1);
    if(wait_ACK()){
      //resend if needed
      stop();
    }
    recieve_byte();
    if(wait_ACK()){
      //resend if needed
      stop();
    }
  }
};

i2c bus = i2c(4, 5);

void setup() {
  bus.init(CLOCK_PIN, DATA_PIN);
  Serial.begin(9600);
}

void loop() {
  uint8_t data = 15;
  for(uint8_t i=START_ADDRESS; i<MAX_ADDRESS; i++){
    if (bus.checkSlave(i)){
      Serial.print(F("There is a device on: ")); 
      Serial.println(i);
      Serial.print(F("Sending data ")); 
      Serial.print(data);
      Serial.print(F(" to device "));
      Serial.println(i);
      
      bus.sendData(i, data);
/*  
      uint8_t result = bus.recieveData(i);
  
      Serial.print(F("Recieved data ")); 
      Serial.print(result);
      Serial.print(F(" from device "));
      Serial.println(i);
*/
    }else{
      Serial.print(F("There is no device on: ")); 
      Serial.println(i);
    }
  }
}
