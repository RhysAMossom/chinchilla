//Processing code:
import processing.serial.*;
Serial port;
void setup(){
  size(256,150);
  println("Available Serial Ports: ");
  println(Serial.list());
  //port = new Serial(this,Serial.list()[0], 9600);
  port = new Serial(this,"/dev/tty.usbmodem411",9600);
}

void draw() {
  for (int i = 0; i < 256; i++){
    stroke(i);
    line(i,0,i,150);
  }
  port.write(mouseX);
}
