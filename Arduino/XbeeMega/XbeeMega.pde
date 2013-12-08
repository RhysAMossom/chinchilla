void setup()  {
  Serial.begin(9600);
  Serial.println("Goodnight moon!");
  // set the data rate for the SoftwareSerial port
  Serial2.begin(9600);
  Serial2.println("Hello, world?");
  pinMode(13,OUTPUT);
}

void loop(){

  if (Serial2.available()) {
      Serial.print((char)Serial2.read());
      digitalWrite(13,LOW);
  }
  if (Serial.available()) {
    digitalWrite(13,HIGH);
      Serial2.print((char)Serial.read());
  }
  delay(100);
}
