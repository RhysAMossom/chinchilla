// Ping)) reads from 3cm to 338cm

#define pinTrigger 52// write signal
#define pinEcho 53 // receive signal

void setup(){
  Serial.begin(9600);
  pinMode(pinTrigger,OUTPUT);
  pinMode(pinEcho, INPUT);
}
  

void loop(){
  long duration, inches, cm;
  
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(5);
  digitalWrite(pinTrigger, LOW);
  
  duration = pulseIn(pinEcho,HIGH);
  //digitalWrite(pinEcho, LOW);
  
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  Serial.print(inches);
  Serial.print("in ");
  Serial.print(cm);
  Serial.println("cm");
  
  delay(100);
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 73.746 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
