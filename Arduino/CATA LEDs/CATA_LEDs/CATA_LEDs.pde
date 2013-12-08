/* Make CATA LEDs blink and flash according to IGVC rules:

Safety Light:  The vehicle must have an easily viewed solid indicator light which is turned on 
whenever the vehicle power is turned on.  The light must go from solid to flashing whenever 
the vehicle is in autonomous mode.  As soon as the vehicle comes out of autonomous mode 
the light must go back to solid. 
*/

void setup()
{
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

void blinkAlternate(int dOn =1000){
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

void blinkAlternate2(int dOn =1000){
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

void blinkHalf(int dOn = 1000){
  solidOff();
  for(int i =3; i<=8; i++)
    digitalWrite(i,HIGH);
  
  delay(dOn);
  solidOff();
  
  
  for(int i =9; i<=13; i++)
    digitalWrite(i,HIGH);
  delay(dOn);
}

void blinkAll(int dOn = 1000, int dOff = 1000){
  solidOn();
  delay(dOn);
  solidOff();
  delay(dOff);
}

void chase(int dOn = 100)
{
  for (int i = 3; i<=13; i++){
    digitalWrite(i, HIGH);   
    delay(dOn);                
    digitalWrite(i, LOW);                  
  }
}

void chase2(int dOn = 100){
  for (int i = 3; i<=13; i++){
    digitalWrite(i, HIGH);   
    delay(dOn);                             
  }
   for (int i = 3; i<=13; i++){
    digitalWrite(i, LOW);   
    delay(dOn);                             
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

void loop(){
  int r = 10;
  for(int i = 0;i<r;i++)
      chase();
  for(int i = 0;i<r;i++)
    chase2();
  for(int i = 0;i<r;i++)
    solidOn();
  solidOff();
  delay(1000);
  for(int i = 0;i<r;i++)
    blinkAlternate();
  for(int i = 0;i<r;i++)
    blinkAlternate2();
  for(int i = 0;i<r;i++)
    blinkHalf();
  for(int i = 0; i<10*r; i++)
    chase(10);
  for(int i = 0;i<r;i++)
    fade();  
   
  delay(5000);
}
