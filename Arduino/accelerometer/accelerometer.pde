double gx,gy,gz,  ref = 1.65;//use 3.3V
const double s = 0.8, samples =50.0;
int x=0,y=0,z=0;
double vx,vy,vz;

//pins
int sl=3,g1=4,g2=5;// outputs
int xPin=0,yPin=1,zPin=2;// inputs


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
  Serial.println("G forces on axes\nX\tY\tZ");
}

void loop()
{
  for(int i =0;i<samples;i++){
    x += analogRead(xPin);
    y += analogRead(yPin);
    z += analogRead(zPin);
  }
  x*=(1/samples);
  y*=(1/samples);
  z*=(1/samples);
  Serial.print(x,DEC);
  Serial.print("\t");
  Serial.print(y,DEC);
  Serial.print("\t");
  Serial.print(z,DEC);
  Serial.print("\t\n");
  
  vx = 5*(x/1024.0);
  gx = (vx-ref)/s;
  vy = 5*(y/1024.0);
  gy = (vy -ref)/s;
  vz = 5*(z/1024.0);
  gz = (vz -ref)/s;
  Serial.print(vx);
  Serial.print("\t");
  Serial.print(vy);
  Serial.print("\t");
  Serial.print(vz);
  Serial.print("\t\n");

  Serial.print(gx,DEC);
  Serial.print("\t");
  Serial.print(gy,DEC);
  Serial.print("\t");
  Serial.print(gz,DEC);
  Serial.print("\t\n");

  delay(1000);
}  
