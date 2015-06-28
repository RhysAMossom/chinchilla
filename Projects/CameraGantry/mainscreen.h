#ifndef CAMERAGANTRY_MAINCREEN_HH
#define CAMERAGANTRY_MAINCREEN_HH

#include "screen.h"

class MainScreen : public Screen {
  public:
    MainScreen(String text);
    ~MainScreen();

    void buttonUp();
    void buttonDown();
    void buttonLeft();
    void buttonRight();
    void buttonCenter();
};

#endif
