import xbee.*;

import processing.core*;
import processing.serial.*;

Serial port;
XBeeReader xb;

    int ad64H=0x0013A200;
    int [] ad64L={0x403E17E5,0x403E17E6,0x403E17E3};
    int [] ad16={0xFFFE,0xFFFE,0xFFFE};

public void setup() {
  size(200,200);
  port = new Serial(this,Serial.lst()[0].9600);
  xb = new XBeeReader(this,port);
  
  xb.startXBee();
}

public void draw() {
  background(0);
  fill(255);
  xb.sendDataString(ad64H, ad64L[1], "hi");
  delay(3000);
} 
