//analog pins 0-5 are also known as digital pins 14-19

//The following pins are used iff that particular servo is in use:
//Digitals pin 9: Servo #1 control
//Digital pin 10: Servo #2 control
#include<Servo.h>
#include <AFMotor.h>
int pins[4];
Servo s1,s2;

void setup() {
  Serial.begin(9600);
  for(int i=0; i<4;i++){
    pins[i] = i+14;
    pinMode(i+14,INPUT);
  }
  s1.attach(9);
  s2.attach(10);
  
  Serial.println("D14\tD15\tD16\tD17\n");
}
  
void loop()
{
  for(int i = 0;i<4;i++){
    Serial.print(digitalRead(pins[i]),DEC);
    Serial.print("\t");
  }
  Serial.print("\n");
  if(digitalRead(pins[2])) Serial.println("Two is ON");
  delay(15);
}
    
