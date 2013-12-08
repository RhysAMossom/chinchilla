void setup() {
Serial.begin(9600);
pinMode(12,OUTPUT);
}

void loop() {
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue, DEC);
  if (sensorValue > 400){
    digitalWrite(12,HIGH);}
   else{
      digitalWrite(12,LOW);}
}
