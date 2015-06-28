#ifndef CAMERAGANTRY_UI_HH
#define CAMERAGANTRY_UI_HH

#include <Arduino.h>
#include <LiquidCrystal.h>
//#include "LCDKeypad.h"

#define NUM_KEYS 5
#define KEYS_PIN 0
const int ADC_KEY_VALS[NUM_KEYS] = {50, 200, 400, 600, 800};
LiquidCrystal lcd(8, 13, 9, 4, 5, 6, 7);
int key=-1;

void setupLCD() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CameraGantry    ");
  lcd.print("   Starting up  ");
  for (char c = 0; c < 32; c++) {
    lcd.scrollDisplayLeft();
    delay(400);
  }
  lcd.clear();
  lcd.setCursor(0,0); 
}

// Convert ADC value to key number
int getKey() {
    int k;
    int input = analogRead(KEYS_PIN);
    for (k = 0; k < NUM_KEYS; k++)
      if (input < ADC_KEY_VALS[k]) return k;
    if (k >= NUM_KEYS)
      k = -1;  // No valid key pressed
    return k;
}

void spinKey() {
   if (getKey() != key) {
     delay(50);  // wait for debounce time
     int newKey = getKey();
     if (newKey != key) {
       key = newKey;
     }
   }
   delay(100);
}

#endif
