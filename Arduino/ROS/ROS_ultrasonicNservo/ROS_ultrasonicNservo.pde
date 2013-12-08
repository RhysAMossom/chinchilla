/* ROS and Ping)) ultrasonic sensor
   reads from 3cm to 338cm
   publishes distance in cm to ROS while a servo sweeps sensor
   just like a radar

	author: Carlos Chinchilla
*/

#include <WProgram.h>
#include <ros.h>
#include <arduinoNros/arduinoNros_msgs.h>

arduinoNros::arduinoNros_msgs radar_msg;
ros::Publisher pub_radar("radar", &radar_msg);
ros::NodeHandle nh;

const int pingPin = 7;// Same pin is used to write and read the signal

#include <Servo.h>

Servo servo;
int inc = 10;

void setup(){
  nh.initNode();
  nh.advertise(pub_radar);

  servo.attach(9);
  
  radar_msg.degree = 0;
}

void loop(){
  pinMode(pingPin,OUTPUT); //send signal
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin,INPUT); // read signal
  
  radar_msg.distance = pulseIn(pingPin,HIGH) / 29 / 2;
  
  servo.write(radar_msg.degree);
  if(radar_msg.degree >=180 ){
    inc = -inc;
  }
  else if(radar_msg.degree <= 0){
    inc = 10;
  }
  radar_msg.degree += inc;
  
  pub_radar.publish(&radar_msg); 
  nh.spinOnce();
  
  delay(100);
}
