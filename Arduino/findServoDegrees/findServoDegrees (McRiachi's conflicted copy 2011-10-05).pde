#include <Servo.h>

Servo myServo;

const int servoPin = 48; // 9 is servo2 in motorshield

void setup(){
  Serial.begin(9600);
  myServo.attach(servoPin);
  
}

void loop(){
  myServo.write(0);
  for (int i = 170;i<=180;i+=1){
  Serial.println(i);
  delay(2000);
  myServo.write(i);
  delay(10);


   }
}

