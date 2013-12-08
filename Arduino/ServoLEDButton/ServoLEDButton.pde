#include <Servo.h>

Servo miServo; // for Micro Servo 9g
int miServoPin = 11, potentiometerPin = 5, valuePotentiometer; // for Micro Servo 9g
int brightness = 0, fadeAmount = 5, LEDpin = 6; //LED
int buttonON, buttonPin = 2; // Button

void setup()
{
  Serial.begin(9600);
  pinMode(LEDpin,OUTPUT); // LED
  pinMode(buttonPin,INPUT); // Button
  miServo.attach(miServoPin); // Micro Servo 9g
}

void loop()
{
  
  Serial.print("Servo is at \t");
  valuePotentiometer = map(analogRead(potentiometerPin), 0, 1023, 0, 179);
  Serial.print(valuePotentiometer,DEC);
  Serial.print("\t degrees.\n");
  
  while(valuePotentiometer < 20)
  {
    Serial.print("\nOut of Bounds\tLED is fading.\n");
    
    while(buttonON == 0){
      analogWrite(LEDpin,brightness);
      brightness = brightness + fadeAmount;
  
      if (brightness == 0 || brightness == 255)
        fadeAmount = -fadeAmount;
      delay(15);
      buttonON = digitalRead(buttonPin);
    }

    valuePotentiometer = map(analogRead(potentiometerPin), 0, 1023, 0, 179);
  }
  analogWrite(LEDpin,brightness = 0);
  miServo.write(valuePotentiometer);
  buttonON = digitalRead(buttonPin);
}
