/* 
Reads Serial-sent messages to toggle mode of safety light flashing
and activates relay that controls Wireless EStop according to data
sent by XBee.
Make CATA LEDs blink and flash according to IGVC rules:

Safety Light:  The vehicle must have an easily viewed solid indicator light which is turned on 
whenever the vehicle power is turned on.  The light must go from solid to flashing whenever 
the vehicle is in autonomous mode.  As soon as the vehicle comes out of autonomous mode 
the light must go back to solid.

Wireless E-Stop:
Must bring the vehicle to a complete stop when activating a button from
a distance of 100 feet away.
*/

// XBee items for Wireless E-Stop
#include <NewSoftSerial.h>
#define xbRX 15
#define xbTX 16
NewSoftSerial xb =  NewSoftSerial(xbRX, xbTX);
#define relayPin 14

/* Define states *** do not modify *******/
const char AUTONOMOUS = 'a';
const char RADIO_CONTROLLED = 'r';
const char STAND_BY = 's';
const char OFF = 'o';

const char ESTOP = 'e';// activates Emergency Stop
const char EGO = 'g'; // deactivates Emergency Stop
/*****************************************/
char inCommand = STAND_BY; // for incoming serial data
char newCommand = inCommand;

// variable to change mode of blinking
int bM = 0;

void setup() {
  Serial.begin(9600);// open serial port, sets data rate to 9600 bps

  // Initialize XBee Wireless E-Stop Items
  xb.begin(9600);
  pinMode(A0,OUTPUT);
    
  // Initialize LEDs
  for (int i =3; i<=13;i++){
        pinMode(i, OUTPUT);
  }
}


void solidOn(){
  for (int i = 3;i<=13; i++){
    digitalWrite(i,HIGH);
  }
}
void solidOnAlternate(){
  for (int i = 3;i<=13; i+=2){
    digitalWrite(i,HIGH);
  }
}

void solidOff(){
  for (int i = 3;i<=13; i++){
    digitalWrite(i,LOW);
  }
}

void blinkAlternate(int dOn =1000, int r = 1){
  for (int h = 0; h < r; h++){
  	solidOff();
  	for(int i =3; i<=13; i+=2)
  	{
	    digitalWrite(i,HIGH);
  	}
  	delay(dOn);
  	solidOff();
  
  	for(int i =4; i<=13; i+=2)
  	{
    	digitalWrite(i,HIGH);
  	}
  	delay(dOn);
  }
}

void blinkAlternate2(int dOn =1000, int r = 1){
  for (int h = 0; h < r; h++){
  	solidOff();
  	for(int i =3; i<=13; i+=2)
  	{
    	digitalWrite(i,HIGH);
  	}
  	delay(dOn);
  
  	for(int i =4; i<=13; i+=2)
  	{
    	digitalWrite(i,HIGH);
  	}
  	delay(dOn);
  	for(int i =3; i<=13; i+=2)
  	{
  	  digitalWrite(i,LOW);
  	}
  	delay(dOn);
  	solidOff();
  	delay(dOn);
  }
}

void blinkHalf(int dOn = 1000, int r = 1){
  for (int h = 0; h < r; h++){
  	solidOff();
  	for(int i =3; i<=8; i++){
    	digitalWrite(i,HIGH);
    }
 	delay(dOn);
  	solidOff();
  
  	for(int i =9; i<=13; i++){
    	digitalWrite(i,HIGH);
 	}
 	delay(dOn);
  }
}

void blinkAll(int dOn = 1000, int dOff = 1000, int r = 1){
  for (int h = 0; h < r; h++){
  	solidOn();
  	delay(dOn);
  	solidOff();
  	delay(dOff);
  }
}

void chase(int dOn = 100, int r = 1){
  for (int h = 0; h < r; h++){
	for (int i = 3; i<=13; i++){
    	digitalWrite(i, HIGH);   
    	delay(dOn);                
    	digitalWrite(i, LOW);                  
  	}
  }
}

void chase2(int dOn = 100, int r = 1){
  for (int h = 0; h < r; h++){
  	for (int i = 3; i<=13; i++){
    	digitalWrite(i, HIGH);   
    	delay(dOn);                             
  	}
   	for (int i = 3; i<=13; i++){
    	digitalWrite(i, LOW);   
    	delay(dOn);                             
  	}
  }
}

void fade(int dFade = 30, int r = 1){
        int fadeAmount = 5;
       	int brightness = 0;
    for (int h = 0; h < r; h++){
        solidOff();
        int r = 255/fadeAmount*2; 
	for(int i = 0; i<=r; i++){
		analogWrite(5,brightness);
                analogWrite(6,brightness);
                analogWrite(10,brightness);
                analogWrite(11,brightness);
  
		brightness += fadeAmount;
		if (brightness == 0 || brightness == 255){
			fadeAmount = -fadeAmount;
		}
		delay(dFade);
	}
    }
}
void error(int dOn = 100,int dOff = 100, int r = 1){
  for (int i = 0; i<r; i++){
    int p = random(3,13);
    digitalWrite(p,HIGH);
    delay(dOn);
    digitalWrite(p,LOW);
    delay(dOff);
  }
}

void loop() {
  if(xb.available() > 0){
      if(xb.read() == ESTOP){
      // Activate E-Stop
      digitalWrite(relayPin,HIGH);
      blinkHalf();
      for(int i = 0; i<3; i++){
        xb.print(ESTOP);
      }
    
      //Wait for GO Message
      while(true){
        if(xb.available() > 0) {
          if(xb.read() == EGO){
            for(int i = 0; i<3; i++){
              xb.print(EGO);
            }
            break;
          }
        }
      }
      // Deactivate E-Stopee
      digitalWrite(relayPin,LOW);
    }   
    // Read the incoming message
    else if(Serial.available() > 0) {
    newCommand = Serial.read();
    
   // Compare old message with new message
        if (inCommand != newCommand){
          solidOff();
          inCommand = newCommand;
          bM = ++bM%6;
        }
    }
  }
  
  // set Flashing mode
  if (inCommand == AUTONOMOUS){
    switch(bM){// choose from the blinking functions declared above
      case 0:  
        blinkAlternate(500);
        break;
      case 1:
        blinkAll(500);
        break;
      case 2:
        chase();
        break;
      case 3:
        chase2();
        break;
      case 4:
        blinkAlternate2();
        break;
      default:
        chase(15);
    }
        
  }
  else if (inCommand == RADIO_CONTROLLED){
      solidOn();
  }
  else if (inCommand == STAND_BY){
    fade();
  }
  else if (inCommand == OFF){
    solidOff();
  }  
  else {// No communication or unrecognized inCommand
    solidOff();
    error();
    solidOff();
  }
}
