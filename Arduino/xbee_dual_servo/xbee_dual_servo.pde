#include <Servo.h>
//Arduino Mega Required (usage of multiple hardware serial ports)
//The XBEE Should be connected to RX1 and TX1
//A servo is controlled on pin 9
//The angle written to the servo will be printed on the serial monitor
//MAKE SURE THE SERIAL MONITOR DOES NOT WRITE LINE FEEDS OR CARRIAGE RETURNS
//Finally, there is no error checking done (yet). Write only 1-3 digit numbers at a time

int i;                  //used in for loops
int buffer_size;        //this will store the number of characters currently in the xbee buffer
Servo x_servo;            //servo object
Servo y_servo;
int x_cord=0;             //this will be the angle that the servo will rotate to
int y_cord=0;
int next;
void setup() 
{
  Serial1.begin(9600);
  Serial.begin(9600);
  x_servo.attach(9);
  y_servo.attach(10);
  x_servo.write(0);
  y_servo.write(0);
}



void loop()                     
{
  if(Serial1.available())                                            //if theres something in the buffer
  {
    buffer_size = Serial1.available();                               //store the current buffer size (I assumed the buffer is FIFO)
    if(buffer_size < 8)                                              //only 7 bytes required for x,y coordinates
    {
      for(i=0;i<buffer_size && next != 44;i++)                                  
      {
        x_cord = x_cord*10 + int(Serial1.read())%48;  //this is what I mentioned in the lab
        next = int(Serial1.peek());
      }
      next = Serial1.read();
      buffer_size = Serial1.available();
//      Serial.write("Buffer size: ");
//      Serial.println(buffer_size);
      for(i=0;i<buffer_size;i++)
      {
        y_cord = y_cord*10 + int(Serial1.read())%48;  //this is what I mentioned in the lab
      }      
      //print it and write it to the servo
      Serial.println(x_cord, DEC);
      Serial.println(y_cord, DEC);
      x_servo.write(x_cord);
      y_servo.write(y_cord);
      x_cord = 0;
      y_cord = 0;
      next = 0;
    }
    else
    {
      Serial1.flush();
      Serial.println("Too much data received! Will ignore it and do nothing.");
    }
  }
  //give it enough time to recieve at least 3 bytes again
  delay(30);
}

