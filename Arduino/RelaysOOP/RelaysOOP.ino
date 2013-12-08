class Relay {
  public:
    Relay(int pin);
    void On();
    void Off();
    void Toggle();
    boolean GetState();
  private:
    int _pin;
};

Relay::Relay(int pin){
  _pin = pin;
  pinMode(_pin, OUTPUT);
}

void Relay::On(){
  digitalWrite(_pin, HIGH);
}

void Relay::Off(){
  digitalWrite(_pin, LOW);
}

void Relay::Toggle(){
  digitalRead(_pin) ? digitalWrite(_pin, LOW) : digitalWrite(_pin, HIGH);
}

boolean Relay::GetState(){
  return digitalRead(_pin);
}

  Relay relay1(10);
  Relay relay2(11);

void setup(){
  Serial.begin(9600);
  Serial.println("Relays initialized");
}

void loop(){
  if(Serial.available() >0){
    char c = Serial.read();
    Serial.print("Received: ");
    Serial.println(c);
    switch(c){
      case 't':
        Serial.println("Toggling");
        relay1.Toggle();
        relay2.Toggle();
        break;
      case 'o':    
        Serial.println("On");
        relay1.On();
        relay2.On();
        break;
      case 'n':
        Serial.println("Off");
        relay1.Off();
        relay2.Off();
        break;
      default:
        Serial.println("Unknown command");
      Serial.flush();
    }
    Serial.print("Relay1: ");
    Serial.println(relay1.GetState());
    Serial.print("Relay2: ");
    Serial.println(relay2.GetState());
     
  }
}
  
