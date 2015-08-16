#ifndef CAMERAGANTRY_UI_H
#define CAMERAGANTRY_UI_H

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "constants.h"

class UI {
  public:
    static UI* instance();
    inline ~UI() {};
    void readButtons();
    void toggleLCD(bool state);
    void setSubtext(const String& text);
    void setTitle(const String& text);

  private:
    void padAndPrintText(const String& text);

    int getButton();
    int currentButton;
    int lastButtonPressed;
    int lastButton;
    LiquidCrystal lcd;
    uint8_t numLines;
    uint8_t numCharPerLine;

  protected:
    int BUTTON_ADC_VALUES[NUM_BUTTONS];
    static UI* _ui;
    UI();
    long lastTimeButtonPressed;
    long debounceTime;
};

#endif
