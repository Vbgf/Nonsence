#define TRIG 11 //D5, digital output
#define ECHO 12 //D6, analog input
#define TIMEOUT 10000

int maximumRange = 200;
int minimumRange = 0;
long duration, distance;

void setup() {
  Serial.begin (9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT );
  digitalWrite(TRIG, LOW );
}

void loop() { 
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH, TIMEOUT);
  
  //Calculate the distance (in cm) based on the speed of sound.
  distance = duration/58.2;
  
  if (distance >= maximumRange || distance <= minimumRange){
    Serial.println("-1");
  }
  else {
    Serial.println(distance);
  }
  
  //delay(100);
}
