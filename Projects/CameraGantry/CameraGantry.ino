// Because the arduino IDE is annoying
#include <LiquidCrystal.h>
#include <StandardCplusplus.h>
#include <vector>

#include "ui.h"
#include "motormanager.h"

void endstop1() {
  MotorManager::instance()->setEndStop1State(digitalRead(ENDSTOP_1_PIN));
}

void endstop2() {
  MotorManager::instance()->setEndStop2State(digitalRead(ENDSTOP_2_PIN));
}

void setup() {
  // Endstops Interrupts
  attachInterrupt(0, endstop1, CHANGE);
  attachInterrupt(1, endstop2, CHANGE);
  
  Serial.begin(9600);
  Serial.println("started");
}

void loop(){
  UI::instance()->readButtons();
}

