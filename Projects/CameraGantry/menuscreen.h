#ifndef CAMERAGANTRY_MENUSCREEN_H
#define CAMERAGANTRY_MENUSCREEN_H

#include <StandardCplusplus.h>
#include <vector>
#include "screen.h"
#include "menuoption.h"
#include "ui.h"

class MenuScreen : public Screen {
  public:
    static MenuScreen* instance();
    inline ~MenuScreen() {};

    void buttonUp(bool pressed);
    void buttonDown(bool pressed);
    void buttonLeft(bool pressed);
    void buttonRight(bool pressed);
    void buttonCenter(bool pressed);
    void buttonNone(bool pressed);

  private:
    std::vector<MenuOption> menuOptions;
    int currentOption;
    static MenuScreen* _menuScreen;
    MenuScreen();
};
#endif
