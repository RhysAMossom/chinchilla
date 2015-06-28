// Because the arduino IDE is annoying
#include <LiquidCrystal.h>
//#include <LCDKeypad.h>
#include <StandardCplusplus.h>
#include <vector>

#include "ui.h"
#include "motor.h"
#include "mainscreen.h"
#include "menuscreen.h"

#define ENDSTOP_1_PIN 2
#define ENDSTOP_2_PIN 3

// Initialize Motor
#define MOTOR_BREAK_A 9
#define MOTOR_DIR_A 12
#define MOTOR_A_MOVE 3
#define MOTOR_BREAK_B 8
#define MOTOR_DIR_B 13
#define MOTOR_B_MOVE 11
Motor motor = Motor(MOTOR_BREAK_A, MOTOR_DIR_A, MOTOR_A_MOVE,
              MOTOR_BREAK_B, MOTOR_DIR_B, MOTOR_B_MOVE);

bool direction = false;
uint16_t steps = 0;
uint16_t steps_per_mm = 0;

volatile int endstop_1_state = LOW;
volatile int endstop_2_state = LOW;

void endstop1() { endstop_1_state = digitalRead(ENDSTOP_1_PIN); }
void endstop2() { endstop_2_state = digitalRead(ENDSTOP_2_PIN); }

void setup() {
  // Endstops Interrupts
  attachInterrupt(0, endstop1, CHANGE);
  attachInterrupt(1, endstop2, CHANGE);

  // LCD Screen
  setupLCD();
}

void loop(){
  spinKey();
  lcd.print(key);
  lcd.setCursor(0,0);
}

