#include "screenmanager.h"

ScreenManager::ScreenManager() {
  mainScreen = MainScreen::instance();
  menuScreen = MenuScreen::instance();
  currentScreen = mainScreen;
  currentScreen->show();
}

ScreenManager* ScreenManager::_screenManager = NULL;

ScreenManager* ScreenManager::instance() {
  if (!_screenManager) {
     _screenManager = new ScreenManager;
  }
  return _screenManager;
}

Screen* ScreenManager::getCurrentScreen() {
  return currentScreen;
}

Screen* ScreenManager::getMainScreen() {
  return mainScreen;
}

Screen* ScreenManager::getMenuScreen() {
  return menuScreen;
}

void ScreenManager::moveTo(Screen* newScreen) {
  currentScreen->hide();
  currentScreen = newScreen;
  currentScreen->show();
}

void ScreenManager::buttonEvent(int currentButton, bool pressed) {
  switch (currentButton) {
    case BUTTON_NONE:
      currentScreen->buttonNone(pressed);
      break;
    case BUTTON_RIGHT:
      currentScreen->buttonRight(pressed);
      break;
    case BUTTON_UP:
      currentScreen->buttonUp(pressed);
      break;
    case BUTTON_DOWN:
      currentScreen->buttonDown(pressed);
      break;
    case BUTTON_LEFT:
      currentScreen->buttonLeft(pressed);
      break;
    case BUTTON_SELECT:
      currentScreen->buttonCenter(pressed);
      break;
    }
}
