#include "menuscreen.h"

MenuScreen::MenuScreen() :
    Screen() {
  setTitle("Menu Screen");
  setSubtext("Mn Subtext");
}

MenuScreen* MenuScreen::_menuScreen = NULL;

MenuScreen* MenuScreen::instance() {
  if (!_menuScreen) {
    _menuScreen = new MenuScreen;
  }
  return _menuScreen;
}

void MenuScreen::buttonUp() {
  setSubtext("Mn buttonUp");
}
  
void MenuScreen::buttonDown() {
  setSubtext("Mn buttonDown");
}

void MenuScreen::buttonLeft() {
  setSubtext("Mn buttonLeft");
}

void MenuScreen::buttonRight() {
  setSubtext("Mn buttonRight");
}

void MenuScreen::buttonCenter() {
  setSubtext("Mn buttonRight");
}

void MenuScreen::buttonNone() {
  setSubtext("Mn no button");
}

