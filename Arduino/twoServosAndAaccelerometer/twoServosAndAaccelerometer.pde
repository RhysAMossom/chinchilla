double gx,gy,gz;
const double s = 0.8, samples =50.0, ref = 1.65;//use 3.3v
double x,y,z;

//pins
int sl=3,g1=4,g2=5;// outputs
int xPin=0,yPin=1,zPin=2;// inputs

void getGs(double& x,double& y, double& z){
  x=0; y=0; z=0;
  for(int i =0;i<samples;i++){
      x += analogRead(xPin);
      y += analogRead(yPin);
      z += analogRead(zPin);
    }
    x*=(1/samples);
    y*=(1/samples);
    z*=(1/samples);
    x =(5*(x/1024.0) - ref)/s;
    y =(5*(y/1024.0) - ref)/s;
    z =(5*(z/1024.0) - ref)/s;
}
  
void calibrate(double& gx, double& gy,double& gz){
  gx=0;gy=0;gz=0;
  for(int j=0;j<10.0;j++){
    getGs(gx,gy,gz);
    gx += gx;
    gy += gy;
    gz += gz;
  }
  gx*=1/10.0;
  gy*=1/10.0;
  gz*=1/10.0;
  Serial.println("Calibrated at\nX\tY\tZ");
  Serial.print(gx);
  Serial.print("\t");
  Serial.print(gy);
  Serial.print("\t");
  Serial.println(gz);
}

void setup()
{
  Serial.begin(9600);

  pinMode(g1,OUTPUT);//g1 and g2 have to do with sensitivity
  pinMode(g2,OUTPUT);
  pinMode(sl,OUTPUT);//sleep
  pinMode(xPin,INPUT);
  pinMode(yPin,INPUT);
  pinMode(zPin,INPUT);
  
  digitalWrite(sl,HIGH);//LOW sleep means sleep mode is ON
  digitalWrite(g1,LOW);
  digitalWrite(g2,LOW);
  
  /*
  g1  g2    gRange (g)    Sensitivity (V/g)
  0    0      1.5            0.8
  0    1        2            0.6
  1    0        4            0.3
  1    1        6            0.2
  */
  calibrate(gx,gy,gz);
}

void loop()
{
  getGs(x,y,z);
  if (x>gx)
    Serial.println("Moving right");
  else if (x<gx)
    Serial.println("Moving left");
  if (y>gy)
    Serial.println("Y+");
  else if (y<gy)
    Serial.println("Y-");
  if (z>gz)
    Serial.println("Z+");
  else if (z<gz)
    Serial.println("Z-");
  
  
  delay(1000);
}  

