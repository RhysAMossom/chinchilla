/* LED Strip Madness
Author: Carlos Chinchilla
November 2013
*/

int LEDS[] = {2,3,4,5,6,7,8,9,10,11,12,13};// R1,G1,B1, ..., RN,GN,BN
int RED_LEDS[] = {2,5,8,11};
int GREEN_LEDS[] = {3,6,9,12};
int BLUE_LEDS[] = {4,7,10,13};
int NUM_LEDS = sizeof(LEDS)/sizeof(LEDS[0]);
int NUM_RED_LEDS = sizeof(RED_LEDS)/sizeof(RED_LEDS[0]);
int NUM_GREEN_LEDS = sizeof(GREEN_LEDS)/sizeof(GREEN_LEDS[0]);
int NUM_BLUE_LEDS = sizeof(BLUE_LEDS)/sizeof(BLUE_LEDS[0]);

// PING
const int pingFront = 14;// Same pin is used to write and read the signal
const int pinTrigger = 15;// write signal
const int pinEcho = 16; // receive signal

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



// BASICS
void groupAnalogWrite(const int *leds,int num_leds, int value){
  for(int l=0; l < num_leds;l++){
    analogWrite(leds[l], value);
  }
}  

void all_off(){
  for(int i =0; i < NUM_LEDS; i++){
    analogWrite(LEDS[i],0);
  }
}

void all_on(){
  for(int i =0; i < NUM_LEDS; i++){
    analogWrite(LEDS[i],255);
  }
}

void color_on(int* leds, int num_leds){
  groupAnalogWrite(leds,num_leds,255);
}

void color_off(int* leds, int num_leds){
  groupAnalogWrite(leds,num_leds,0);
}

  
void one_on_all_off(int led){
  all_off();
  analogWrite(led,255);
}

void one_off_all_on(int led){
  all_on();
  analogWrite(led,0);
}

void rgb(int red, int green, int blue){
  groupAnalogWrite(RED_LEDS, NUM_RED_LEDS, red);
  groupAnalogWrite(GREEN_LEDS, NUM_GREEN_LEDS, green);
  groupAnalogWrite(BLUE_LEDS, NUM_BLUE_LEDS, blue);
}

// EFFECTS

void fade_all(int time_on=10, int time_off=10)  {
 // Requires enough current to drive all LEDs 
  all_off();
// FADE IN
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) {
    groupAnalogWrite(BLUE_LEDS, NUM_BLUE_LEDS, fadeValue);
//    delay(time_on);      
    for(int  fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
      groupAnalogWrite(RED_LEDS, NUM_RED_LEDS, fadeValue);
//      delay(time_on);  
      for(int  fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
        groupAnalogWrite(GREEN_LEDS, NUM_GREEN_LEDS, fadeValue);
         delay(time_on);  
      }
    }                                
  } 

// FADE OUT
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue -=5) {
    groupAnalogWrite(BLUE_LEDS, NUM_BLUE_LEDS, fadeValue);
//    delay(time_off);      
    for(int  fadeValue = 0 ; fadeValue <= 255; fadeValue -=5) { 
      groupAnalogWrite(RED_LEDS, NUM_RED_LEDS, fadeValue);
//      delay(time_off);  
      for(int  fadeValue = 0 ; fadeValue <= 255; fadeValue -=5) { 
        groupAnalogWrite(GREEN_LEDS, NUM_GREEN_LEDS, fadeValue);
         delay(time_off);  
      }
    }                                
  }
}

void flash_each_strip_each_color(int time_on=10, int time_off=0){
  // When wait_time is very small, the eye sees the 3 colors at the same time
  for(int i =0; i < NUM_LEDS; i++){
    analogWrite(LEDS[i],255);
    delay(time_on);
    analogWrite(LEDS[i],0);
    delay(time_off);
  }
}

void flash_all_strips_each_color(int time_on=100, int time_off=0){
  color_on(BLUE_LEDS, NUM_BLUE_LEDS);
  delay(time_on);
  color_off(BLUE_LEDS, NUM_BLUE_LEDS);
  delay(time_off);
  color_on(RED_LEDS, NUM_RED_LEDS);
  delay(time_on);
  color_off(RED_LEDS, NUM_RED_LEDS);
  delay(time_off);
  color_on(GREEN_LEDS, NUM_GREEN_LEDS);
  delay(time_on);
  color_off(GREEN_LEDS, NUM_GREEN_LEDS);
  delay(time_off);
}

void flash_and_bar(int time_on=200){
  for(int f = 0; f< NUM_LEDS; f++){
    flash_each_strip_each_color();
    one_on_all_off(LEDS[f]);
    delay(time_on);
  }
}




// ARDUINO FUNCTIONS
void setup()  {
  Serial.begin(9600);
  pinMode(pinTrigger,OUTPUT);
  pinMode(pinEcho, INPUT);
  Serial.println("Parallax Ping\t\tChinese Ping");
  
} 

void loop() {
//  rgb();
  flash_all_strips_each_color();
//  flash_each_strip_each_color();
//  flash_and_bar();
/*
  long inches1, inches2;
  
  inches1 = getDuration(pingFront);//microsecondsToInches(getDuration(pingFront));
//  cm1 = microsecondsToCentimeters(getDuration(pingFront));
  inches2 = getDuration(pinTrigger, pinEcho);//microsecondsToInches(getDuration(pinTrigger, pinEcho));
//  cm2 = microsecondsToCentimeters(getDuration(pinTrigger, pinEcho));
  
  Serial.print(inches1);
  Serial.print("\t\t");
  Serial.println(inches2);
  flash_all_strips_each_color(map(inches1,0,1000,0,255),100);
  //delay(100);
 */
}


