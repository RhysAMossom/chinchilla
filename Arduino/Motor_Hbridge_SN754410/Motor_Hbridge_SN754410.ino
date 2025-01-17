/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(13, OUTPUT);  
  pinMode(12,OUTPUT);  
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);               // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(200); 
  digitalWrite(12, HIGH);    // turn the LED off by making the voltage LOW
  delay(200); 
  digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
  delay(200); 
}
