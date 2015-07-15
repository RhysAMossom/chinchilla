#include "mainscreen.h"

MainScreen::MainScreen() :
    Screen() {
  setTitle("Main Screen");
  setSubtext("MS Subtext");
}

void MainScreen::buttonUp() {
  setSubtext("MS buttonUp");
}
  
void MainScreen::buttonDown() {
  setSubtext("MS buttonDown");
}

void MainScreen::buttonLeft() {
  setSubtext("MS buttonLeft");
}

void MainScreen::buttonRight() {
  setSubtext("MS buttonRight");
}

void MainScreen::buttonCenter() {
  setSubtext("MS buttonRight");
}

void MainScreen::buttonNone() {
  setSubtext("MS no button");
}


