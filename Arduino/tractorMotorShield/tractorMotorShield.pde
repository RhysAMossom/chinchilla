#include <AFMotor.h>
bool l = true;

AF_DCMotor mR(1, MOTOR12_2KHZ);
AF_DCMotor mL(2, MOTOR12_2KHZ);
void setup() {
  mR.setSpeed(110);//0 is stopped, full speed is 255;
  mL.setSpeed(110);//0 is stopped, full speed is 255;
  
  pinMode(14,INPUT);//bumper detects front collision
}

void back(){
    mR.run(BACKWARD);
    mL.run(BACKWARD);
  delay(1000);
}

void right(int d){
    mL.run(FORWARD);
    mR.run(BACKWARD);
  delay(d);
}
  
void left(int d){  
    mR.run(FORWARD);
    mL.run(BACKWARD);
  delay(d);
}

void halt(){
  mR.run(RELEASE);// motor is stopped
  mL.run(RELEASE);// motor is stopped
}

void loop(){
    if(digitalRead(14) == HIGH)
    {    
      halt();
      back();
      if (l)
      {
       left(2300);
       l = false;
      }
      else
      {
        right(2300);
        l = true;
      }
    }
    mR.run(FORWARD);
    mL.run(FORWARD);
    delay(10);
}
