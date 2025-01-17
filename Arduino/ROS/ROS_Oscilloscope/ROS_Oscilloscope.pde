/*
 * rosserial ADC Example
 *
 * This is a poor man's Oscilloscope.  It does not have the sampling
 * rate or accuracy of a commerical scope, but it is great to get
 * an analog value into ROS in a pinch.
 */

#include <WProgram.h>
#include <ros.h>
#include <rosserial_arduino_demos/Adc.h>

ros::NodeHandle nh;

rosserial_arduino_demos::Adc adc_msg;
ros::Publisher p("adc", &adc_msg);


void setup()
{
  pinMode(13, OUTPUT);
  nh.initNode();

  nh.advertise(p);
}

//We average the analog reading to eliminate some of the noise
int averageAnalog(int pin){
 int v=0;
      for(int i=0; i<4; i++) v+= analogRead(pin);
      return v/4;
}

long adc_timer;

void loop()
{

    adc_msg.adc0 = averageAnalog(0);
    adc_msg.adc1 = averageAnalog(1);
    adc_msg.adc2 = averageAnalog(2);
    adc_msg.adc3 = averageAnalog(3);
    adc_msg.adc4 = averageAnalog(4);
    adc_msg.adc5 = averageAnalog(5);

    p.publish(&adc_msg);

  nh.spinOnce();
}
