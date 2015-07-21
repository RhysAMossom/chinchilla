#include "screenmanager.h"

ScreenManager::ScreenManager() {
  mainScreen = MainScreen::instance();
  menuScreen = MenuScreen::instance();
  mainScreen->show();
  menuScreen->hide();
  currentScreen = mainScreen;
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
  currentScreen = newScreen;
  UI::instance()->setTitle(currentScreen->getTitle());
  UI::instance()->setSubtext(currentScreen->getSubtext());
}
