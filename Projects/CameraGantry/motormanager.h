#ifndef CAMERAGANTRY_MOTORMANAGER_H
#define CAMERAGANTRY_MOTORMANAGER_H

#include "Arduino.h"
#include "Stepper.h"
#include <StandardCplusplus.h>
#include <vector>

#define DEFAULT_SPEED 10 // mm/s
#define DEFAULT_DISTANCE 300 // mm
#define STEPS_PER_MM 10
#define STEPS_PER_REVOLUTION 100 //200

// Motor defines
#define MOTOR_BREAK_A 16
#define MOTOR_DIR_A 12
#define MOTOR_A_MOVE 3
#define MOTOR_BREAK_B 15
#define MOTOR_DIR_B 13
#define MOTOR_B_MOVE 11

// Enstop pins
#define ENDSTOP_1_PIN 2
#define ENDSTOP_2_PIN 3

class MotorManager {
  public:

    inline ~MotorManager() {};
    static MotorManager* instance();

    inline int getState() { return currentState; };
    bool isRunning();
    String getStateString();
    String getDirectionString();
    inline bool getDirection() { return direction; };
    inline uint16_t getSpeed() { return speed; };
    inline uint16_t getDistance() { return distance; };
    
    void setDirection(bool dir);
    void setSpeed(uint16_t mm_per_s);
    inline void setDistance(uint16_t mm) { distance = mm; };

    // Called in interrupt routine
    inline void setEndStop1State(bool state) { endStop1State = state;};
    inline void setEndStop2State(bool state) { endStop2State = state;}

    void home();
    void continuousMove(bool direction);
    
    void spinMotor();
    void start();
    void stop();
    
  private:
    MotorManager();
    static MotorManager* _motorManager;

    bool direction;
    bool directionBackup;
    uint16_t speed;
    uint16_t distance;
    uint16_t mmToSteps(uint16_t mm);
    uint16_t stepsLeft;
    
    Stepper* motor;
    bool endStop1State;
    bool endStop2State;
    int currentState;
    std::vector<String> stateStrings;

    void endstop1();
    void endstop2();
};
#endif
