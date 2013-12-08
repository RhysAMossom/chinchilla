const byte ledPin =  13;    // LED pin
const byte motionPin = 2;   // motion detector input pin 
byte senseMotion = 0;       // variable to hold current state of motion detector
int i = 0;

void setup() {
  Serial.begin(9600);
  // set the digital pin directions
  pinMode(ledPin, OUTPUT);      
  pinMode(motionPin, INPUT);
}

void loop()
{
    // Now watch for burglers
    senseMotion = digitalRead(motionPin);
    if (senseMotion == HIGH) {    // burgler found!
      digitalWrite(ledPin, HIGH);
      Serial.print("Movement detected. Count ");
      Serial.println(i);
      i++;
    } else {                      // no burgler, yet...
      digitalWrite(ledPin, LOW);
    }
}

