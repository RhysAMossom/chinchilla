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
      setSubtext("Stopped");
    } else {
      MotorManager::instance()->home();
      setSubtext("Homing");
    }
    delay(1000);
    setSubtext(MotorManager::instance()->getStateString());
}

void MainScreen::buttonLeft(bool pressed) {
  if (pressed) {
    setSubtext("Moving Left");
    MotorManager::instance()->continuousMove(false);    
  } else {
    setSubtext("Stopped");
    MotorManager::instance()->stop();
  }
  delay(1000);
  setSubtext(MotorManager::instance()->getStateString());
}

void MainScreen::buttonRight(bool pressed) {
  if (pressed) {
    setSubtext("Moving Right");
    MotorManager::instance()->continuousMove(true);
  } else {
    setSubtext("Stopped");
    MotorManager::instance()->stop();
  }
  delay(1000);
  setSubtext(MotorManager::instance()->getStateString());
}

void MainScreen::buttonCenter(bool pressed) {
  if (!pressed) {
    if (MotorManager::instance()->isRunning()){
      MotorManager::instance()->stop();
      setSubtext("Stopped");
    } else {
      MotorManager::instance()->start();
      setSubtext("Started");
    }
    delay(1000);
    setSubtext(MotorManager::instance()->getStateString());
  }
}

void MainScreen::buttonNone(bool pressed) {
  setSubtext(MotorManager::instance()->getStateString());
}


