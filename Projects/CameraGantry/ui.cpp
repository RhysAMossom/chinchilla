#include <Arduino.h>

#include "ui.h"
#include "screenmanager.h"

UI::UI() :
  lcd(8, 13, 9, 4, 5, 6, 7),
  currentButton(BUTTON_NONE),
  lastButtonPressed(BUTTON_NONE),
  lastButton(BUTTON_NONE),
  lastTimeButtonPressed(0),
  debounceTime(100),
  numLines(2),
  numCharPerLine(16) {
    pinMode(LCD_LED_PIN,OUTPUT);
    lcd.begin(numCharPerLine,numLines);
    lcd.setCursor(0,0);
    lcd.clear();
    toggleLCD(true);
    BUTTON_ADC_VALUES[BUTTON_RIGHT] = BUTTONHYSTERESIS;
    BUTTON_ADC_VALUES[BUTTON_UP] = 145;
    BUTTON_ADC_VALUES[BUTTON_DOWN] = 329;
    BUTTON_ADC_VALUES[BUTTON_LEFT] = 505;
    BUTTON_ADC_VALUES[BUTTON_SELECT] = 741;
}

UI* UI::_ui = NULL;

UI* UI::instance() {
  if (!_ui) {
    _ui = new UI;
  }
  return _ui;
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

int UI::getButton() {
   int buttonVoltage = analogRead(BUTTON_ADC_PIN);
  
   // Parse analog signal to button pressed
   if (buttonVoltage <= BUTTON_ADC_VALUES[NUM_BUTTONS-1] + BUTTONHYSTERESIS) {
     //sense if the voltage falls within valid voltage windows
     for (int b = 0; b < NUM_BUTTONS; b++) {
       if(buttonVoltage >= (BUTTON_ADC_VALUES[b] - BUTTONHYSTERESIS)
          && buttonVoltage <= (BUTTON_ADC_VALUES[b] + BUTTONHYSTERESIS)) {
            return b;
          }
     }
   }
   return BUTTON_NONE;
}

void UI::readButtons() {
   int buttonReading = getButton();

   // If we detect a button press start timer
   if (buttonReading != lastButton) {
     lastTimeButtonPressed = millis();
   }
    
   // if time is up check status of button
   if (millis() - lastTimeButtonPressed > debounceTime) {
     if (buttonReading != currentButton) {
       // Catch On Press
       if((currentButton == BUTTON_NONE) && (buttonReading != BUTTON_NONE)) {
          lastButtonPressed = buttonReading;
          ScreenManager::instance()->buttonEvent(lastButtonPressed, true);
       }
       // Catch On Release but release last button pressed
       if((currentButton != BUTTON_NONE ) && (buttonReading == BUTTON_NONE)) {
         ScreenManager::instance()->buttonEvent(lastButtonPressed, false); 
       }
       currentButton = buttonReading;            
     }
   } else {
     // save reading for next iteration
     lastButton = buttonReading;
   }
}

