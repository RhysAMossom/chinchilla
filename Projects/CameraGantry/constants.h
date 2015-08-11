#ifndef CAMERAGANTRY_CONSTANTS_H
#define CAMERAGANTRY_CONSTANTS_H

// Motor defines
#define STEPS_PER_MM 27
#define STEPS_PER_REVOLUTION 200

#define MOTOR_BREAK_A 16
#define MOTOR_DIR_A 12
#define MOTOR_A_MOVE 3
#define MOTOR_BREAK_B 15
#define MOTOR_DIR_B 13
#define MOTOR_B_MOVE 11

// at 200 steps per rev, speeds above 100 RMPs makes motor skip steps
// 100 RPMs @ 200 steps/rev = 20,000 steps/min ~= 333 steps/sec ~= 20 mm/s
#define MAX_SPEED_MM_PER_S 15
#define MIN_SPEED_MM_PER_S 1
#define DEFAULT_SPEED_MM_PER_S 5
#define DEFAULT_DISTANCE_MM 270
#define MAX_DISTANCE_MM 270

#define DEFAULT_STEP_DISTANCE_MM 10
#define DEFAULT_STEP_TIME_INTERVAL_MS 5000


// Enstop pins
#define ENDSTOP_1_PIN 2
#define ENDSTOP_2_PIN 3

#endif // CAMERAGANTRY_CONSTANTS_H