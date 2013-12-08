/* ROS and Camera Mount - Control Two Servos
  subscribes to a node that publishes X and Y coordinates
  and makes servoX and servoY move to their respective position.

	author: Carlos Chinchilla
*/

#include <WProgram.h>
#include <Servo.h>
#include <ros.h>
#include <std_msgs/UInt16.h>

/*********************** SERVO FUNCTIONS *************************/

// Servo Libraries
#include <Servo.h>
Servo servoX, servoY;
#define servoMin 6
#define servoMax 180

// Servo Variables
#define smoothDelay 30 // miliseconds to delay and give the effect of a smooth move
#define increment 1
int centerX = 90;
int centerY = 90;

// Servo Functions
void center(){
  moveTo(centerX,centerY);
}// end center()

void moveTo(int x, int y)
{
  // Check Boundaries
  if(x > servoMax){
    x = servoMax;
  }
  else if(x < servoMin){
    x = servoMin;
  }
  if(y > servoMax){
    y = servoMax;
  }
  else if(y < servoMin){
    y = servoMin;
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
  }
  else if(x < servoMin){
    x = servoMin;
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
  }
  else if(y < servoMin){
    y = servoMin;
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
  }
  else if(x < servoMin){
    x = servoMin;
  }
  if(y > servoMax){
    y = servoMax;
  }
  else if(y < servoMin){
    y = servoMin;
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

/*********************** ROS FUNCTIONS **************************/

ROS_CALLBACK(servo_cbX, std_msgs::UInt16, cmd_msgX)  
  smoothMoveX(cmd_msgX.data,100);
}

ROS_CALLBACK(servo_cbY, std_msgs::UInt16, cmd_msgY)
  smoothMoveY(cmd_msgY.data);
}

ros::NodeHandle nh;
ros::Subscriber subX("servoX", &cmd_msgX, servo_cbX);
ros::Subscriber subY("servoY", &cmd_msgY, servo_cbY);

/*********************** ARDUINO FUNCTIONS **********************/

void setup(){
  nh.initNode();
  nh.subscribe(subX);
  nh.subscribe(subY);
  
  servoX.attach(9);
  servoY.attach(10);
  center();
}


void loop(){
  nh.spinOnce();
  delay(1);

}//end loop()
