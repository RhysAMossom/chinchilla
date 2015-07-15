#ifndef CAMERAGANTRY_MENUSCREEN_H
#define CAMERAGANTRY_MENUSCREEN_H

#include <StandardCplusplus.h>
#include <vector>
#include "screen.h"
#include "menuoption.h"
#include "ui.h"

class MenuScreen : public Screen {
  public:
    MenuScreen();
    inline ~MenuScreen() {};

    void buttonUp();
    void buttonDown();
    void buttonLeft();
    void buttonRight();
    void buttonCenter();
    void buttonNone();

  private:
    std::vector<MenuOption> menuOptions;
};
#endif
