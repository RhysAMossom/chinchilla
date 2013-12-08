/*
takes analog input from a flex sensor in terms of change in 
resistance and moves a servo motor based on how much the flex
sensor is bent. The input data is smoothed before being sent
to the servos. This program controls 4 servos individually with 
4 individually wired flex sensors. 

written by kevin chen on 6/20/11
*/

#include <Servo.h> 

int inputPin1 = 0;
Servo myservo1;

int inputPin2 = 1;
Servo myservo2; 

int inputPin3 = 2;
Servo myservo3; 

int inputPin4 = 3;
Servo myservo4; 

int var1;
int var2;
int var3;
int var4;

void setup()
{
  Serial.begin(9600);
  myservo1.attach(8);
  myservo2.attach(9);
  myservo3.attach(10);
  myservo4.attach(11);
}

void loop () 
{
  var1 = 0;                                    //var1 acts as a storage variable
  for (int i = 0; i<20; i++)                   //runs the function below 20 times and then resets
  {  
    var1 += analogRead(inputPin1);             //adds the input to var1 and renames the sum var1 to store
  }
  {
    var1 = var1/20;                            //takes average of var1 in order to smooth the data
    var1 = map(var1, 500, 800, 0, 179);        //sets range for input and the degrees that the servo can move
    myservo1.write(var1);                      //var1 is used to map how much the servo moves
  }  

  {
    var2 = 0;                                  //performs same task as above but for servo 2
    for(int j = 0; j<20; j++)
    {
      var2 += analogRead(inputPin2); 
    }
    {
      var2 = var2/20;
      var2 = map(var2, 500, 800, 0, 179);
      myservo2.write(var2);
    }
  }

  {
    var3 = 0;
    for(int k = 0; k<20; k++)
    {
      var3 += analogRead(inputPin3); 
    }
    {
      var3 = var3/20;
      var3 = map(var3, 500, 800, 0, 179);
      myservo3.write(var3);
    }
  }

  {
    var4 = 0;
    for(int l = 0; l<20; l++)
    {
      var4 += analogRead(inputPin4); 
    }
    {
      var4 = var4/20;
      var4 = map(var4, 500, 800, 0, 179);
      myservo4.write(var4);
    }
  }
  Serial.println(var1, DEC);                         //prints the inputs in order to serve as a check
  Serial.println(var2, DEC);                        
  Serial.println(var3, DEC);
  Serial.println(var4, DEC);
}
