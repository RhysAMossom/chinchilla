#include "screen.h"

Screen::Screen(String title, String subtext, UI &ui) :
    visible(false),
    title(title),
    subtext(subtext) {
    ui = ui;
    update();
}

void Screen::buttonUp() { return; }
void Screen::buttonDown() { return; }
void Screen::buttonLeft() { return; }
void Screen::buttonRight() { return; }
void Screen::buttonCenter() { return; }

void Screen::hide() {
    visible = false;
}

void Screen::show() {
    visible = true;
    update();
}

void Screen::update() {
  if (visible) {
    ui->setTitle(title);
    ui->setSubtext(subtext);
  }
}

bool Screen::isVisible() {
    return visible;
}

void Screen::setTitle(String text) {
  title = text;
}

void Screen::setSubtext(String text) {
  subtext = text;
}
