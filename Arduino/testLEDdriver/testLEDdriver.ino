// outputs
#define   VPRG_pin 2
const char VPRG = 'v';
static bool VPRG_state = true;
#define SIN_pin 3
const char SIN = 's';
static bool SIN_state = false;
#define SCLK_pin 4
const char SCLK = 'c';
static bool SCLK_state = true;
#define XLAT_pin 5
const char XLAT = 'x';
static bool XLAT_state = false;
#define BLANK_pin 6
const char BLANK ='b';
static bool BLANK_state = false;
#define DCPRG_pin 7
const char DCPRG = 'd';
static bool DCPRG_state = false;
#define GSCLK_pin 8
const char GSCLK = 'g';
static bool GSCLK_state = true;

// inputs
#define SOUT_pin 9
static int SOUT_state = 0;
#define XERR_pin 10
static int XERR_state = 0;

char in_command;

void setup(){
  // outputs
  pinMode(VPRG_pin, OUTPUT);
  pinMode(SIN_pin, OUTPUT);
  pinMode(SCLK_pin, OUTPUT);
  pinMode(XLAT_pin, OUTPUT);
  pinMode(BLANK_pin, OUTPUT);
  pinMode(DCPRG_pin, OUTPUT);
  pinMode(GSCLK_pin, OUTPUT);
  
  // inputs
  pinMode(SOUT_pin, INPUT);  
  pinMode(XERR_pin, INPUT);
  
  Serial.begin(9600);
}

void loop(){
  if (Serial.available()){
     in_command = Serial.read();
     Serial.print("received: ");
     Serial.println(in_command);
     switch((int)in_command){
       case (int)VPRG:
         VPRG_state = ! VPRG_state;
         digitalWrite(VPRG_pin,VPRG_state); 
         break;
       case (int)SIN:
         SIN_state = ! SIN_state;
         digitalWrite(SIN_pin,SIN_state);
         break;
       case (int)SCLK:
         SCLK_state = ! SCLK_state;
         digitalWrite(SCLK_pin,SCLK_state);
         break;
       case (int)XLAT:
         XLAT_state = ! XLAT_state;
         digitalWrite(XLAT_pin,XLAT_state);
         break;
       case (int)BLANK:
         BLANK_state = ! BLANK_state;
         digitalWrite(BLANK_pin,BLANK_state);
         break;
       case (int)DCPRG:
         DCPRG_state = ! DCPRG_state;
         digitalWrite(DCPRG_pin,DCPRG_state);
         break;
       case (int)GSCLK:
         GSCLK_state = ! GSCLK_state;
         digitalWrite(GSCLK_pin,GSCLK_state);
         break;
       default:
         Serial.println("Unknown command.");
       } 
  Serial.println("VPRG\tSIN\tSCLK\tXLAT\tBLANK\tDCPRG\tGSCLK\tSOUT\tXERR");
  Serial.print(VPRG_state);
  Serial.print("\t");
  Serial.print(SIN_state);
  Serial.print("\t");
  Serial.print(SCLK_state);
  Serial.print("\t");
  Serial.print(XLAT_state);
  Serial.print("\t");
  Serial.print(BLANK_state);
  Serial.print("\t");
  Serial.print(DCPRG_state);
  Serial.print("\t");
  Serial.print(GSCLK_state);
  
  SOUT_state = digitalRead(SOUT_pin);
  XERR_state = digitalRead(XERR_pin);
  
  Serial.print("\t");
  Serial.print(SOUT_state);
  Serial.print("\t");
  Serial.println(XERR_state);
  }
  delay(1000);
}
     
