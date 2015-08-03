#include "mainscreen.h"
#include "screenmanager.h"
#include "motormanager.h"

MainScreen::MainScreen() :
    Screen() {
  setTitle("Camera Gantry");
  setSubtext("by Chinchilla");
}

MainScreen* MainScreen::_mainScreen = NULL;

MainScreen* MainScreen::instance() {
  if (!_mainScreen) {
    _mainScreen = new MainScreen;
  }
  return _mainScreen;
}

void MainScreen::buttonUp(bool pressed) {
  if (!pressed) {
    ScreenManager::instance()->moveTo(ScreenManager::instance()->getMenuScreen());
  }
}
  
void MainScreen::buttonDown(bool pressed) {
  if (MotorManager::instance()->isRunning()){
    MotorManager::instance()->stop();
  } else {
    MotorManager::instance()->home();
  }
}

void MainScreen::buttonLeft(bool pressed) {
  if (pressed) {
    MotorManager::instance()->continuousMove(false);    
  } else {
    MotorManager::instance()->stop();
  }
}

void MainScreen::buttonRight(bool pressed) {
  if (pressed) {
    MotorManager::instance()->continuousMove(true);
  } else {
    MotorManager::instance()->stop();
  }
}

void MainScreen::buttonCenter(bool pressed) {
  if (!pressed) {
    if (MotorManager::instance()->isRunning()){
      MotorManager::instance()->stop();
    } else {
      MotorManager::instance()->start();
    }
  }
}

void MainScreen::buttonNone(bool pressed) {
  setSubtext(MotorManager::instance()->getStateString());
}


