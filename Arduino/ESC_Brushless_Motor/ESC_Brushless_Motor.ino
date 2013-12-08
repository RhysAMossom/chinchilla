#include <Servo.h>
Servo ESC;

void setup(){
  Serial.begin(9600);
  ESC.attach(9);


  Serial.println("Initializing speed controller");
  ESC.write(160); 
  delay(5000);
  ESC.write(10); // initialization of speed controller
  delay(5000);
  Serial.println("Writing 19 to ESC");
  ESC.write(19);
  // Turn on slowly
  for(int i = 50; i < 56; i++){
    ESC.write(i);
    delay(50);
  }
}

void loop(){
  int old_val = 0;
  int val = map(analogRead(0),0,1023,40,90);
  if (val != old_val){
    Serial.print("Writing to ESC val = ");
    Serial.println(val);
    ESC.write(val); //almost the highest possible speed
  }
  old_val = val;
  delay(1000);
}
