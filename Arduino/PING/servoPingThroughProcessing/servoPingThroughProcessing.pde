#include <Servo.h>
Servo servo; // for Micro Servo 9g goes from 15 to 178 degrees

const int pingPin = 14;// Same pin is used to write and read the signal
const int servoPin = 10;
bool repeat = true;
int d [163];
void setup(){
  Serial.begin(9600);
  servo.attach(servoPin);

  moveTo(15);
  delay(1000);
}

void loop(){
  if(repeat){
    for (int i = 0; i<178-15; i++)
    {
      d[i] = getCentimeters();
      Serial.println(d[i]);
      addDeg(1);
//      while(Serial.read() != 0){}
      delay(10);
        
    }
    repeat = false;
  }
}

void moveTo(int x)
{
  if(x>178)
    x=178;
  else if(x<15)
    x=15;  
  servo.write(x);
}
void addDeg(int x)
{
  moveTo(x+servo.read());
}

int getCentimeters()
{
  // Ping)) reads from 3cm to 338cm
  pinMode(pingPin,OUTPUT); //send signal
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  pinMode(pingPin,INPUT); // read signal
  return pulseIn(pingPin,HIGH) / 29 / 2;
}

