#include <NewSoftSerial.h>

// Use pin #2 as the RX and pin #3 as the TX
NewSoftSerial mySerial =  NewSoftSerial(52, 53);


void setup()  {
  Serial.begin(9600);
  Serial.println("Goodnight moon!");
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");
  pinMode(13,OUTPUT);
}

void loop(){

  if (mySerial.available()) {
      Serial.print((char)mySerial.read());
      digitalWrite(13,LOW);
  }
  if (Serial.available()) {
    digitalWrite(13,HIGH);
      mySerial.print((char)Serial.read());
  }
  delay(100);
}
