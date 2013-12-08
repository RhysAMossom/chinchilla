const int LEDpin = 9;

void setup()
{
  Serial.begin(9600);
  pinMode(LEDpin,OUTPUT);
}

void loop()
{
  byte brightness;
  if (Serial.available()){
    brightness = Serial.read();
    analogWrite(LEDpin,brightness);
  }
}

