#ifndef CAMERAGANTRY_SCREENMANAGER_H
#define CAMERAGANTRY_SCREENMANAGER_H

#include <Arduino.h>
#include "screen.h"
#include "mainscreen.h"
#include "menuscreen.h"

class ScreenManager {
  public:
    static ScreenManager* instance();
    inline ~ScreenManager() {};
    void moveTo(Screen* screen);
    Screen* getCurrentScreen();
    Screen* getMainScreen();
    Screen* getMenuScreen();
    void buttonEvent(int currentButton, bool pressed);

  private:
    static ScreenManager* _screenManager;
    ScreenManager();
    
    Screen* currentScreen;
    MainScreen* mainScreen;
    MenuScreen* menuScreen;
};

#endif
