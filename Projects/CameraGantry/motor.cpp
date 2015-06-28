#include "motor.h"

Motor::Motor(int channelABreak, int channelADir, int channelAMove,
             int channelBBreak, int channelBDir, int channelBMove) :
    running(false),
    channelABreak(channelABreak),
    channelADir(channelADir),
    channelAMove(channelAMove),
    channelBBreak(channelBBreak),
    channelBDir(channelBDir),
    channelBMove(channelBMove) {
      pinMode(channelABreak, OUTPUT);
      pinMode(channelADir, OUTPUT); // HIGH = forwards and LOW = backwards
      pinMode(channelBBreak, OUTPUT);
      pinMode(channelBDir, OUTPUT);
}

void Motor::move(uint16_t steps, uint16_t steps_per_mm, bool direction) {
  running = true;
  // move according to params passed
  running = false;
}
  
bool Motor::isRunnig() { return running; };

/*
void backwards(int delayLength){
 
  digitalWrite(MOTOR_BREAK_A, LOW);  //ENABLE CH A
  digitalWrite(MOTOR_BREAK_B, HIGH); //DISABLE CH B

  digitalWrite(MOTOR_DIR_A, HIGH);   //Sets direction of CH A
  analogWrite(MOTOR_A_MOVE, 255);   //Moves CH A
  
  delay(delayLength);
  
  digitalWrite(MOTOR_BREAK_A, HIGH);  //DISABLE CH A
  digitalWrite(MOTOR_BREAK_B, LOW); //ENABLE CH B

  digitalWrite(MOTOR_DIR_B, HIGH);   //Sets direction of CH B
  analogWrite(MOTOR_B_MOVE, 255);   //Moves CH B
  
  delay(delayLength);
  
  digitalWrite(MOTOR_BREAK_A, LOW);  //ENABLE CH A
  digitalWrite(MOTOR_BREAK_B, HIGH); //DISABLE CH B

  digitalWrite(MOTOR_DIR_A, LOW);   //Sets direction of CH A
  analogWrite(MOTOR_A_MOVE, 255);   //Moves CH A
  
  delay(delayLength);
    
  digitalWrite(MOTOR_BREAK_A, HIGH);  //DISABLE CH A
  digitalWrite(MOTOR_BREAK_B, LOW); //ENABLE CH B

  digitalWrite(MOTOR_DIR_B, LOW);   //Sets direction of CH B
  analogWrite(MOTOR_B_MOVE, 255);   //Moves CH B
  
  delay(delayLength);

}

void fowards(int delayLength) {
 
  digitalWrite(MOTOR_BREAK_A, LOW);  //ENABLE CH A
  digitalWrite(MOTOR_BREAK_B, HIGH); //DISABLE CH B

  digitalWrite(MOTOR_DIR_A, HIGH);   //Sets direction of CH A
  analogWrite(MOTOR_A_MOVE, 255);   //Moves CH A
  
  delay(delayLength);
  
  digitalWrite(MOTOR_BREAK_A, HIGH);  //DISABLE CH A
  digitalWrite(MOTOR_BREAK_B, LOW); //ENABLE CH B

  digitalWrite(MOTOR_DIR_B, LOW);   //Sets direction of CH B
  analogWrite(MOTOR_B_MOVE, 255);   //Moves CH B
  
  delay(delayLength);
  
  digitalWrite(MOTOR_BREAK_A, LOW);  //ENABLE CH A
  digitalWrite(MOTOR_BREAK_B, HIGH); //DISABLE CH B

  digitalWrite(MOTOR_DIR_A, LOW);   //Sets direction of CH A
  analogWrite(MOTOR_A_MOVE, 255);   //Moves CH A
  
  delay(delayLength);
    
  digitalWrite(MOTOR_BREAK_A, HIGH);  //DISABLE CH A
  digitalWrite(MOTOR_BREAK_B, LOW); //ENABLE CH B

  digitalWrite(MOTOR_DIR_B, HIGH);   //Sets direction of CH B
  analogWrite(MOTOR_B_MOVE, 255);   //Moves CH B
  
  delay(delayLength);

}*/
