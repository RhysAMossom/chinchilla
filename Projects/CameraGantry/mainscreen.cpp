#include "mainscreen.h"
#include "screenmanager.h"

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

void MainScreen::buttonUp() {
  ScreenManager* screenManager = ScreenManager::instance();
  screenManager->moveTo(screenManager->getMenuScreen());
}
  
void MainScreen::buttonDown() {
  setSubtext("Info Screen");
}

void MainScreen::buttonLeft() {
  setSubtext("Moving Left");
}

void MainScreen::buttonRight() {
  setSubtext("Moving Right");
}

void MainScreen::buttonCenter() {
  setSubtext("Start/Stop");
}

void MainScreen::buttonNone() {
  setSubtext("");
}


