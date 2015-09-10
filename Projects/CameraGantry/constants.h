#ifndef CAMERAGANTRY_CONSTANTS_H
#define CAMERAGANTRY_CONSTANTS_H

// Pins used by LCD:
// lcd(8, 13, 9, 4, 5, 6, 7),

// Motor defines
#define STEPS_PER_MM 40
#define STEPS_PER_REVOLUTION 40

#define MOTOR_PIN_1 52
#define MOTOR_PIN_2 50
#define MOTOR_PIN_3 48
#define MOTOR_PIN_4 46

// at 200 steps per rev, speeds above 100 RMPs makes motor skip steps
// 100 RPMs @ 200 steps/rev = 20,000 steps/min ~= 333 steps/sec ~= 20 mm/s
#define MAX_SPEED_MM_PER_S 15
#define MIN_SPEED_MM_PER_S 1
#define DEFAULT_SPEED_MM_PER_S 5
#define DEFAULT_DISTANCE_MM 270
#define MAX_DISTANCE_MM 270
#define MAX_STEP_DISTANCE_MM 270
#define DEFAULT_STEP_DISTANCE_MM 10
#define DEFAULT_STEP_TIME_INTERVAL_MS 5000
#define MAX_STEP_TIME_INTERVAL_S 3600

// Enstop pins
#define ENDSTOP_1_PIN 20
#define ENDSTOP_2_PIN 21

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

#endif // CAMERAGANTRY_CONSTANTS_H
