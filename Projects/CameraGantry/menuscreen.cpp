#include "menuscreen.h"
#include "menuoption.h"
#include "screenmanager.h"

MenuScreen::MenuScreen() :
    Screen(),
    currentOption(0) {
  motorManager = MotorManager::instance();
  speedSetting = new MenuOption(10, "Speed", "mm/s", 0, 10);
  menuOptions.push_back(speedSetting);
  
  distanceSetting = new MenuOption(10, "Distance", "mm", 0, 10);
  menuOptions.push_back(distanceSetting);
  
  directionOptions.push_back("left");
  directionOptions.push_back("right");
  directionSetting = new MenuOptionText(1, "Direction", directionOptions);
  menuOptions.push_back(directionSetting);
  
  ledOptions.push_back("off");
  ledOptions.push_back("on");
  ledSetting = new MenuOptionText(0, "LED state", ledOptions);
  menuOptions.push_back(ledSetting);
  
  settingsOptions.push_back("cancel");
  settingsOptions.push_back("save all");
  settingsOptions.push_back("restore defaults");
  settingsSetting = new MenuOptionText(0, "Settings", settingsOptions);
  menuOptions.push_back(settingsSetting);
  
  setTitle(menuOptions[currentOption]->getTitle());
  setSubtext(menuOptions[currentOption]->getText());
}

MenuScreen* MenuScreen::_menuScreen = NULL;

MenuScreen* MenuScreen::instance() {
  if (!_menuScreen) {
    _menuScreen = new MenuScreen;
  }
  return _menuScreen;
}

void MenuScreen::buttonUp(bool pressed) {
  if (pressed) {
    if (++currentOption >= menuOptions.size()) {
      currentOption = menuOptions.size() -1;
      return;
    }
    setTitle(menuOptions[currentOption]->getTitle());
    setSubtext(menuOptions[currentOption]->getText());
  }
}
  
void MenuScreen::buttonDown(bool pressed) {
  if (pressed) {
    if ( --currentOption < 0 ) {
      currentOption = 0;
      ScreenManager* screenManager = ScreenManager::instance();
      screenManager->moveTo(screenManager->getMainScreen());
    }
    setTitle(menuOptions[currentOption]->getTitle());
    setSubtext(menuOptions[currentOption]->getText());
  }
}

void MenuScreen::buttonLeft(bool pressed) {
  if (pressed) {
    menuOptions[currentOption]->previousOption();
    setSubtext(menuOptions[currentOption]->getText());
  }
}

void MenuScreen::buttonRight(bool pressed) {
  if (pressed) {
    menuOptions[currentOption]->nextOption();
    setSubtext(menuOptions[currentOption]->getText());
  }
}

void MenuScreen::buttonCenter(bool pressed) {
  if (pressed) {
    menuOptions[currentOption]->save();
    saveEvent();
    setSubtext(menuOptions[currentOption]->getText());
  }
}

void MenuScreen::buttonNone(bool pressed) {
  // Do nothing here
}

void MenuScreen::saveEvent() {
  if (menuOptions[currentOption] == speedSetting) {
    motorManager->setSpeed(menuOptions[currentOption]->getCurrentValue());
  } else if (menuOptions[currentOption] == distanceSetting) {
    
  } else if (menuOptions[currentOption] == directionSetting) {
    
  } else if (menuOptions[currentOption] == ledSetting) {
    
  } else if (menuOptions[currentOption] == settingsSetting) {
    
  }
}
