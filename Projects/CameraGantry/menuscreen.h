#ifndef CAMERAGANTRY_MENUSCREEN_HH
#define CAMERAGANTRY_MENUSCREEN_HH

#include <StandardCplusplus.h>
#include <vector>
#include "screen.h"
#include "menuoption.h"
#include "ui.h"
// forwared declaration
class MenuOption;

class MenuScreen : public Screen {
  public:
    MenuScreen();
    inline ~MenuScreen() {};

    void buttonUp();
    void buttonDown();
    void buttonLeft();
    void buttonRight();
    void buttonCenter();
    void noButton();

  private:
    std::vector<MenuOption> menuOptions;
};

#endif
