/*
  Servo Control and Push Botton
   Subscribe to servo commands and publish
   state of a push button.
   
   author: Carlos Chinchilla
 */

#include <WProgram.h>
#include <Servo.h> 
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Bool.h>

Servo servo;

ROS_CALLBACK( servo_cb, std_msgs::UInt16, cmd_msg)
  servo.write(cmd_msg.data); //set servo angle, should be from 0-180  
  digitalWrite(13, HIGH-digitalRead(13));  //toggle led  
}

ros::NodeHandle nh;
ros::Subscriber sub("servo", &cmd_msg, servo_cb);

std_msgs::Bool pushed_msg;
ros::Publisher pub_button("pushed", &pushed_msg);

const int button_pin = 7;
const int led_pin = 13;

// Button Variables
bool last_reading;
long last_debounce_time=0;
long debounce_delay=50;
bool published = true;

void setup(){
  // Initialize Node Handler and declar subscribers and publishers
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub_button);

  pinMode(led_pin,OUTPUT);
  pinMode(button_pin,INPUT);
  
  // Enable the pull-up resistor on button
  PORTD |= (1<<PD7);

  // Button is a normally button
  last_reading = ! digitalRead(button_pin);
  
  // Servo
  servo.attach(9); //attach it to pin 9
}

void loop(){
  bool reading = ! digitalRead(button_pin);
  
  if (last_reading!= reading){
      last_debounce_time = millis();
      published = false;
  }
  
  //if the button value has not changed for the debounce delay, we know its stable
  if ( !published && (millis() - last_debounce_time)  > debounce_delay) {
    digitalWrite(led_pin, reading);
    pushed_msg.data = reading;
    pub_button.publish(&pushed_msg);
    published = true;
  }

  last_reading = reading;

  nh.spinOnce();
}
