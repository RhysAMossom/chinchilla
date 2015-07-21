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
    inline String getTitle() { return title; };
    inline String getSubtext() { return subtext; };

  private:
    bool visible;
    String title;
    String subtext;
    UI* ui;
};

#endif
