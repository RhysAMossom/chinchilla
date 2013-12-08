//--------------Servo-----------
#include <Servo.h>
#define servoXpin 9
#define servoYpin 10
#define INCREMENT 5
Servo servoX, servoY; 
int centerX = 90;
int centerY = 90;

//-------------Temperature Sensor-----------
#define tempPin 0
float tempK = 0;

//--------------Charger Relay-----------
#define chargerPin 4
#define chargerLED 8
bool chargerState = LOW;

//--------------Lights Relay-----------
#define lightsPin 3
#define lightsLED 11
bool lightsState = LOW;

//--------------Fan Relay-----------
#define fanPinA 5
#define fanPinB 6
#define fanLED 7
bool fanState = LOW;

//--------------Motion Sensor-----------
#define motionPin 2

#include "commands.h"

//---------------------------------SETUP------------------------------------
void setup() {
  Serial.begin(9600);
  // Pins
  for (int i = 3; i<=8;i++)
    pinMode(i,OUTPUT);
  pinMode(11,OUTPUT);
  reset();
  // Servo
  servoX.attach(servoXpin,15,178);// for Micro Servo 9g goes from 15 to 178 degrees
  servoY.attach(servoYpin,15,178);

}// end setup()

void reset(){
  servoX.write(centerX);
  servoY.write(centerY);
  digitalWrite(chargerPin, LOW);
  digitalWrite(lightsPin,LOW);
  digitalWrite(fanPinA,HIGH);
  digitalWrite(fanPinB,LOW);
  digitalWrite(fanLED, fanState = LOW);
  digitalWrite(lightsLED,lightsState = digitalRead(lightsPin));
  digitalWrite(chargerLED,chargerState = digitalRead(chargerPin));
}

//---------------------------------LOOP------------------------------------
void loop(){
  if (Serial.available()) {
        char inCommand = Serial.read();
        Serial.print("Received: ");
        if (inCommand == RESET){
            reset();
            //Serial.print(RESET);
            Serial.println("Reset Complete");
        }
        else if(inCommand == CHARGER_OFF){
            digitalWrite(chargerPin, LOW);  
            digitalWrite(chargerLED,chargerState = digitalRead(chargerPin));
            Serial.println("Charger Off");
        }
        else if(inCommand == CHARGER_ON){
            digitalWrite(chargerPin, HIGH);  
            digitalWrite(chargerLED,chargerState = digitalRead(chargerPin));
            Serial.println("Charger On");
        }
        else if(inCommand == LIGHTS_OFF){
            digitalWrite(lightsPin, LOW);
            delay(500);  
            digitalWrite(lightsLED,lightsState = digitalRead(lightsPin));
            Serial.print("Lights Off");
        }
        else if(inCommand == LIGHTS_ON){
            digitalWrite(lightsPin, HIGH);
            delay(500);  
            digitalWrite(lightsLED,lightsState = digitalRead(lightsPin));
            Serial.println("Lights On");
        }
       else if(inCommand == FAN_OFF){
            digitalWrite(fanPinA,HIGH);
            digitalWrite(fanPinB,LOW);
            digitalWrite(fanLED,fanState = LOW);
            Serial.println("Fan Off");
       }
       else if(inCommand == FAN_ON){
            digitalWrite(fanPinA,LOW);
            digitalWrite(fanPinB,HIGH);
            digitalWrite(fanLED,fanState = HIGH);
            Serial.println("Fan On");
       }
       else if(inCommand == CAM_UP){
            servoY.write(servoY.read() + INCREMENT);
            Serial.print("X: ");
            Serial.print(servoX.read());
            Serial.print(" Y: ");
            Serial.println(servoY.read());
       }
       else if(inCommand == CAM_DOWN){
            servoY.write(servoY.read() - INCREMENT);
            Serial.print("X: ");
            Serial.print(servoX.read());
            Serial.print(" Y: ");
            Serial.println(servoY.read());
       }
       else if(inCommand == CAM_LEFT){
            servoX.write(servoX.read() - INCREMENT);
            Serial.print("X: ");
            Serial.print(servoX.read());
            Serial.print(" Y: ");
            Serial.println(servoY.read());
       }
       else if(inCommand == CAM_RIGHT){
            servoX.write(servoX.read() + INCREMENT);
            Serial.print("X: ");
            Serial.print(servoX.read());
            Serial.print(" Y: ");
            Serial.println(servoY.read());
       }
       else if(inCommand == CAM_CENTER){
            servoX.write(centerX);
            servoY.write(centerY);
            Serial.print("Centered at X: ");
            Serial.print(servoX.read());
            Serial.print(" Y: ");
            Serial.println(servoY.read());
       }
       else if(inCommand == CAM_SET_CENTER){
            centerX = servoX.read();
            centerY = servoY.read();
            Serial.print("Set center to X: ");
            Serial.print(servoX.read());
            Serial.print(" Y: ");
            Serial.println(servoY.read());
       }
       else if(inCommand == GET_STATES){
            if (lightsState = digitalRead(lightsPin))
              Serial.println("Lights On");
            else
              Serial.println("Lights Off");
            if(chargerState = digitalRead(chargerPin))
              Serial.println("Charger On");
            else
              Serial.println("Charger Off");
            if(fanState)
              Serial.println("Fan On");
            else
              Serial.println("Fan Off");
            Serial.print("Temperature (Kelvin) ");
            Serial.println(tempK = analogRead(0) * 0.004882812 * 100);
        }
        else if(inCommand == GET_TEMP){
            Serial.print("Temperature (Kelvin) ");
            Serial.println(tempK = analogRead(0) * 0.004882812 * 100);
            Serial.print("Temperature (Celsius) ");
            Serial.println(tempK - 2.5 - 273.15);  
            //temp_in_celsius = temp_in_kelvin - 2.5 - 273.15 ;
            //temp_in_fahrenheit = ((temp_in_kelvin - 2.5) * 9 / 5) - 459.67;
        }
        else
            Serial.println("Wrong command");
      }// end if(Serial.available)
      
      // Motion Detection
      if (digitalRead(motionPin)) {
        delay(5000); // see if movement is consistent over a moment
        if(digitalRead(motionPin)){
          Serial.print(MOVEMENT_DETECTED);
        }
      }
}// end loop()
