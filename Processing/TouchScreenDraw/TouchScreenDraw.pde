import processing.serial.*;
Serial arduino;

import stdint.h
import "TouchScreen.h"

int x,y,p,n;

void setup(){
  size(900,900);
  frameRate(32);

  println(Serial.list());
  arduino = new Serial(this,Serial.list()[0],9600);  
  arduino.bufferUntil('\n');
}

void draw(){ 
  background(255,255,255); 
  fill(p);
  ellipse(x,y,40,40);
}

void serialEvent(Serial arduino){
  n  = Integer.parseInt(trim(arduino.readStringUntil('\n')));
  p = n%1000;
  y = n%1000000 -p;
  x = (n - (y+p))/ 1000000;
}

