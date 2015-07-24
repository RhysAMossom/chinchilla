#ifndef CAMERAGANTRY_SCREEN_H
#define CAMERAGANTRY_SCREEN_H

#include <Arduino.h>
#include "ui.h"

class Screen {
  public:
    Screen();
    inline ~Screen() {};

    inline virtual void buttonUp(bool pressed) {};
    inline virtual void buttonDown(bool pressed) {};
    inline virtual void buttonLeft(bool pressed) {};
    inline virtual void buttonRight(bool pressed) {};
    inline virtual void buttonCenter(bool pressed) {};
    inline virtual void buttonNone(bool pressed) {};

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
