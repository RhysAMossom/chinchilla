#include "screen.h"

Screen::Screen(String text) :
    visible(false),
    mainText(text) {}

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
}

bool Screen::isVisible() {
    return visible;
}

void Screen::setText(String text) {
    mainText = text;
}
