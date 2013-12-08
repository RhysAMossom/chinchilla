// Motorshield and Servo Libraries
#include <AFMotor.h>
#include <Servo.h>

// Motors and Servo
AF_DCMotor mR(1, MOTOR12_2KHZ);
AF_DCMotor mL(2, MOTOR12_2KHZ);
#define motorSpeed 120//0 is stopped, full speed is 255;
Servo radar;
#define center 96
const int numDegreesSides = 4; // number of readings on the sides
const int arrayDegreesSides[] = {2,30,160, 180};
const int numDegreesFront = 3; // number of readings on the front
const int arrayDegreesFront[] = {75,center,115};

// Ping Sensor
#define pinTrigger 52// write signal
#define pinEcho 53 // receive signal

// Distance Variables
#define backMS 200 // miliseconds to back up before turning
#define turnMS 920 // miliseconds it takes to do a 90 degree turn (about 950ms for 90 degrees at motor speed 120)
#define addition2cf 1 // controls how close the vehicle should get to the obstacle
int cf;// conversion factor ms/cm
#define clearance 20 // cm of distance between obstacle and front of vehicle when stopped
long arrayDistancesSides[numDegreesSides];
long arrayDistancesFront[numDegreesFront];

// Thinking LED: turned on when calculations are made
#define ledPin 14


// Functions for moving
void forward(long d){
    mR.run(FORWARD);
    mL.run(FORWARD);
    delay(d);
}

void back(int d = 500){
    mL.run(BACKWARD);
    mR.run(BACKWARD);
  delay(d);
}

void right(int d = turnMS){
    mR.run(BACKWARD);
    mL.run(FORWARD);
  delay(d);
}
  
void left(int d = turnMS){  
    mR.run(FORWARD);
    mL.run(BACKWARD);
  delay(d);
}

void halt(){
    mR.run(RELEASE);// motor is stopped
    mL.run(RELEASE);// motor is stopped
}


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
}

int calibrate(long time = 1000) {
  int cf = -1;
  while(cf<20 || cf >45){
    Serial.println("Calibrating...");
    halt();
    long d1,d2, difference;
    radar.write(center);
    delay(15);
    // warm up
    getDistance();
    
    // Get first distance, move, get second distance.
    delay(1000);
    d1 = getDistance();
    Serial.println("\tFirst Reading\n\t");
    Serial.print(d1);
    delay(1000);
    forward(time);
    halt();
    delay(1000);
    d2 = getDistance();
    Serial.println("\tSecond Reading");
    Serial.println(d2);
    
    // Compute difference and calculate the conversion factor
    difference = d1-d2;
    difference = abs(difference);
    Serial.println("\tDifference");
    Serial.println(difference);
    
    int cfA , cfB;
    cf = time/difference;
    Serial.print("Conversion Factor is: \t");
    Serial.println(cf);

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
}

// Main functions
void setup() {
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT); // Thinking LED
  digitalWrite(ledPin, HIGH); // Turn Thinking LED On
  
  mR.setSpeed(motorSpeed);//0 is stopped, full speed is 255;
  mL.setSpeed(motorSpeed);
  
  radar.attach(10);
  radar.write(center);
  
  pinMode(pinTrigger,OUTPUT);
  pinMode(pinEcho, INPUT);
  
  cf = calibrate(); // conversion factor
  Serial.println("Done with Setup\n");
  delay(500);
  digitalWrite(ledPin, LOW); // Turn Thinking LED Off
}

void loop(){
   // Get front readings
     for(int i = 0; i<numDegreesFront; i++){
       radar.write(arrayDegreesFront[i]);
       delay(1000);
       arrayDistancesFront[i] = getDistance();
       Serial.print("Degree ");
       Serial.print(arrayDegreesFront[i]);
       Serial.print(" measures ");
       Serial.println(arrayDistancesFront[i]);
       delay(500);
     }
    
   digitalWrite(ledPin, HIGH); // Turn Thinking LED On
   
   //Distance Front is the smallest distance measured in the front
   long dF = min(arrayDistancesFront[0],min(arrayDistancesFront[1],arrayDistancesFront[2]));
   Serial.print("\nSmallest front distance measured is: ");
   Serial.println(dF);
   // lastDistanceForward keeps track of the last forward distanced moved
   long lastDistanceForward = 0;
   
   // Going Forward
   if (dF > clearance){
     Serial.print("Want to move ");
     Serial.print(dF);
     Serial.print(" cm.\nMoving for ");
     lastDistanceForward = (dF-clearance)*cf;
     Serial.print(lastDistanceForward);
     Serial.println(" sec.");
     digitalWrite(ledPin, LOW); // Turn Thinking LED Off
     forward(lastDistanceForward);
     halt();
     Serial.println("Stopped");
   }
   else // Choose where to turn
     Serial.println("Distance is less than clearance.\n Choosing path...");
     
     // Get side readings
     for(int i = 0; i<numDegreesSides; i++){
       radar.write(arrayDegreesSides[i]);
       delay(1000);
       arrayDistancesSides[i] = getDistance();
       Serial.print("Degree ");
       Serial.print(arrayDegreesSides[i]);
       Serial.print(" measures ");
       Serial.println(arrayDistancesSides[i]);
       delay(500);
     }
     
     digitalWrite(ledPin, HIGH); // Turn Thinking LED On
     // Detect side objects
     if (abs(arrayDistancesSides[0]-arrayDistancesSides[1]) > 10){
       Serial.print("Odd reading on degrees ");
       Serial.print(arrayDegreesSides[0]);
       Serial.print(" and ");
       Serial.println(arrayDegreesSides[1]);
     }
     if (abs(arrayDistancesSides[2]-arrayDistancesSides[3]) > 10){
       Serial.print("Odd reading on degrees ");
       Serial.print(arrayDegreesSides[2]);
       Serial.print(" and ");
       Serial.println(arrayDegreesSides[3]);
     }
     
     // Compare readings. Left side corresponds to degrees < 90
     long dR, dL;
     dR = min(arrayDistancesSides[2],arrayDistancesSides[3]);
     dL = min(arrayDistancesSides[0],arrayDistancesSides[1]);
     Serial.print("dR is: ");
     Serial.print(dR);
     Serial.print("\tdL is: ");
     Serial.println(dL);
     
     digitalWrite(ledPin, LOW); // Turn Thinking LED Off
     
     // Turn 90 degrees. Turning right is the default move
     if (dR >= dL && dR > clearance){
       Serial.println("Turning Right");
       back(backMS);
       halt();
       delay(500);
       right();
       halt();
     }
     else if(dL> dR && dL > clearance){
       Serial.println("Turning Left");
       back(backMS);
       halt();
       delay(500);
       left();
       halt();
     }
     else { // For cases: (dR,dL) < clearance
       if (lastDistanceForward > 0){
         Serial.println("Backing up");
         back(lastDistanceForward);// back up last distance moved forward
         halt();
       }
       else{
         Serial.println("Turning around"); //180 degrees
         back(backMS);
         halt();
         delay(500);
         right();
         right();
         halt();
       }
     }
}
