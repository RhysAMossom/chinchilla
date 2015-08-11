#include "motormanager.h"
#include "ui.h"
#include "constants.h"

MotorManager::MotorManager() :
    currentState(0),
    direction(true),
    directionBackup(true),
    speed(DEFAULT_SPEED_MM_PER_S),
    distance(DEFAULT_DISTANCE_MM),
    distanceLeft(0),
    stepDistance(DEFAULT_STEP_DISTANCE_MM),
    stepTimeInterval(DEFAULT_STEP_TIME_INTERVAL_S),
    stepDistanceLeft(0),
    moveInSteps(false),
    runStep(false),
    endStop1State(false),
    endStop2State(false) {
    stateStrings.push_back("Idle");
    stateStrings.push_back("Time Lapse");
    stateStrings.push_back("Running");
    stateStrings.push_back("Homing");
    stateStrings.push_back("Moving");

    motor = new Stepper(STEPS_PER_REVOLUTION, MOTOR_DIR_A, MOTOR_DIR_B);
    pinMode(MOTOR_A_MOVE, OUTPUT);
    pinMode(MOTOR_B_MOVE, OUTPUT);
    pinMode(MOTOR_BREAK_A, OUTPUT);
    pinMode(MOTOR_BREAK_B, OUTPUT);
    digitalWrite(MOTOR_A_MOVE, HIGH);
    digitalWrite(MOTOR_B_MOVE, HIGH);
    digitalWrite(MOTOR_BREAK_A, LOW);
    digitalWrite(MOTOR_BREAK_B, LOW);
    setSpeed(speed);
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
  motor->setSpeed(mmPerSecToRPM(speed));
}

void MotorManager::home() {
  currentState = 3; // HOMING
  distanceLeft = DEFAULT_DISTANCE_MM;
  directionBackup = direction;
  direction = !direction;
}

void MotorManager::spinMotor() {
  if (!(endStop1State || endStop2State)) {
    switch (currentState) {
      case 1: // Running timelapse
        // TODO: catch overflow in millis()
	if (!runStep && millis() - lastMoveTime >= stepTimeInterval) {
	  // avoid checking the time all the time.
	  runStep = true;
	}
        if (runStep)
          if (stepDistanceLeft > 0)) {
              // move 1 mm at a time
              if (direction)
                motor->step(STEPS_PER_MM);
              else
                motor->step(-STEPS_PER_MM);
              stepDistanceLeft--;
              // Report status to screen
              UI::instance()->setSubtext(getStateString());
          } else {
            // Post-step move action goes here
            runStep = false;
            lastMoveTime = millis();
	    distanceLeft -= stepDistanceLeft;
            stepDistanceLeft = stepDistance;
        } else {
          UI::instance()->setSubtext("next move in "
            + (String)(millis() + stepTimeInterval - lastMoveTime) + "s");
        }
        break;
      case 2: // Running Continuously
      case 3: // Homing
      case 4: // Moving
        if (distanceLeft > 0) {
          // move 1 mm at a time
          if (direction)
            motor->step(STEPS_PER_MM);      
          else
            motor->step(-STEPS_PER_MM);
          distanceLeft--;
          // Report status to screen
          UI::instance()->setSubtext(getStateString());
        }
        break;
    }
  }
}

void MotorManager::continuousMove(bool dir) {
  currentState = 4; // MOVING
  distanceLeft = DEFAULT_DISTANCE_MM;
  directionBackup = direction;
  direction = dir;
}

void MotorManager::start() {
  currentState = stepMove ? 1 : 2; // RUNNING TIMELAPSE : RUNNING CONTINUOUSLY
  stepDistanceLeft = stepDistance;
  stepRun = true;
  distanceLeft = distance;
  directionBackup = direction;
  lastMoveTime = millis();
}

void MotorManager::stop() {
  currentState = 0; // IDLE
  direction = directionBackup;
  distanceLeft = 0;
  stepDistanceLeft = 0;
  stepRun = false;
}

bool MotorManager::isRunning() {
  return (currentState != 0);
}

uint16_t MotorManager::mmPerSecToRPM(uint16_t mm_per_s) {
  // mm/s * 60s = mm/min =
  return mm_per_s*60*STEPS_PER_MM/STEPS_PER_REVOLUTION;
}

String MotorManager::getDirectionString() {
  if (direction)
    return "R";
  return "L";
}

String MotorManager::getStateString() {
  if (!isRunning())
    return getDirectionString() + " " + (String)distance + "mm " + (String)speed + "mm/s";
  return stateStrings[currentState] + " " + getDirectionString() + " " + (String)(distanceLeft) + "mm";
}

