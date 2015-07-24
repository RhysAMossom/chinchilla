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
  if (pressed) {
    ScreenManager* screenManager = ScreenManager::instance();
    screenManager->moveTo(screenManager->getMenuScreen());
  }
}
  
void MainScreen::buttonDown(bool pressed) {
  if (pressed) {
    setSubtext("Info Screen");
  } else {
    setSubtext("");
  }
}

void MainScreen::buttonLeft(bool pressed) {
  if (pressed) {
    setSubtext("Moving Left");
  } else {
    setSubtext("Stopped");
    delay(1000);
    setSubtext("");
  }
}

void MainScreen::buttonRight(bool pressed) {
  if (pressed) {
    setSubtext("Moving Right");
  } else {
    setSubtext("Stopped");
    delay(1000);
    setSubtext("");
  }
}

void MainScreen::buttonCenter(bool pressed) {
  if (pressed) {
    setSubtext("Started");
  } else {
    setSubtext("Stopped");
  }
  delay(1000);
  setSubtext("");
}

void MainScreen::buttonNone(bool pressed) {
  setSubtext(MotorManager::instance()->getStateString());
}


