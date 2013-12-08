// Wireless E-Stop Button

#include <NewSoftSerial.h>

// Use pin #2 as the RX and pin #3 as the TX
NewSoftSerial xb =  NewSoftSerial(2, 3);

/* Define states *** do not modify *******/
const char ESTOP = 'e';// activates Emergency Stop
const char EGO = 'g'; // deactivates Emergency Stop
//****************************************/

// Indicator LEDs
#define red 9
#define green 8
#define yellow 10
#define buttonPin 14

void setup(){
  xb.begin(9600);
  
  // Initialize LEDs
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(yellow,OUTPUT);
  
  digitalWrite(red,HIGH);
  digitalWrite(green,HIGH);
  digitalWrite(yellow,HIGH);
  delay(2000);
  digitalWrite(red,LOW);
  digitalWrite(green,LOW);
//  digitalWrite(yellow,LOW);

  //Button
  pinMode(buttonPin,INPUT);
}

void loop(){
  //Check Button State
  if (digitalRead(buttonPin) == HIGH){
    // Send STOP message
    for(int i = 0; i<3;i++){
      xb.print(ESTOP);
      delay(100);
    }
    // Turn red light ON
    digitalWrite(red,HIGH);
    digitalWrite(green,LOW);

    // Wait for button to be OFF
    while(digitalRead(buttonPin) == HIGH){
      //checkMsg();
      delay(100);
    }
    // Send GO message
    for(int i = 0; i<3;i++){
      xb.print(EGO);
      delay(100);
    }
  }
  else{
    // turn green light OFF
    digitalWrite(red,LOW);
    digitalWrite(green,HIGH);
  }
}
