#include <AFMotor.h>

AF_DCMotor motor(1, MOTOR12_2KHZ);
void setup() {
  Serial.begin(9600);
  Serial.println("Motor Shield Test");
  
  motor.setSpeed(100);//0 is stopped, full speed is 255;
}

void loop(){
  Serial.println("tick");
  motor.run(FORWARD);
  delay(1000);

  Serial.println("tock");
  motor.run(BACKWARD);
  delay(1000);
  
  Serial.println("tack");
  motor.run(RELEASE);// motor is stopped
  delay(1000);
}
