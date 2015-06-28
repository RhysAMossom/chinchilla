#include <Arduino.h>

#include "ui.h"

UI::UI() :
  lcd(8, 13, 9, 4, 5, 6, 7),
  button(BUTTON_NONE),
  previousButton(BUTTON_NONE),
  buttonPressed(false),
  buttonReleased(false),
  numLines(2),
  numCharPerLine(16) {
    pinMode(LCD_LED_PIN,OUTPUT);
    lcd.begin(numCharPerLine,numLines);
    lcd.setCursor(0,0);
    lcd.clear();
    toggleLCD(true);
    Serial.begin(9600);
    BUTTON_ADC_VALUES[BUTTON_RIGHT] = BUTTONHYSTERESIS;
    BUTTON_ADC_VALUES[BUTTON_UP] = 145;
    BUTTON_ADC_VALUES[BUTTON_DOWN] = 329;
    BUTTON_ADC_VALUES[BUTTON_LEFT] = 505;
    BUTTON_ADC_VALUES[BUTTON_SELECT] = 741;
}

void UI::setTitle(String text) {
  lcd.setCursor(0,0);
  padAndPrintText(text);
}

void UI::setSubtext(String text) {
  lcd.setCursor(0,1);
  padAndPrintText(text);
}

void UI::padAndPrintText(String text) {
  for (int c = text.length(); c < numCharPerLine; c++) {
    text += " ";
  }
  lcd.print(text);
}

void UI::toggleLCD(bool state) {
  digitalWrite(LCD_LED_PIN, state);
}

int UI::getButton() { return button; }

void UI::readButtons() {
   int buttonVoltage = analogRead(BUTTON_ADC_PIN);
  
   if (buttonVoltage <= BUTTON_ADC_VALUES[NUM_BUTTONS-1] + BUTTONHYSTERESIS) {
     //sense if the voltage falls within valid voltage windows
     for (int b = 0; b < NUM_BUTTONS; b++) {
       if(buttonVoltage >= (BUTTON_ADC_VALUES[b] - BUTTONHYSTERESIS)
          && buttonVoltage <= (BUTTON_ADC_VALUES[b] + BUTTONHYSTERESIS)) {
            button = b;
            break;
          }
     }
   } else {
     button = BUTTON_NONE; 
   }
   // Catch On Press
   if((previousButton == BUTTON_NONE) && (button != BUTTON_NONE)) {
      //it's the duty of the receiver to clear these flags if it wants to detect a new button change event
      buttonPressed  = true;
      buttonReleased = false;
   }
   // Catch On Release
   if((previousButton != BUTTON_NONE ) && ( button == BUTTON_NONE)) {
      buttonPressed  = false;
      buttonReleased = true;
   }
   previousButton = button;
}

void UI::clearButtonFlags() {
  buttonPressed  = false;
  buttonReleased = false;
}

bool UI::isButtonPressed(int buttonIn) {
  return (buttonIn == button && buttonPressed);
}

bool UI::isButtonReleased() {
  return (buttonReleased);
}
