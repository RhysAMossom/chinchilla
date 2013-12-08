import processing.serial.*;

int x, y, p;
String msg;
String[] coordinates = new String[3];


void serialEvent(Serial myPort){
  msg = myPort.read();
  while(msg[msg.lentgh()-1] != 'e'){
    msg =+ myPort.read();
  }
  
  println(msg);
  
}// end serialEvent()

// -------- Processing functions --------//
void setup()
{
  size(900,900);
  smooth();
  
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600);
}// end setup()

void draw() {
 fill(p%256);
 ellipse(x,y,20,20);
}// end draww()

