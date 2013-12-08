import processing.serial.*;
Serial arduino;

float curX=300.0,curY=200.0;
float [] x;
float [] y;
int i =0;
float a = 15.0*PI/180;
const int maxDegree = 180;

void setup(){
  size(600,400);
  rectMode(CENTER);
  frameRate(30);
  x= new float[maxDegree];
  y= new float[maxDegree];

  //println(Serial.list());
  arduino = new Serial(this,Serial.list()[0],9600);  
  arduino.bufferUntil('\n');
}

void draw(){ 
  background(0); 

  for(int j = 0; j<i;j++){
    stroke(255);
    point(curX+x[j],curY+y[j]);
  }
  
}

void serialEvent(Serial arduino){
  String temp = arduino.readStringUntil('\n');
  println(temp);
  if(temp != null){
    int d = Integer.parseInt(trim(temp));
    println(d);
    x[i]=cos(a)*d;
    y[i]=sin(a)*d;
    
    if(i<maxDegree){//a <178*PI/180.0){
      i++;
      a+= PI/180.0;
      }
    }  
}

