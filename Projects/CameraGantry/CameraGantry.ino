// Because the arduino IDE is annoying
#include <LiquidCrystal.h>
#include <StandardCplusplus.h>
#include <vector>

#include "ui.h"
#include "motor.h"
#include "mainscreen.h"
#include "menuscreen.h"

UI ui = UI();

MainScreen mainScreen(ui);

// Initialize Motor
#define MOTOR_BREAK_A 16
#define MOTOR_DIR_A 12
#define MOTOR_A_MOVE 3
#define MOTOR_BREAK_B 15
#define MOTOR_DIR_B 13
#define MOTOR_B_MOVE 11
Motor motor = Motor(MOTOR_BREAK_A, MOTOR_DIR_A, MOTOR_A_MOVE,
              MOTOR_BREAK_B, MOTOR_DIR_B, MOTOR_B_MOVE);

bool direction = false;
uint16_t steps = 0;
uint16_t steps_per_mm = 0;

#define ENDSTOP_1_PIN 2
#define ENDSTOP_2_PIN 3
volatile int endstop_1_state = LOW;
volatile int endstop_2_state = LOW;

void endstop1() { endstop_1_state = digitalRead(ENDSTOP_1_PIN); }
void endstop2() { endstop_2_state = digitalRead(ENDSTOP_2_PIN); }

void setup() {
  // Endstops Interrupts
  attachInterrupt(0, endstop1, CHANGE);
  attachInterrupt(1, endstop2, CHANGE);
}

void loop(){
}

