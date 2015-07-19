// Because the arduino IDE is annoying
#include <LiquidCrystal.h>
#include <StandardCplusplus.h>
#include <vector>

#include "ui.h"
#include "motormanager.h"
#include "mainscreen.h"
#include "menuscreen.h"

Screen* currentScreen;
UI* ui;
MainScreen* mainScreen;
MenuScreen* menuScreen;
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

  ui = UI::instance();
  mainScreen = MainScreen::instance();
  menuScreen = MenuScreen::instance();


  motorManager = MotorManager::instance();
  
  mainScreen->show();
  menuScreen->hide();
  currentScreen = mainScreen;
}

void loop(){
  ui->readButtons();
  int button = ui->getButton();
  ui->setTitle(currentScreen->getTitle());
  ui->setSubtext(currentScreen->getSubtext());
  switch (button) {
    case BUTTON_NONE:
      currentScreen->buttonNone();
      break;
    case BUTTON_RIGHT:
      currentScreen->buttonRight();
      break;
    case BUTTON_UP:
      currentScreen->buttonUp();
      break;
    case BUTTON_DOWN:
      currentScreen->buttonDown();
      break;
    case BUTTON_LEFT:
      currentScreen->buttonLeft();
      break;
    case BUTTON_SELECT:
      currentScreen->buttonCenter();
      break;
    default:
      ui->setSubtext("UNCAUGHT BUTTON ERR");
  }  
}

