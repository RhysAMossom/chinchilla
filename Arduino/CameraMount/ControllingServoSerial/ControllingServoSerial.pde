#include <Servo.h>
Servo servoX, servoY;
#define servoMin 6
#define servoMax 180

/*** Incomming commands ******/
const char UP = 'u';
const char DOWN = 'd';
const char LEFT = 'l';
const char RIGHT = 'r';
const char CENTER = 'c';
const char SET_CENTER = 't';
const char COORDINATES = 'o';
const char SMOOTH_MOVE_TO = 's';
/*****************************/

// Variables
#define smoothDelay 50 // miliseconds to delay and give the effect of a smooth move
#define increment 1
int centerX = 90;
int centerY = 90;
int inMsg ,x,y;

/******* Funtions ********/
void center(){
  moveTo(centerX,centerY);
}// end center()

void moveTo(int x, int y)
{
  // Check Boundaries
  if(x > servoMax){
    x = servoMax;
    Serial.println("Out of X Bounds");
  }
  else if(x < servoMin){
    x = servoMin;
    Serial.println("Out of X Bounds");
  }
  if(y > servoMax){
    y = servoMax;
    Serial.println("Out of Y Bounds");
  }
  else if(y < servoMin){
    y = servoMin;
    Serial.println("Out of Y Bounds");
  }
  
  servoX.write(x);
  servoY.write(y);  
}// end moveTo()

void addDiag(const int x = increment, const int y = increment)
{
  moveTo(x + servoX.read(), y + servoY.read());
}// end addDiag()

void addX(const int x = increment) {
  addDiag(x,0);
}// end addX()

void addY(const int y = increment) {
  addDiag(0,y);
}// end addY()

void smoothMoveX(int x, int d = smoothDelay){
  // check boundaries
  if(x > servoMax){
    x = servoMax;
    Serial.println("Out of X Bounds");
  }
  else if(x < servoMin){
    x = servoMin;
    Serial.println("Out of X Bounds");
  }
  
  // move
  while(servoX.read() < x){
    addX(1);
    delay(d);
  }
  while(servoX.read() > x){
    addX(-1);
    delay(d);
  }
}// end smoothMoveX()

void smoothMoveY(int y, int d = smoothDelay){
  // check boundaries
  if(y > servoMax){
    y = servoMax;
    Serial.println("Out of X Bounds");
  }
  else if(y < servoMin){
    y = servoMin;
    Serial.println("Out of X Bounds");
  }
  
  // move
  while(servoY.read() < y){
    addY(1);
    delay(d);
  }
  while(servoY.read() > y){
    addY(-1);
    delay(d);
  }
}// end smoothMoveY()

void smoothMoveTo(int x, int y, int d = smoothDelay){
  // Check boundaries
  if(x > servoMax){
    x = servoMax;
    Serial.println("Out of X Bounds");
  }
  else if(x < servoMin){
    x = servoMin;
    Serial.println("Out of X Bounds");
  }
  if(y > servoMax){
    y = servoMax;
    Serial.println("Out of X Bounds");
  }
  else if(y < servoMin){
    y = servoMin;
    Serial.println("Out of X Bounds");
  }
  //move
  while(servoX.read() != x || servoY.read() != y){
    if(servoX.read() < x){ addX(1);}
    else if(servoX.read() > x){addX(-1);}

    if(servoY.read() < y){ addY(1);}
    else if(servoY.read() > y) {addY(-1);}
    delay(d);
  }
}// end smoothMoveTo()
    

// Communication
void printLocation(){
         Serial.println("Current Position\nX\tY");
         Serial.print(servoX.read());
         Serial.print("\t");
         Serial.println(servoY.read());
}// end printLocation()

// Parsing
int serialReadInt(){
 int i, serAva;                        // i is a counter, serAva hold number of serial available
 char inputBytes [7];                  // Array hold input bytes
 char * inputBytesPtr = &inputBytes[0];// Pointer to the first element of the array
     
 if (Serial.available()>0)             // Check to see if there are any serial input
 {
   delay(5);                           // Delay for terminal to finish transmitted
                                       // 5mS work great for 9600 baud (increase this number for slower baud)
   serAva = Serial.available();        // Read number of input bytes
   for (i=0; i<serAva; i++)            // Load input bytes into array
     inputBytes[i] = Serial.read();
   inputBytes[i] =  '\0';              // Put NULL character at the end
   return atoi(inputBytesPtr);         // Call atoi function and return result
 }
 else
   return -1;                          // Return -1 if there is no input
}// end SerialReadInt()

void getCoordinatesFromUser(int* X, int* Y){
  // Get X
  int& xCoor = *X;
  int& yCoor = *Y;
  
  Serial.println("Waiting for xxx coordinate");
  xCoor = serialReadInt();
  while(xCoor < 0){
    xCoor = serialReadInt();
  }
 
  // Get Y
  Serial.println("Waiting for yyy coordinate");
  yCoor = serialReadInt();
  while(yCoor < 0){
    yCoor = serialReadInt();
  }
 
  Serial.println("Received: " + (String)xCoor + " , " + (String)yCoor);
}// end getCoordinatesFromUser()

  

/*********************** ARDUINO FUNCTIONS **********************/

void setup()
{
  Serial.begin(9600);
  
  //Digital pin 10: Servo #1 control
  //Digital pin 9: Servo #2 control
  servoX.attach(10);
  servoY.attach(9);
  
  //Center Servos
  center();
  printLocation();
}// end setup()

void loop(){
  if(Serial.available() >0){
     inMsg = (char)Serial.read();
     switch((int)inMsg){
       case (int)UP:
         addY();
         Serial.println("Moving Up");
         break;
       case (int)DOWN:
         addY(-increment);
         Serial.println("Moving Down");
         break;
       case (int)CENTER:
         center();
         Serial.println("Centering");
         break;
       case (int)SET_CENTER:
         Serial.println("New Center at");
         centerX = servoX.read();
         centerY = servoY.read();
         printLocation();
         break;
       case (int)LEFT:
         addX();
         Serial.println("Moving Left");         
         break;
       case (int)RIGHT:
         addX(-increment);
         Serial.println("Moving Right");
         break;
       case (int)COORDINATES:
         Serial.println("Move To Coordinates");
         x = 0;
         y = 0;
         getCoordinatesFromUser(&x,&y);
         moveTo(x,y);
         break;
       case (int)SMOOTH_MOVE_TO:
         Serial.println("Smooth Move To Coordinates");
         x = 0;
         y = 0;
         getCoordinatesFromUser(&x,&y);
         smoothMoveTo(x,y);
         break;
       default:
         Serial.println("Unknown Command");
     }
     Serial.flush();
     printLocation();
  }
}//end loop()
