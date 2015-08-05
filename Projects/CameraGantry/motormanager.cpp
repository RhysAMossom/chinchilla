#include "motormanager.h"
#include "ui.h"

MotorManager::MotorManager() :
    currentState(0),
    direction(true),
    directionBackup(true),
    speed(DEFAULT_SPEED),
    distance(DEFAULT_DISTANCE),
    stepsLeft(0),
    endStop1State(false),
    endStop2State(false) {
    stateStrings.push_back("Idle");
    stateStrings.push_back("Running");
    stateStrings.push_back("Homing");
    stateStrings.push_back("Moving R");
    stateStrings.push_back("Moving L");    

    motor = new Stepper(STEPS_PER_REVOLUTION, MOTOR_DIR_A, MOTOR_DIR_B);
    pinMode(MOTOR_A_MOVE, OUTPUT);
    pinMode(MOTOR_B_MOVE, OUTPUT);
//    pinMode(MOTOR_BREAK_A, OUTPUT);
//    pinMode(MOTOR_BREAK_B, OUTPUT);
    digitalWrite(MOTOR_A_MOVE, HIGH);
    digitalWrite(MOTOR_B_MOVE, HIGH);
//    digitalWrite(MOTOR_BREAK_A, LOW);
//    digitalWrite(MOTOR_BREAK_B, LOW);
    motor->setSpeed(mmToSteps(speed));
}

MotorManager* MotorManager::_motorManager = NULL;

MotorManager* MotorManager::instance() {
  if (!_motorManager) {
    _motorManager = new MotorManager;
  }
  return _motorManager;
}

void MotorManager::setDirection(bool dir) {
  direction = dir;
  directionBackup = dir;
}

void MotorManager::setSpeed(uint16_t mm_per_s) {
  speed = mm_per_s; 
  motor->setSpeed(mmToSteps(speed));
}

void MotorManager::home() {
  currentState = 2; // HOMING
  stepsLeft = mmToSteps(DEFAULT_DISTANCE);
  directionBackup = direction;
}

void MotorManager::spinMotor() {  
  // do next move if moves are queued
  if (currentState != 0 && stepsLeft > 0 && !(endStop1State || endStop2State)) {
    if (direction)
      motor->step(STEPS_PER_MM);      
    else
      motor->step(-STEPS_PER_MM);
    stepsLeft -= STEPS_PER_MM;
    // if we are moving we must report status to screen
    UI::instance()->setSubtext(getStateString());
  }
}

void MotorManager::continuousMove(bool dir) {
  if (dir)
    currentState = 3; // MOVE RIGHT
  else
    currentState = 4; // MOVE LEFT
  stepsLeft = mmToSteps(DEFAULT_DISTANCE);
  directionBackup = direction;
  direction = dir;
}

void MotorManager::start() {
  currentState = 1; // RUNNING
  stepsLeft = mmToSteps(distance);
  directionBackup = direction;
}

void MotorManager::stop() {
  currentState = 0; // IDLE
  direction = directionBackup;
  stepsLeft = 0;
}

bool MotorManager::isRunning() {
  return (currentState != 0);
}

uint16_t MotorManager::mmToSteps(uint16_t mm) {
    return mm*STEPS_PER_MM;
}

String MotorManager::getDirectionString() {
  if (direction)
    return "R";
  return "L";
}

String MotorManager::getStateString() {
  if (!isRunning())
    return getDirectionString() + " " + (String)distance + "mm " + (String)speed + "mm/s";
  return stateStrings[currentState] + " " + (String)(stepsLeft/STEPS_PER_MM) + "mm";
}

