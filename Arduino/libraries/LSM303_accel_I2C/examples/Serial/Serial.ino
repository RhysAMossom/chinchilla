#include <Wire.h>
#include <LSM303.h>
//
//Arduino Uno/Duemilanove     LSM303 board
//                    5V  ->  VIN
//                   GND  ->  GND
//          Analog Pin 5  ->  SCL
//          Analog Pin 4  ->  SDA
//
//Arduino Mega                LSM303 board
//                    5V  ->  VIN
//                   GND  ->  GND
//        Digital Pin 21  ->  SCL
//        Digital Pin 20  ->  SDA

LSM303 compass;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  compass.init();
  compass.enableDefault();
}

void loop() {
  compass.read();

  Serial.print("A ");
  Serial.print("X: ");
  Serial.print((int)compass.a.x);
  Serial.print(" Y: ");
  Serial.print((int)compass.a.y);
  Serial.print(" Z: ");
  Serial.print((int)compass.a.z);

  Serial.print(" M ");  
  Serial.print("X: ");
  Serial.print((int)compass.m.x);
  Serial.print(" Y: ");
  Serial.print((int)compass.m.y);
  Serial.print(" Z: ");
  Serial.println((int)compass.m.z);
  
  delay(100);
}
