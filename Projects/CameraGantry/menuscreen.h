#ifndef CAMERAGANTRY_MENUSCREEN_H
#define CAMERAGANTRY_MENUSCREEN_H

#include <StandardCplusplus.h>
#include <vector>
#include "screen.h"
#include "menuoption.h"
#include "ui.h"
#include "motormanager.h"

class MenuScreen : public Screen {
  public:
    static MenuScreen* instance();
    inline ~MenuScreen() {};

    void buttonUp(bool pressed);
    void buttonDown(bool pressed);
    void buttonLeft(bool pressed);
    void buttonRight(bool pressed);
    void buttonCenter(bool pressed);
    void buttonNone(bool pressed);

  private:
    static MenuScreen* _menuScreen;
    MenuScreen();

    void saveEvent();
    std::vector<MenuOption*> menuOptions;
    int currentOption;
    
    MotorManager* motorManager;
    MenuOption* speedSetting;
    MenuOption* distanceSetting;
    MenuOption* stepDistanceSetting;
    MenuOption* stepTimeIntervalSetting;
    std::vector<String> directionOptions;
    MenuOptionText* directionSetting;
    std::vector<String> moveTypeOptions;
    MenuOptionText* moveTypeSetting;
    std::vector<String> ledOptions;
    MenuOptionText* ledSetting;  
    std::vector<String> settingsOptions;
    MenuOptionText* settingsSetting;
};
#endif
