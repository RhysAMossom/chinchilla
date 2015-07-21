#include "screen.h"

Screen::Screen() :
    visible(false),
    title(""),
    subtext("") {
}

void Screen::hide() {
    visible = false;
}

void Screen::show() {
    visible = true;
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

String Screen::getTitle() { return title; }

String Screen::getSubtext() { return subtext; }

