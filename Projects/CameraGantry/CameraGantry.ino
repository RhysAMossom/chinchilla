// Because the arduino IDE is annoying
#include <LiquidCrystal.h>
#include <StandardCplusplus.h>
#include <vector>

#include "ui.h"
#include "motor.h"
#include "mainscreen.h"
#include "menuscreen.h"

// Initialize Motor
#define MOTOR_BREAK_A 16
#define MOTOR_DIR_A 12
#define MOTOR_A_MOVE 3
#define MOTOR_BREAK_B 15
#define MOTOR_DIR_B 13
#define MOTOR_B_MOVE 11

bool direction = false;
uint16_t steps = 0;
uint16_t steps_per_mm = 0;

#define ENDSTOP_1_PIN 2
#define ENDSTOP_2_PIN 3
volatile int endstop_1_state = LOW;
volatile int endstop_2_state = LOW;

void endstop1() { endstop_1_state = digitalRead(ENDSTOP_1_PIN); }
void endstop2() { endstop_2_state = digitalRead(ENDSTOP_2_PIN); }

Screen* currentScreen;
UI* ui;
MainScreen* mainScreen;
Motor* motor;


void setup() {
  // Endstops Interrupts
  attachInterrupt(0, endstop1, CHANGE);
  attachInterrupt(1, endstop2, CHANGE);

  ui = new UI();
  mainScreen = new MainScreen();

  motor = new Motor(MOTOR_BREAK_A, MOTOR_DIR_A, MOTOR_A_MOVE,
                    MOTOR_BREAK_B, MOTOR_DIR_B, MOTOR_B_MOVE);

  mainScreen->show();
  currentScreen = mainScreen;

}

void loop(){
  ui->readButtons();
  int button = ui->getButton();
  ui->setTitle(currentScreen->getTitle());
  ui->setSubtext(currentScreen->getSubtext());
  switch (button) {
    case BUTTON_NONE:
      currentScreen->buttonNone();
      break;
    case BUTTON_RIGHT:
      currentScreen->buttonRight();
      break;
    case BUTTON_UP:
      currentScreen->buttonUp();
      break;
    case BUTTON_DOWN:
      currentScreen->buttonDown();
      break;
    case BUTTON_LEFT:
      currentScreen->buttonLeft();
      break;
    case BUTTON_SELECT:
      currentScreen->buttonCenter();
      break;
    default:
      ui->setSubtext("UNCAUGHT BUTTON ERR");
  }  


}

