#include "mainscreen.h"

MainScreen::MainScreen(UI& ui) :
    Screen("","", ui) {
  setTitle("Main Screen");
  setSubtext("Main Screen Subtext");
  update();
}
