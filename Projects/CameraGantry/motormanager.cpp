#include "motormanager.h"
#include "ui.h"
#include "constants.h"
#include "mainscreen.h"

MotorManager::MotorManager() :
    currentState(0),
    direction(true),
    directionBackup(true),
    speed(DEFAULT_SPEED_MM_PER_S),
    distance(DEFAULT_DISTANCE_MM),
    distanceLeft(0),
    stepDistance(DEFAULT_STEP_DISTANCE_MM),
    stepTimeInterval(DEFAULT_STEP_TIME_INTERVAL_MS),
    lastMoveTime(0),
    stepDistanceLeft(0),
    moveInSteps(true),
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
      case 0: // Idle
        break;
      case 1: // Running timelapse
        // TODO: catch overflow in millis()
	if (!runStep && (long)(millis() - lastMoveTime - stepTimeInterval) >= 0) {
	  // avoid checking the time all the time.
	  runStep = true;
	}
        if (runStep) {
          if (stepDistanceLeft > 0) {
              // move 1 mm at a time
              if (direction)
                motor->step(STEPS_PER_MM);
              else
                motor->step(-STEPS_PER_MM);
              stepDistanceLeft--;
              distanceLeft--;
              // Report status to screen
              UI::instance()->setSubtext(getStateString());
          } else {
            // Post-step move action goes here
            postStepProcess();
            runStep = false;
            lastMoveTime = millis();
            stepDistanceLeft = stepDistance;
          }
        } else {
          UI::instance()->setSubtext("waiting " + 
            (String)((long)(lastMoveTime + stepTimeInterval - millis())/1000 + 1) + "s "
            + distanceLeft + "mm");
        }
        if (distanceLeft <= 0) {
          stop();
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
        } else {
          stop();
        }
        
        break;
    }
  } else if(isRunning()){
      stop();
  }
}

void MotorManager::continuousMove(bool dir) {
  currentState = 4; // MOVING
  distanceLeft = DEFAULT_DISTANCE_MM;
  directionBackup = direction;
  direction = dir;
}

void MotorManager::start() {
  currentState = moveInSteps ? 1 : 2; // RUNNING TIMELAPSE : RUNNING CONTINUOUSLY
  stepDistanceLeft = stepDistance;
  runStep = true;
  distanceLeft = distance;
  directionBackup = direction;
  lastMoveTime = millis();
}

void MotorManager::stop() {
  UI::instance()->setSubtext(stateStrings[currentState] + " stopped");
  currentState = 0; // IDLE
  direction = directionBackup;
  distanceLeft = 0;
  stepDistanceLeft = 0;
  runStep = false;
  delay(1000);
  MainScreen::instance()->buttonNone(false);
}

void MotorManager::postStepProcess() {
  UI::instance()->setSubtext("Say 'cheese'");
  digitalWrite(LCD_LED_PIN, !digitalRead(LCD_LED_PIN));
  delay(100);
  digitalWrite(LCD_LED_PIN, !digitalRead(LCD_LED_PIN));
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
    return (moveInSteps ? "TL ": "C ") + getDirectionString() + " " + (String)distance + "mm " +
    (moveInSteps ? (String)stepDistance + "mm/" + (String)(stepTimeInterval/1000) + "s" : (String)speed + "mm/s");
  return stateStrings[currentState] + " " + getDirectionString() + " " + (String)(distanceLeft) + "mm";
}

