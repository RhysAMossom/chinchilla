// Motorshield and Servo Libraries
#include <AFMotor.h>
#include <Servo.h>

// Motors
AF_DCMotor mR(1, MOTOR12_2KHZ);
AF_DCMotor mL(2, MOTOR12_2KHZ);
#define motorSpeed 120//0 is stopped, full speed is 255;

// Camera Variables
Servo servoX, servoY; // for Micro Servo 9g goes from 15 to 178 degrees
#define servoMin 6
#define servoMax 180
#define smoothDelay 50 // miliseconds to delay and give the effect of a smooth move
#define increment 2
int centerX = 110;//((servoMax - servoMin)/2);
int centerY = 45;//((servoMax - servoMin)/2);
bool camControl = false;
int x,y;

// Radar Servo
Servo radar;
#define pinRadar 26
#define radarCenter 96
#define numDegreesSides 4 // number of readings on the sides
const int arrayDegreesSides[] = {2,30,160, 180};
#define numDegreesFront 3 // number of readings on the front
const int arrayDegreesFront[] = {75,radarCenter,115};

// Ping Sensor
#define pinTrigger 24// write signal
#define pinEcho 25 // receive signal

// Distance Variables
#define forwardMS 500
#define backMS 500 // miliseconds to back up before turning
#define turnMS 1500 // miliseconds it takes to do a 90 degree turn (about 950ms for 90 degrees at motor speed 120)
#define addition2cf 1 // controls how close the vehicle should get to the obstacle

int cf;// conversion factor ms/cm
#define cfLowerBound 20
#define cfUpperBound 55

#define clearance 20 // cm of distance between obstacle and front of vehicle when stopped
long arrayDistancesSides[numDegreesSides];
long arrayDistancesFront[numDegreesFront];

/* Wirless Communication // *If using ArduinoMEGA, use any of the other Serial Ports instead
#include <NewSoftSerial.h>
// newSoftSerial(int RX, int TX)
NewSoftSerial xb = NewSoftSerial(50,51);*/

/************** Incomming commands *****************/
char inCommand;
// Vehicle Commands
const char AUTONOMOUS = 'a';
const char WIRELESS = 'w';
const char STOP = 'h';
const char BACK = 'b';
const char FRONT = 'f';
const char CALIBRATE = 'c';

const char LEFT = 'l';// for both vehicle and camera
const char RIGHT = 'r';// for both vehicle and camera
const char INSTRUCTIONS = 'i';// for both vehicle and camera

// Camera Commands
const char CAMERA = 'm';
const char UP = 'u';
const char DOWN = 'd';
const char CENTER = 'e';
const char SET_CENTER = 't';
const char COORDINATES = 'o';
const char SMOOTH_MOVE_TO = 's';
/****************************************************/
/**************** Instructions **********************/
const String instructionsWireless = "\nWhit.e Wireless Controls\nLetter\tFunction\n a\tAutonomous Mode\n m\tCamera Mode\n w\tWireless Mode\n h\tStop Whit.e\n b\tMove Backwards\n f\tMove Forwards\n c\tCalibrate Whit.e\n m\tCamera Mode\n l\tMove Whit.e Left\n r\tMove Whit.e Right\n i\tPrint Instructions\n";
const String instructionsCam = "\nWhit.e Camera Controls\nLetter\tFunction\n a\tAutonomous Mode\n w\tWireless Mode\n m\tCamera Mode\n e\tCenter Camera\n o\tMove Camera To Coordinates\n s\tMove Camera Smoothly To Coordinates\n u\tMove Camera Up\n d\tMove Camera Down\n l\tMove Camera Left\n r\tMove Camera Right\n i\tPrint Instructions\n";

// ---------------- Vehicle Mode  (Autonomous/Wireless Control)
bool isAuto = false;

// State functions
bool isAutonomous(){
  if (Serial2.available() && (int)Serial2.read() == (int)WIRELESS){
    return false;}
  else{
    return true;}
}// end isAutonomous()

// ---------------- Functions for moving
void forward(long d){
    mR.run(FORWARD);
    mL.run(FORWARD);
    delay(d);
}// end forward()

void back(int d = 500){
    mL.run(BACKWARD);
    mR.run(BACKWARD);
  delay(d);
}// end back()

void right(int d = turnMS){
    mR.run(BACKWARD);
    mL.run(FORWARD);
  delay(d);
}// end right()
  
void left(int d = turnMS){  
    mR.run(FORWARD);
    mL.run(BACKWARD);
  delay(d);
}// end left()

void halt(){
    mR.run(RELEASE);// motor is stopped
    mL.run(RELEASE);// motor is stopped
}// end halt()


long getDistance(){
  long duration, distance = -1;
  while (distance <0 || distance > 300)
  {
    digitalWrite(pinTrigger, LOW);
    delayMicroseconds(2);
    digitalWrite(pinTrigger, HIGH);
    delayMicroseconds(5);
    digitalWrite(pinTrigger, LOW);
    duration = pulseIn(pinEcho,HIGH)+0.0;
  //digitalWrite(pinEcho, LOW);
     distance = duration / 29 / 2;
  }
  return distance;
}// end getDistance()

int calibrate(long time = 1000) {
  int cf = -1;
  while(cf<cfLowerBound || cf >cfUpperBound){
    sendMsg("Calibrating...");
    halt();
    long d1,d2, difference;
    radar.write(radarCenter);
    delay(15);
    // warm up
    getDistance();
    
    // Get first distance, move, get second distance.
    delay(1000);
    d1 = getDistance();
    sendMsg("\tFirst Reading\n\t" + (String)d1);
    delay(1000);
    forward(time);
    halt();
    delay(1000);
    d2 = getDistance();
    sendMsg("\tSecond Reading" + (String)d2);
    
    // Compute difference and calculate the conversion factor
    difference = d1-d2;
    difference = abs(difference);
    sendMsg("\tDifference" + (String)difference);
    
    int cfA , cfB;
    cf = time/difference;
    sendMsg("Conversion Factor is: " + (String)cf);

    // Back up to initial position
    back(time);
    halt();
  }
  return cf + addition2cf;
  //formula:
  // t(ms) -> x (cm) : test input time
  // T    -> X : desired time
  // 
  // T = X*t/x = X *cf
  
  sendMsg("Calibrated, cf is " + (String)cf);
}// end calibrate()

// ---------------- Camera Servos Functions
void center(){
  moveTo(centerX,centerY);
}// end center()

void moveTo(int x, int y)
{
  // Check Boundaries
  if(x > servoMax){
    x = servoMax;
    sendMsg("Servo Out Of X Bounds");
  }
  else if(x < servoMin){
    x = servoMin;
    sendMsg("Servo Out Of X Bounds");
  }
  if(y > servoMax){
    y = servoMax;
    sendMsg("Servo Out Of Y Bounds");
  }
  else if(y < servoMin){
    y = servoMin;
    sendMsg("Servo Out Of Y Bounds");
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
    sendMsg("Servo Out Of X Bounds");
  }
  else if(x < servoMin){
    x = servoMin;
    sendMsg("Servo Out Of X Bounds");
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
    sendMsg("Servo Out Of X Bounds");
  }
  else if(y < servoMin){
    y = servoMin;
    sendMsg("Servo Out Of X Bounds");
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
    sendMsg("Servo Out Of X Bounds");
  }
  else if(x < servoMin){
    x = servoMin;
    sendMsg("Servo Out Of X Bounds");
  }
  if(y > servoMax){
    y = servoMax;
    sendMsg("Servo Out Of Y Bounds");
  }
  else if(y < servoMin){
    y = servoMin;
    sendMsg("Servo Out Of Y Bounds");
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
    

// ---------------- Communication Functions
void sendMsg(String msg){
  Serial.println(msg);
  Serial2.println(msg);
}// end sendMsg()

void printCamLocation(){
         sendMsg("Camera Current Position\nX\tY");
         sendMsg((String)servoX.read() + "\t" + (String)servoY.read());
}// end printCamLocation()

// Parsing
int serialReadInt(){
 int i, serAva;                        // i is a counter, serAva hold number of serial available
 char inputBytes [7];                  // Array hold input bytes
 char * inputBytesPtr = &inputBytes[0];// Pointer to the first element of the array
   
 if (Serial2.available()>0)             // Check to see if there are any serial input
 {
   delay(1000);                           // Delay for terminal to finish transmitted
                                       // 5mS work great for 9600 baud (increase this number for slower baud)
   serAva = Serial2.available();        // Read number of input bytes
   for (i=0; i<serAva; i++)            // Load input bytes into array
     inputBytes[i] = Serial2.read();
   inputBytes[i] =  '\0';              // Put NULL character at the end
   Serial2.flush();
   return atoi(inputBytesPtr);         // Call atoi function and return result
 }
 else
   return -1;                          // Return -1 if there is no input
}// end SerialReadInt()

void getCoordinatesFromUser(int* X, int* Y){
  // Get X
  int& xCoor = *X;
  int& yCoor = *Y;
  
  sendMsg("Waiting for xxx coordinate");
  xCoor = serialReadInt();
  while(xCoor < 0){
    xCoor = serialReadInt();
  }
 
  // Get Y
  sendMsg("Waiting for yyy coordinate");
  yCoor = serialReadInt();
  while(yCoor < 0){
    yCoor = serialReadInt();
  }
 
  sendMsg("Received: " + (String)xCoor + " , " + (String)yCoor);
}// end getCoordinatesFromUser()

//-------------------------- Arduino IDE Functions -------------------------//

void setup() {
  // USB Communication
  Serial.begin(9600);  
  // XBee Communication
  Serial2.begin(9600);
  sendMsg("Whit.e is awake!");

  // Motors
  mR.setSpeed(motorSpeed);//0 is stopped, full speed is 255;
  mL.setSpeed(motorSpeed);
  
  // Servos
  //Digital pin 10: Servo #1 control
  //Digital pin 9: Servo #2 control
  radar.attach(pinRadar);
  servoX.attach(10);
  servoY.attach(9);
  //Center Servos
  center();
  radar.write(radarCenter);
  
  // Ultrasonit Sensor
  pinMode(pinTrigger,OUTPUT);
  pinMode(pinEcho, INPUT);
  
  // Calibration
  cf =25;// calibrate(); // conversion factor
  sendMsg("...and done with Setup\n");
  sendMsg(instructionsWireless);
  delay(1000);
}// end setup()

void loop(){

// ------------------ WIRELESS MODE ----------------------// 
    while(!isAuto){
      if (Serial2.available()) {
        inCommand = Serial2.read();
        switch((int)inCommand){
          case (int)INSTRUCTIONS:
            sendMsg(instructionsWireless);
            break;
          case (int)WIRELESS:
            sendMsg("Whit.e Is In Wireless Mode");
            break;
          case (int)STOP:
            sendMsg("Stopped");  
            halt();
            break;
          case (int)LEFT:
            sendMsg("Turning Left");
            left(turnMS);  
            halt();
            break;
          case (int)RIGHT:
            sendMsg("Turning Right");
            right(turnMS);            
            halt();
            break;
          case (int)FRONT:
            sendMsg("Moving Forwards");
            forward(forwardMS);
            halt();
            break;
          case (int)BACK:
            sendMsg("Moving Backwards");
            back(backMS);
            halt();
            break;
          case (int)CALIBRATE:
            cf = calibrate();
            break;
          case (int)AUTONOMOUS:
            sendMsg("Stopped\nWireless Mode Off.\nGoing into Autonomous Mode.");
            halt();
            isAuto = true;
            break;
          case (int)CAMERA:
          /***** Camera Mode ******/
              halt();
              camControl = true;
              sendMsg("Camera Mode ON");
              sendMsg(instructionsCam);
              Serial2.flush();
              while(camControl){
                if (Serial2.available()) {
                  inCommand = Serial2.read();
                  switch((int)inCommand){
                    case (int)INSTRUCTIONS:
                       sendMsg(instructionsCam);
                       break;
                    case (int)CAMERA:
                       sendMsg("Whit.e Is In Camera Mode");
                       break;
                    case (int)UP:
                       addY();
                       sendMsg("Camera Moving Up");
                       break;
                     case (int)DOWN:
                       addY(-increment);
                       sendMsg("Camera Moving Down");
                       break;
                     case (int)CENTER:
                       center();
                       sendMsg("Centering Camera");
                       break;
                     case (int)SET_CENTER:
                       Serial.println("New Center at");
                       centerX = servoX.read();
                       centerY = servoY.read();
                       printCamLocation();
                       break;
                     case (int)LEFT:
                       addX();
                       sendMsg("Camera Moving Left");         
                       break;
                     case (int)RIGHT:
                       addX(-increment);
                       sendMsg("Camera Moving Right");
                       break;
                     case (int)COORDINATES:
                       sendMsg("Move Camera To Coordinates");
                       x = 0;
                       y = 0;
                       getCoordinatesFromUser(&x,&y);
                       moveTo(x,y);
                       break;
                     case (int)SMOOTH_MOVE_TO:
                       sendMsg("Camera Smooth Move To Coordinates");
                       x = 0;
                       y = 0;
                       getCoordinatesFromUser(&x,&y);
                       smoothMoveTo(x,y);
                       break;
                      case (int)WIRELESS:
                        sendMsg("Camera Mode Off.\nGoing into Wireless Mode");
                        camControl = false;
                        isAuto = false;
                        break;
                      case (int)AUTONOMOUS:
                        sendMsg("Camera Mode Off.\nGoing into Autonomous Mode");
                        camControl = false;
                        isAuto = true;
                        break;
                      default:
                        sendMsg("Camera Mode: Unknown Command");
                  }// end switch(inCommand)
                }// end if(Serial2.available)
             }// end while(camControl)
             break;
           default:
             sendMsg("Wireless Mode: Unknown Command");
        }//end switch(inCommand)
      }// end if(Serial2.available)
    }//end while(!isAuto)
    
// ------------------ AUTONOMOUS MODE ----------------------//
    while(isAuto){ 
       // Check for Autonomous Escape Command 
      if (!(isAuto = isAutonomous())){ 
         sendMsg("Autnomous Mode OFF");
         break;
       }
       sendMsg("Autonomous Mode ON");       
       
       // Get front readings
       for(int i = 0; i<numDegreesFront; i++){
         radar.write(arrayDegreesFront[i]);
         delay(1000);
         arrayDistancesFront[i] = getDistance();
         sendMsg("Degree " + (String)arrayDegreesFront[i] + " measures " + (String)arrayDistancesFront[i]);
         delay(500);
       }

       // Check for Autonomous Escape Command 
       if (!(isAuto = isAutonomous())){ 
         sendMsg("Autnomous Mode OFF");
         break;
       }       
       
       //Distance Front is the smallest distance measured in the front
       long dF = min(arrayDistancesFront[0], min(arrayDistancesFront[1], arrayDistancesFront[2]));
       sendMsg("Smallest front distance measured is: " + dF);
       // lastDistanceForward keeps track of the last forward distanced moved
       long lastDistanceForward = 0;
       
       // Going Forward
       if (dF > clearance){
         sendMsg("Want to move " + (String)dF + " cm.");
         
         lastDistanceForward = (dF-clearance)*cf;
         sendMsg("Moving for " + (String)lastDistanceForward + " sec.");
         forward(lastDistanceForward);
         halt();
         sendMsg("Stopped");
       }
       else // Choose where to turn
         sendMsg("Distance is less than clearance.\n Choosing path...");
         
         // Get side readings
         for(int i = 0; i<numDegreesSides; i++){
           radar.write(arrayDegreesSides[i]);
           delay(1000);
           arrayDistancesSides[i] = getDistance();
           sendMsg("Degree " + (String)arrayDegreesSides[i] + " measures " + (String)arrayDistancesSides[i]);
           delay(500);
         }
         
         // Detect side objects
         if (abs(arrayDistancesSides[0]-arrayDistancesSides[1]) > 10){
           sendMsg("Odd reading on degrees " + (String)arrayDegreesSides[0] + " and " + (String)arrayDegreesSides[1]);
         }
         if (abs(arrayDistancesSides[2]-arrayDistancesSides[3]) > 10){
           sendMsg("Odd reading on degrees "+ (String)arrayDegreesSides[2] + " and " + (String)arrayDegreesSides[3]);
         }
         
         // Compare readings. Left side corresponds to degrees < 90
         long dR, dL;
         dR = min(arrayDistancesSides[2],arrayDistancesSides[3]);
         dL = min(arrayDistancesSides[0],arrayDistancesSides[1]);
         sendMsg("dR is: " + (String)dR + "\tdL is: " + (String)dL);
         
         // Turn 90 degrees. Turning right is the default move
         if (dR >= dL && dR > clearance){
           sendMsg("Turning Right");
           back(backMS);
           halt();
           delay(500);
           right();
           halt();
         }
         else if(dL> dR && dL > clearance){
           sendMsg("Turning Left");
           back(backMS);
           halt();
           delay(500);
           left();
           halt();
         }
         else { // For cases: (dR,dL) < clearance
           if (lastDistanceForward > 0){
             sendMsg("Backing up");
             back(lastDistanceForward);// back up last distance moved forward
             halt();
           }
           else{
             sendMsg("Turning around"); //180 degrees
             back(backMS);
             halt();
             delay(500);
             right();
             right();
             halt();
           }
         }
    }// end while(isAuto)
    sendMsg("Autonomous Mode Off.\nGoing into Wireless Mode.");
    isAuto = false;
}// end loop()
