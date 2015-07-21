// Because the arduino IDE is annoying
#include <LiquidCrystal.h>
#include <StandardCplusplus.h>
#include <vector>

#include "ui.h"
#include "motormanager.h"
#include "screenmanager.h"

UI* ui;
ScreenManager* screenManager;
MotorManager* motorManager;

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
  
#ifdef DEBUGCG
  Serial.begin(9600);
  Serial.println("started");
#endif

  ui = UI::instance();
  screenManager = ScreenManager::instance();
  motorManager = MotorManager::instance();

}

void loop(){
  ui->readButtons();
  int button = ui->getButton();

  switch (button) {
    case BUTTON_NONE:
      screenManager->getCurrentScreen()->buttonNone();
      break;
    case BUTTON_RIGHT:
      screenManager->getCurrentScreen()->buttonRight();
      break;
    case BUTTON_UP:
      screenManager->getCurrentScreen()->buttonUp();
      break;
    case BUTTON_DOWN:
      screenManager->getCurrentScreen()->buttonDown();
      break;
    case BUTTON_LEFT:
      screenManager->getCurrentScreen()->buttonLeft();
      break;
    case BUTTON_SELECT:
      screenManager->getCurrentScreen()->buttonCenter();
      break;
    default:
      ui->setSubtext("UNCAUGHT BUTTON ERR");
    }  
  ui->setTitle(screenManager->getCurrentScreen()->getTitle());
  ui->setSubtext(screenManager->getCurrentScreen()->getSubtext());
}

