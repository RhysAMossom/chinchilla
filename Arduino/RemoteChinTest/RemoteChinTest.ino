#include "commands.h"
int pin = 4; 
int pinLED = 8;
int pin1 = 3;
int pinLED1 = 9;
int pinA = 5;
int pinB = 6;
bool state = LOW;
bool stateAB = LOW;

//---------------------------------SETUP------------------------------------
void setup() {
  Serial.begin(9600);
  for (int i = 3; i<=9;i++)
    pinMode(i,OUTPUT);
    
  digitalWrite(pinLED, HIGH);
  digitalWrite(pinLED1,HIGH);
  digitalWrite(7,HIGH);
  delay(1000);
  digitalWrite(pinLED,LOW);
  digitalWrite(pinLED1, LOW);
  digitalWrite(7,LOW);
}// end setup()

//---------------------------------LOOP------------------------------------
void loop(){
  if (Serial.available()) {
        char inCommand = Serial.read();
        Serial.print("I received: ");
        Serial.println(inCommand);
        if (inCommand == RESET){
            digitalWrite(pin, LOW);
            digitalWrite(pin1,LOW);
            digitalWrite(pinA,HIGH);
            digitalWrite(pinB,LOW);
            state = digitalRead(pin);
            digitalWrite(pinLED,state);
            digitalWrite(pinLED1,state);
            stateAB = LOW;
            delay(500);
            digitalWrite(pinA,LOW);
            digitalWrite(7,stateAB);
            Serial.println("Reset");
        }
        else if(inCommand == LIGHTS_OFF){
            digitalWrite(pin, LOW);  
            state = digitalRead(pin);
            digitalWrite(pinLED,state);
            Serial.println(state);
        }
        else if(inCommand == LIGHTS_ON){
            digitalWrite(pin, HIGH);  
            state = digitalRead(pin);
            digitalWrite(pinLED,state);
            Serial.println(state);
        }
        else if(inCommand == FAN_OFF){
            digitalWrite(pin1, LOW);  
            state = digitalRead(pin1);
            digitalWrite(pinLED1,state);
            Serial.println(state);
        }
        else if(inCommand == FAN_ON){
            digitalWrite(pin1, HIGH);  
            state = digitalRead(pin1);
            digitalWrite(pinLED1,state);
            Serial.println(state);
        }
       else if(inCommand == CHARGER_OFF){
            digitalWrite(pinA,HIGH);
            digitalWrite(pinB,LOW);
            stateAB = LOW;
            digitalWrite(7,stateAB);
            Serial.println(stateAB);
            delay(500);
            digitalWrite(pinA,LOW);
       }
       else if(inCommand == CHARGER_ON){
            digitalWrite(pinA,LOW);
            digitalWrite(pinB,HIGH);
            stateAB = HIGH;
            digitalWrite(7,stateAB);
            Serial.println(stateAB);
            delay(500);
            digitalWrite(stateAB,LOW);
       }
       Serial.flush();
      }// end if(Serial.available)
}// end loop()
