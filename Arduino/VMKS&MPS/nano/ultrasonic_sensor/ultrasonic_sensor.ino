#define VCC  10  //D4, +5V
#define TRIG 11 //D5, digital output
#define ECHO 12 //D6, analog input
//#define GND   //D7, GND
#define PWM  3  // test pin

int maximumRange = 200;
int minimumRange = 0;
long duration, distance;

void setup() {
  Serial.begin (9600);
  pinMode(VCC,  OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT );
//  pinMode(GND,  OUTPUT);

  digitalWrite(VCC,  HIGH);
  digitalWrite(TRIG, LOW );
//  digitalWrite(GND,  LOW );
  analogWrite(PWM, 150);
}

void loop() { 
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH);
  
  //Calculate the distance (in cm) based on the speed of sound.
  distance = duration/58.2;
  
  if (distance >= maximumRange || distance <= minimumRange){
    Serial.println("-1");
  }
  else {
    Serial.println(distance);
  }
  
  delay(100);
}
