#ifndef CAMERAGANTRY_SCREEN_HH
#define CAMERAGANTRY_SCREEN_HH

#include <Arduino.h>
#include "ui.h"

class Screen {
  public:
    Screen(String title, String subtext);
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

#endif
