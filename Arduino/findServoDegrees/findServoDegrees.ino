#include <Servo.h>

Servo myServo;

const int servoPin = 10; // 9 is servo2 in motorshield

void setup(){
  Serial.begin(9600);
  myServo.attach(servoPin);
  
}

void loop(){
  for (int i = 0;i<180;i+=1){
    Serial.println(i);
    myServo.write(i);
    delay(10);
  }
}

