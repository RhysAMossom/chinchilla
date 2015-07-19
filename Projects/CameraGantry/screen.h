#ifndef CAMERAGANTRY_SCREEN_H
#define CAMERAGANTRY_SCREEN_H

#include <Arduino.h>
#include "ui.h"

class Screen {
  public:
    Screen();
    inline ~Screen() {};

    inline virtual void buttonUp() {};
    inline virtual void buttonDown() {};
    inline virtual void buttonLeft() {};
    inline virtual void buttonRight() {};
    inline virtual void buttonCenter() {};
    inline virtual void buttonNone() {};

    void hide();
    void show();
    bool isVisible();
    void setTitle(String text);
    void setSubtext(String text);
    String getTitle();
    String getSubtext();

  private:
    bool visible;
    String title;
    String subtext;
};

class ScreenManager {
  public:
    static ScreenManager* instance();
    inline ~ScreenManager() {};
    void addScreen();
    void moveTo(Screen* screen);
    void moveBack();
    Screen* currentScreen();

  private:
    static ScreenManager* _staticManager;
    ScreenManager();
}

#endif
