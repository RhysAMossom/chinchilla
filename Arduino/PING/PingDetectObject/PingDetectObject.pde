#include <Servo.h>
Servo servo;

const int pingPin = 14; // Ping)) reads from 3cm to 338cm
const int servoPin = 10; //for servo1 in motorShield
int maxDegree = 175, minDegree = 15, degree;
bool repeat = true;
int duration, cm, distance;

void setup(){
  Serial.begin(9600);
  degree = minDegree;
  servo.attach(servoPin);
}

void loop(){
  if (repeat){
  
  pinMode(pingPin,OUTPUT); //send signal
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin,INPUT); // read signal
  duration = pulseIn(pingPin,HIGH);
  distance = duration/29/2;

  Serial.println(distance);
  if (degree <maxDegree){
    degree+= 10;
    servo.write(degree);
  }
  else{
    Serial.println("done");
    repeat = false;
  }
  }
  delay(1000);
  
}
