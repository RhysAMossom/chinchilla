#include "menuscreen.h"
#include "menuoption.h"
#include "screenmanager.h"
#include "ui.h"

MenuScreen::MenuScreen() :
    Screen(),
    currentOption(0) {
  motorManager = MotorManager::instance();

  speedSetting = new MenuOption(motorManager->getSpeed(), "Speed", "mm/s", 1, 300, 5);
  menuOptions.push_back(speedSetting);
  
  directionOptions.push_back("left");
  directionOptions.push_back("right");
  directionSetting = new MenuOptionText(1, "Direction", directionOptions);
  menuOptions.push_back(directionSetting);
  
  distanceSetting = new MenuOption(motorManager->getDirection(), "Distance", "mm", 1, 300, 10);
  menuOptions.push_back(distanceSetting);
  
  ledOptions.push_back("on");
  ledOptions.push_back("off");
  // LED is on by default
  ledSetting = new MenuOptionText(0, "LED state", ledOptions);
  menuOptions.push_back(ledSetting);
  
  settingsOptions.push_back("cancel changes");
  settingsOptions.push_back("save all");
  settingsOptions.push_back("reset all");
  settingsSetting = new MenuOptionText(0, "Settings", settingsOptions);
  settingsSetting->appendOptionStates = false;
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
  if (!pressed) {
    if (++currentOption >= menuOptions.size()) {
      currentOption = menuOptions.size() -1;
      return;
    }
    setTitle(menuOptions[currentOption]->getTitle());
    setSubtext(menuOptions[currentOption]->getText());
  }
}
  
void MenuScreen::buttonDown(bool pressed) {
  if (!pressed) {
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
  if (!pressed) {
    menuOptions[currentOption]->previousOption();
    setSubtext(menuOptions[currentOption]->getText());
  }
}

void MenuScreen::buttonRight(bool pressed) {
  if (!pressed) {
    menuOptions[currentOption]->nextOption();
    setSubtext(menuOptions[currentOption]->getText());
  }
}

void MenuScreen::buttonCenter(bool pressed) {
  if (!pressed) {
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
    motorManager->setDistance(menuOptions[currentOption]->getCurrentValue());
  } else if (menuOptions[currentOption] == directionSetting) {
    if (directionOptions[menuOptions[currentOption]->getCurrentValue()] == "right") {
      motorManager->setDirection(true);
    } else {
      motorManager->setDirection(false);
    }    
  } else if (menuOptions[currentOption] == ledSetting) {
    if (ledOptions[menuOptions[currentOption]->getCurrentValue()] == "on") {
      UI::instance()->toggleLCD(true);
    } else {
      UI::instance()->toggleLCD(false);
    }
  } else if (menuOptions[currentOption] == settingsSetting) {

    // Get selected option and apply respective functions to all menu options but this one
    int setting = menuOptions[currentOption]->getCurrentValue();
    if (settingsOptions[setting] == "cancel changes") {
      UI::instance()->setSubtext("Cancelling...");
      for (currentOption = 0; currentOption < menuOptions.size(); currentOption++) {
        if (menuOptions[currentOption] != settingsSetting) {
          menuOptions[currentOption]->cancel();
          saveEvent();
        }
      }
    } else if (settingsOptions[setting] == "save all") {
      UI::instance()->setSubtext("Saving...");
      for (currentOption = 0; currentOption < menuOptions.size(); currentOption++) {
        if (menuOptions[currentOption] != settingsSetting) {
          menuOptions[currentOption]->save();
          saveEvent();
        }
      }
    } else if (settingsOptions[setting] == "reset all") {
      UI::instance()->setSubtext("Resetting...");
      for (currentOption = 0; currentOption < menuOptions.size(); currentOption++) {       
        if (menuOptions[currentOption] != settingsSetting) {
          menuOptions[currentOption]->setDefault(); 
          saveEvent();
        }
      }
    }
    // when done reset currentOption move to main screen
    delay(1000); // message can be displayed
    currentOption = 0;
    ScreenManager::instance()->moveTo(ScreenManager::instance()->getMainScreen());
  }
}
