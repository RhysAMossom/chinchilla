#ifndef CAMERAGANTRY_MOTORMANAGER_H
#define CAMERAGANTRY_MOTORMANAGER_H

#include "Arduino.h"
#include "Stepper.h"
#include <StandardCplusplus.h>
#include <vector>

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
    uint16_t distanceLeft;
    uint16_t mmPerSecToRPM(uint16_t mm);
    
    Stepper* motor;
    bool endStop1State;
    bool endStop2State;
    int currentState;
    std::vector<String> stateStrings;

    void endstop1();
    void endstop2();
};
#endif
