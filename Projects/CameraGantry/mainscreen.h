#ifndef CAMERAGANTRY_MAINCREEN_HH
#define CAMERAGANTRY_MAINCREEN_HH

#include "screen.h"
#include "ui.h"

class MainScreen : public Screen {
  public:
    MainScreen();
    inline ~MainScreen() {};

    void buttonUp();
    void buttonDown();
    void buttonLeft();
    void buttonRight();
    void buttonCenter();
    void buttonNone();
};

#endif
