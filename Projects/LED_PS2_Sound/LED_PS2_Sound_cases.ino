/*
 * LED & Sound with PS2 control strip program
 * Author: Carlos Chinchilla
 * 2013-2015
 

*/

/********************** State Machine *********************************/
void loop(){
#ifndef TESTING_EFFECT

#ifdef USE_PS2_CONTROLLER
#include "ps2_control.h"
#endif // USE_PS2_CONTROLLER  

/********************** Main Effects Routine **************************/  
repeats++;
int eq;
#ifdef DEBUG_LEDS
    // Report status on global variables
    Serial.print("Current effect: ");
    Serial.print(effect);
    Serial.print(" Continuous effects: ");
    Serial.print(continuous_flow);
    Serial.print(" Continuous themes: ");
    Serial.print(continuous_themes);
    Serial.print(" Repeat: ");
    Serial.print(repeats);
    Serial.print(" Speed: ");
    if (wait_factor)
      Serial.println("fast");
    else
      Serial.println("slow");
#endif

/********************** Effects State Machine *************************/  
#include "effects_state_machine.h"

/********************** Test Area *************************************/  
#else
#include "test_cases.h"
#endif // TESTING_EFFECT
}

/*
 * TO DO:
 * - figure out speed
 * - write routines for each state in state machine
 * - Paletes:
 * -- Candy Cane
 * -- Green and Blue (Rainforest)
 * - Starty sky
 * - Change license to closed source
 * - Button Effects to work on:
 * -- R2 Galaxy
 * -- R3 shift strip drawing
 * -- L3 draw
 * -- CROSS fast routine
 * -- TRIANGLE fade between colors
 * -- CIRCLE rainbows and coor palettes
 * -- SQUARE sound routines
 * -- SELECT choose color - needs testing
*/
