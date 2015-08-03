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

void Screen::setTitle(const String& text) {
  title = text;
  if (isVisible())
    ui->setTitle(title);
}

void Screen::setSubtext(const String& text) {
  subtext = text;
  if (isVisible())
    ui->setSubtext(subtext);
}

