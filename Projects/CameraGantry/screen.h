#ifndef CAMERAGANTRY_SCREEN_HH
#define CAMERAGANTRY_SCREEN_HH

#include <Arduino.h>

class Screen {
  public:
    Screen(String text);
    ~Screen();

    void buttonUp();
    void buttonDown();
    void buttonLeft();
    void buttonRight();
    void buttonCenter();

    void hide();
    void show();
    bool isVisible();
    void setText(String Text);

  private:
    void update();
    bool visible;
    String mainText;
};

#endif
