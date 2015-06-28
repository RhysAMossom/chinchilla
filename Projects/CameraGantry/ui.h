#ifndef CAMERAGANTRY_UI_HH
#define CAMERAGANTRY_UI_HH

#include <Arduino.h>
#include <LiquidCrystal.h>

#define LCD_LED_PIN 10
#define BUTTON_ADC_PIN A0
#define NUM_BUTTONS 5
#define BUTTONHYSTERESIS 10  // hysteresis for valid button sensing window
#define BUTTON_NONE -1
#define BUTTON_RIGHT 0
#define BUTTON_UP 1
#define BUTTON_DOWN 2
#define BUTTON_LEFT 3
#define BUTTON_SELECT 4

class UI {
  public:
    UI();
    inline ~UI() {};
    void readButtons();
    int getButton();
    void toggleLCD(bool state);
    void clearButtonFlags();
    bool isButtonPressed(int button);
    bool isButtonReleased();
    void setSubtext(String text);
    void setTitle(String text);

  private:
    void padAndPrintText(String text);
  
    int button;
    int previousButton;
    bool buttonPressed;
    bool buttonReleased;
    LiquidCrystal lcd;
    uint8_t numLines;
    uint8_t numCharPerLine;

  protected:
    int BUTTON_ADC_VALUES[NUM_BUTTONS];
};

#endif
