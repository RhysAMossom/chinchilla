#include "menuscreen.h"
#include "menuoption.h"
#include "screenmanager.h"

MenuScreen::MenuScreen() :
    Screen(),
    currentOption(0) {
  menuOptions.push_back(MenuOption(10, "Speed", "mm/s", 0, 10));
  menuOptions.push_back(MenuOption(10, "Distance", "mm", 0, 10));
  menuOptions.push_back(MenuOption(1, "Direction", "", 0, 1));
  menuOptions.push_back(MenuOption(0, "LED state", "", 0, 1));
  menuOptions.push_back(MenuOption(0, "Settings", "", 0, 4));
  
  setTitle(menuOptions[currentOption].getTitle());
  setSubtext(menuOptions[currentOption].getText());
}

MenuScreen* MenuScreen::_menuScreen = NULL;

MenuScreen* MenuScreen::instance() {
  if (!_menuScreen) {
    _menuScreen = new MenuScreen;
  }
  return _menuScreen;
}

void MenuScreen::buttonUp() {
  if (++currentOption >= menuOptions.size()) {
    currentOption = menuOptions.size() -1;
    return;
  }
  setTitle(menuOptions[currentOption].getTitle());
  setSubtext(menuOptions[currentOption].getText());
}
  
void MenuScreen::buttonDown() {
  Serial.println(currentOption);
  if ( --currentOption < 0 ) {
    currentOption = 0;
    ScreenManager* screenManager = ScreenManager::instance();
    screenManager->moveTo(screenManager->getMainScreen());
  }
  setTitle(menuOptions[currentOption].getTitle());
  setSubtext(menuOptions[currentOption].getText());
}

void MenuScreen::buttonLeft() {
  menuOptions[currentOption].previousOption();
  setSubtext(menuOptions[currentOption].getText());
}

void MenuScreen::buttonRight() {
  menuOptions[currentOption].nextOption();
  setSubtext(menuOptions[currentOption].getText());
}

void MenuScreen::buttonCenter() {
  menuOptions[currentOption].save();
  setSubtext(menuOptions[currentOption].getText());
}

void MenuScreen::buttonNone() {
  // Do nothing here
}

