//--------------Charger Relay-----------
#define chargerPinA 5
#define chargerPinB 6
#define chargerLED 7
bool chargerState = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(chargerPinA,OUTPUT);
  pinMode(chargerPinB,OUTPUT);
  pinMode(chargerLED,OUTPUT);
}// end setup()

void loop(){
    Serial.println("Charger Off");
    digitalWrite(chargerPinA,HIGH);
    digitalWrite(chargerPinB,LOW);
    digitalWrite(chargerLED, LOW);
    //Serial.print(chargerState);
    //delay(500);
    //digitalWrite(chargerPinA,LOW);
    //Serial.print(CHARGER_OFF);
    
    delay(5000);
    
    
    Serial.println("Charger On");
    digitalWrite(chargerPinA, LOW);
    digitalWrite(chargerPinB, HIGH);
    digitalWrite(chargerLED, HIGH);
    //Serial.println(chargerLED);
    //delay(500);
    //digitalWrite(chargerPinB,LOW);
    //Serial.println(CHARGER_ON);
    delay(5000);
 
}// end loop()
