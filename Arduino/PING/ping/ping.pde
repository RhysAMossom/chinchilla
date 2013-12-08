// Ping)) reads from 3cm to 338cm

const int pingPin = 48;// Same pin is used to write and read the signal

void setup(){
  Serial.begin(9600);
}

void loop(){
  float duration, inches, cm;
  
  pinMode(pingPin,OUTPUT); //send signal
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  pinMode(pingPin,INPUT); // read signal
  duration = pulseIn(pingPin,HIGH)+0.0;
  
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  Serial.print(inches);
  Serial.print("in ");
  Serial.print(cm);
  Serial.println("cm");
  
  delay(100);
}

float microsecondsToInches(float microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 73.746 / 2.0;
}

float microsecondsToCentimeters(float microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2.0;
}
