#include "screen.h"

Screen::Screen() :
  visible(false),
  title(""),
  subtext("") {
      ui = UI::instance();
}

void Screen::hide() {
  visible = false;
}

void Screen::show() {
  visible = true;
  ui->setTitle(title);
  ui->setSubtext(subtext);
}

bool Screen::isVisible() {
  return visible;
}

void Screen::setTitle(String text) {
  title = text;
  if (visible)
    ui->setTitle(title);
}

void Screen::setSubtext(String text) {
  subtext = text;
  if (visible)
    ui->setSubtext(subtext);
}

