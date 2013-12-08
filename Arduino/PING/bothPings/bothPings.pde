// Ping)) reads from 3cm to 338cm


const int pingFront = 14;// Same pin is used to write and read the signal
const int pinTrigger = 15;// write signal
const int pinEcho = 16; // receive signal

void setup(){
  Serial.begin(9600);
  pinMode(pinTrigger,OUTPUT);
  pinMode(pinEcho, INPUT);
  Serial.println("Parallax Ping\t\tChinese Ping");
}
  

long getDuration(int pinTrigger, int pinEcho){
  long duration;
  
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(5);
  digitalWrite(pinTrigger, LOW);
  duration = pulseIn(pinEcho,HIGH);
  //digitalWrite(pinEcho, LOW);
  return duration;
}

long getDuration(int pingPin){
  long duration;
  
  pinMode(pingPin,OUTPUT); //send signal
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  pinMode(pingPin,INPUT); // read signal
  duration = pulseIn(pingPin,HIGH)+0.0;
  
  return duration;
}

void loop(){
  long inches1,cm1, inches2,cm2;
  
  inches1 = microsecondsToInches(getDuration(pingFront));
  cm1 = microsecondsToCentimeters(getDuration(pingFront));
  inches2 = microsecondsToInches(getDuration(pinTrigger, pinEcho));
  cm2 = microsecondsToCentimeters(getDuration(pinTrigger, pinEcho));
  
  Serial.print(inches1);
  Serial.print("in ");
  Serial.print(cm1);
  Serial.print("cm\t\t");
  Serial.print(inches2);
  Serial.print("in ");
  Serial.print(cm2);
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
