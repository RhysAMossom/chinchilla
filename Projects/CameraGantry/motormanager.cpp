#include "motormanager.h"

MotorManager::MotorManager() :
    currentState(IDLE),
    direction(false),
    speed(DEFAULT_SPEED),
    distance(DEFAULT_DISTANCE) {

    stateStrings.push_back("Idle");
    stateStrings.push_back("Running");
    stateStrings.push_back("Error");

    motor = new Motor(MOTOR_BREAK_A, MOTOR_DIR_A, MOTOR_A_MOVE,
                      MOTOR_BREAK_B, MOTOR_DIR_B, MOTOR_B_MOVE);
}

MotorManager* MotorManager::_motorManager = NULL;

MotorManager* MotorManager::instance() {
  if (!_motorManager) {
    _motorManager = new MotorManager;
  }
  return _motorManager;
}

void MotorManager::home() {
  while (!(endStop1State || endStop2State)) {
//    motor->move();
  }
}

void MotorManager::spinMotor() {
  // do next move if moves are queued
  return;
}
void MotorManager::start() {
  return;
}

void MotorManager::stop() {
  return;
}
    
uint16_t MotorManager::mmToSteps(uint16_t mm) {
    return mm*STEPS_PER_MM;
}
