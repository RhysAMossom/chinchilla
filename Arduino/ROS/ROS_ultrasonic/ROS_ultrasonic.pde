/* ROS and Ping)) ultrasonic sensor
   reads from 3cm to 338cm
   publishes distance in cm to ROS

	author: Carlos Chinchilla
*/

#include <WProgram.h>
#include <ros.h>
#include <std_msgs/UInt16.h>

std_msgs::UInt16 distance_msg;
ros::Publisher pub_ultrasonic("distance", &distance_msg);
ros::NodeHandle nh;

const int pingPin = 7;// Same pin is used to write and read the signal

void setup(){
  nh.initNode();
  nh.advertise(pub_ultrasonic);
}

void loop(){
  
  pinMode(pingPin,OUTPUT); //send signal
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  pinMode(pingPin,INPUT); // read signal
  
  distance_msg.data = pulseIn(pingPin,HIGH) / 29 / 2;
  pub_ultrasonic.publish(&distance_msg); 
  nh.spinOnce();
  
  delay(100);
}
