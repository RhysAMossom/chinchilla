#include <AFMotor.h>
#include <Servo.h>

AF_DCMotor mTraction(1, MOTOR12_2KHZ);
AF_DCMotor mSteering(2, MOTOR12_2KHZ);
Servo radar;

const int pingRadar = 14, pingFront = 15;// Same pin is used to write and read the signal
const int cF = 30; //conversion factor: if Speed is 200, around 8.89cm per second
//formula:
// t(ms) -> x (cm) : test input time
// T    -> X : desired time
// 
// T = X*t/x

const int pinPing = 15;

void setup() {
  Serial.begin(9600);
  mTraction.setSpeed(200);//0 is stopped, full speed is 255;
  mSteering.setSpeed(200);//0 is stopped, full speed is 255;
  radar.attach(10);
  getDistance();
  delay(2000);
}


long getDistance(){
  long duration, distance;
  
  pinMode(pingPin,OUTPUT); //send signal
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  pinMode(pingPin,INPUT); // read signal
  duration = pulseIn(pingPin,HIGH);
  distance = duration / 29 / 2;
  Serial.println(distance);
  return distance;
}

void loop(){
    radar.write(92); // Move servo to point to the front
    delay(500);
  
    long distance = getDistance();
    delay(1000);
    if (distance >= 5){
      mTraction.run(FORWARD);
      delay(2000);
      mTraction.run(RELEASE);
    }
    int dL,dR; // left and right distances
    radar.write(10);
    delay(1000);
    dL = getDistance();
    
    radar.write(170);
    delay(1000);
    dR = getDistance();
}
