int brightness = 0, fadeAmount = 5, LEDpin = 9;

void setup()
{
  pinMode(LEDpin,OUTPUT);
}

void loop()
{
  analogWrite(LEDpin,brightness);
  brightness = brightness + fadeAmount;
  
  if (brightness == 0 || brightness == 255)
  fadeAmount = -fadeAmount;
  
  delay(30);
}
