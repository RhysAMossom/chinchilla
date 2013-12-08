#include <AFMotor.h>

AF_DCMotor mR(1, MOTOR12_2KHZ);
AF_DCMotor mL(2, MOTOR12_2KHZ);
#define motorSpeed 120//0 is stopped, full speed is 255;

#define turnMS 1800 //number of miliseconds it takes to do a 90 degree turn

// Functions for moving
void forward(long d){
    mR.run(FORWARD);
    mL.run(FORWARD);
    delay(d);
}

void back(int d){
    mR.run(BACKWARD);
    mL.run(BACKWARD);
  delay(d);
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

void setup() {
  mR.setSpeed(motorSpeed);//0 is stopped, full speed is 255;
  mL.setSpeed(motorSpeed);
}

void loop(){
  right(turnMS);
  halt();
  delay(3000);
  left(turnMS);
  halt();
  delay(3000); 
}
