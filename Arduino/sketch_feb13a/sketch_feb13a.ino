#define Out1 7
#define Out2 6
#define en12 4
#define PotPin 0

boolean fp = false;
#define th 2// accuracy threshold
#define t 10 // time (ms) to move motor before next reading

  
void forward(int d = 1000){
  Serial.println("forward");
  digitalWrite(en12,LOW);
  digitalWrite(Out1,HIGH);
  digitalWrite(Out2,LOW);
  digitalWrite(en12,HIGH);
  delay(d);
}

void backward(int d = 1000){
  Serial.println("backward");
  digitalWrite(en12,LOW);
  digitalWrite(Out2,HIGH);
  digitalWrite(Out1,LOW);
  digitalWrite(en12,HIGH);
  delay(d);
}

void halt(int d = 1000){
  Serial.println("halt");
  digitalWrite(en12,LOW);
  digitalWrite(Out1,HIGH);
  digitalWrite(Out2,HIGH);
  digitalWrite(en12,HIGH);
  delay(d);
}

void neutral(int d = 1000){
  Serial.println("neutral");
  digitalWrite(en12,LOW);
  delay(d);
}

void moveTo(int p){
  int val = analogRead(PotPin);
  while(p - th > val || val > p + th){
    if(val < p){
      if(fp){
        do{
          forward(t);
          Serial.println(val=analogRead(PotPin));
        }while (val < p);
      }
      else{
        do{
          backward(t);
          Serial.println(val=analogRead(PotPin));
        }while (val < p);
      }
    }
    else { // if (val < p)
      if(fp){
        do{
          backward(t);
          Serial.println(val=analogRead(PotPin));
        }while (val > p);
      }
      else{
        do{
          forward(t);
          Serial.println(val=analogRead(PotPin));
        }while (val > p);
      }
    }
  }
  halt(1);
}

/*********************************/
void setup(){
  Serial.begin(9600);
  pinMode(Out1,OUTPUT);
  pinMode(Out2,OUTPUT);
  pinMode(en12,OUTPUT);
  int v = analogRead(PotPin);
  forward(10);
  if (analogRead(PotPin) > v)
    fp = true;//forward is positive
}

void loop(){
  Serial.println("\n\nMoving to 10");
  moveTo(10);
}


/* TODO: 
* put moveTo in interrupts
* moveTo() must be solid 1kHZ 
* make moveTo() as fast as possible
* use state machines
*/
