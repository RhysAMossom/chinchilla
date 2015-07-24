#ifndef CAMERAGANTRY_MAINCREEN_H
#define CAMERAGANTRY_MAINCREEN_H

#include "screen.h"
#include "ui.h"

class MainScreen : public Screen {
  public:
    static MainScreen* instance();
    inline ~MainScreen() {};

    void buttonUp(bool pressed);
    void buttonDown(bool pressed);
    void buttonLeft(bool pressed);
    void buttonRight(bool pressed);
    void buttonCenter(bool pressed);
    void buttonNone(bool pressed);

  private:
    static MainScreen* _mainScreen;
    MainScreen();
};
#endif
