#ifndef CAMERAGANTRY_SCREEN_HH
#define CAMERAGANTRY_SCREEN_HH

#include <Arduino.h>
#include "ui.h"

class Screen {
  public:
    Screen(String title, String subtext, UI& ui);
    inline ~Screen() {};

    void buttonUp();
    void buttonDown();
    void buttonLeft();
    void buttonRight();
    void buttonCenter();

    void hide();
    void show();
    bool isVisible();
    void setTitle(String text);
    void setSubtext(String text);
    void update();

  private:
    UI* ui;
    bool visible;
    String title;
    String subtext;
};

#endif
