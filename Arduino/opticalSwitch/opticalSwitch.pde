int opticalSwitchPin = 2;
int valOpticalSwitch;

void setup(){
  Serial.begin(9600);
  pinMode(opticalSwitchPin,INPUT);
 // pinMode(8,OUTPUT);
}

void loop(){
  
 // digitalWrite(8,HIGH);
  valOpticalSwitch = analogRead(opticalSwitchPin);
  Serial.println(valOpticalSwitch,DEC);
 // digitalWrite(8,LOW);
  
  /*
  valOpticalSwitch = digitalRead(opticalSwitchPin);
  if(valOpticalSwitch == HIGH)
    Serial.println("H");
  else
    Serial.println("L");*/
    
  delay(15);
}
