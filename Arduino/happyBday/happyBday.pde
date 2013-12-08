#include<Servo.h>

#define buttonPin 7

Servo mount;

void setup(){
  // LEDs
  for (int l = 3; l <7; l++){
    pinMode(l, OUTPUT);
    digitalWrite(l,HIGH);
    delay(300);
  }

  // Button  
  pinButton(buttonPin,INPUT);
  // Enable the pull-up resistor on pin 7
  PORTD |= (1<<PD7);
  
  // Servo
  mount.attach(9);
  mount.write(0);
}

void loop(){
  if(digitalRead(buttonPin) == HIGH){
    //Birthday Party Mode
    for(int var = 0;var <=255;var++_{
      //LEDs
      
      //Servo
    }
  }
  
  // Stand-by Mode
  smoothMove(90);
  solidOff();
  delay(100);
}

void solidOff(){
  for (int i = 3;i<=7; i++){
    digitalWrite(i,LOW);
  }
}

void smoothMove(int d){
  if(d > 180){
    d = 180;}
  if(d < 0) {
    d = 0;
  }

  int cd;

  while(cd = mount.read()> d){
    mount.write(cd - 1);
    delay(15);
  }
  while(cd = mount.read() < d){
    mount.write(cd + 1);
    delay(15);
  }
}
