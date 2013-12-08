#include <AFMotor.h>

//formula:
// t(ms) -> x (cm) : test input time
// T    -> X : desired time
// 
// T = X*t/x

AF_DCMotor mR(2, MOTOR12_2KHZ);
AF_DCMotor mL(1, MOTOR12_2KHZ);

void setup() {
  mR.setSpeed(200);//0 is stopped, full speed is 255;
  mL.setSpeed(200);//0 is stopped, full speed is 255;
}

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

void loop(){
    halt();
    delay(3000);
    forward(2000);
}
