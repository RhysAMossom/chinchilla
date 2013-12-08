/*
Whit.e is a semi-autonomous robot (vehicle) based on the arduino boards.
This code is made to demonsrtate the robot's features of detecting obstacles.

The robot will first calibrate its ultrasonic sensor and sync with its wheels.
Then it will measure the distance to the next object in front and travel
that distance up to a clearance space. Then it will measure and compare the 
distances to the next object to the left and right. The robot will turn to the side
with the smallest distance measured.

Author: Carlos A. Chinchilla

*/
// Motorshield and Servo Libraries
#include <AFMotor.h>
#include <Servo.h>

// Motors
AF_DCMotor mR(1, MOTOR12_2KHZ);
AF_DCMotor mL(2, MOTOR12_2KHZ);
#define motorSpeed 120//0 is stopped, full speed is 255;

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

// ---------------- Communication Functions
void sendMsg(String msg){
  Serial.println(msg);
  Serial2.println(msg);
}// end sendMsg()

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

  //Center Servos
  radar.write(radarCenter);
  
  // Ultrasonit Sensor
  pinMode(pinTrigger,OUTPUT);
  pinMode(pinEcho, INPUT);
  
  // Calibration
  cf = calibrate(); // conversion factor
  sendMsg("...and done with Setup\n");
  delay(1000);
}// end setup()

void loop(){
// ------------------ AUTONOMOUS MODE DEMO ----------------------//
       
       // Get front readings
       sendMsg("Reading front");
       for(int i = 0; i<numDegreesFront; i++){
         radar.write(arrayDegreesFront[i]);
         delay(1000);
         arrayDistancesFront[i] = getDistance();
         sendMsg("Degree " + (String)arrayDegreesFront[i] + " measures " + (String)arrayDistancesFront[i]);
         delay(500);
       }
       
       //Distance Front is the smallest distance measured in the front
       long dF = min(arrayDistancesFront[0], min(arrayDistancesFront[1], arrayDistancesFront[2]));
       sendMsg("Smallest front distance: " + dF);
       // lastDistanceForward keeps track of the last forward distanced moved
       long lastDistanceForward = 0;
       
       // Going Forward
       if (dF > clearance){
         sendMsg("I Want to move " + (String)dF + " cm.");
         
         lastDistanceForward = (dF-clearance)*cf;
         sendMsg("Moving for " + (String)lastDistanceForward + " seconds.");
         forward(lastDistanceForward);
         halt();
         sendMsg("AHH! almost crashed there.");
       }
       else // Choose where to turn
         sendMsg("I am too close, let me turn around.");
         
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
             sendMsg("Beep! Beep! Backing up");
             back(lastDistanceForward);// back up last distance moved forward
             halt();
           }
           else{
             sendMsg("Spin halfway with me."); //180 degrees
             back(backMS);
             halt();
             delay(500);
             right();
             right();
             halt();
           }
         }
}// end loop()
