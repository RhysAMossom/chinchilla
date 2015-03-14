#ifndef PS2_CONTROL_H
#define PS2_CONTROL_H

ps2x.read_gamepad(); //read controller
  
/********************** Non-Blocking Cases ****************************/
  if(ps2x.ButtonPressed(PSB_START)){
    //Toggle effect continuity
    continuous_flow = !continuous_flow;
  }
  else if(ps2x.ButtonPressed(PSB_L1)) {
#ifdef DEBUG_LEDS
    Serial.println("Pressed L1");
#endif
    // Flash random color
    backup();
    flash_and_dim(random_color(),10*wait_factor,10,10);
    FastLED.delay(100);
    restore();
  }
  else if(ps2x.ButtonPressed(PSB_L2)) {
#ifdef DEBUG_LEDS
    Serial.println("Pressed L2");
#endif
    // flash black
    backup();
    all_off();
    FastLED.delay(10*wait_factor);
    restore();
  }
  else if(ps2x.ButtonPressed(PSB_L3)) {
#ifdef DEBUG_LEDS
    Serial.println("Pressed L3");
#endif
    // Draw dragging a single pixel with brightness control
    // Press CROSS to save press SQUARE when done.
  }
  else if(ps2x.ButtonPressed(PSB_R1)) {
#ifdef DEBUG_LEDS
    Serial.println("Pressed R1");
#endif
    // Explosion
    uint16_t led = random(0,NUM_LEDS-1);
    explosion(random_color(), strip[led], led, random(10,50),false);
  }
  else if(ps2x.ButtonPressed(PSB_R2)) {
#ifdef DEBUG_LEDS
    Serial.println("Pressed R2");
#endif
    // Galaxia
    strip[random(0,NUM_LEDS-1)] = random_color();
    strip[random(0,NUM_LEDS-1)] = random_color();
    strip[random(0,NUM_LEDS-1)] = random_color();
  }
  else if(ps2x.ButtonPressed(PSB_R3)) {
#ifdef DEBUG_LEDS
    Serial.println("Pressed R3");
#endif
    // Shift strip drawing and adjust brightness
  }
  else if(ps2x.ButtonPressed(PSB_PAD_LEFT)) {
#ifdef DEBUG_LEDS
    Serial.println("Pressed pad left");
#endif
    // Previous effect
    effect -= 2;
  }
  else if(ps2x.ButtonPressed(PSB_PAD_RIGHT)) {
#ifdef DEBUG_LEDS
    Serial.println("Pressed pad right");
#endif
    // Next Effect
    effect++;
  }
  
  // Speed control
  if(ps2x.ButtonPressed(PSB_PAD_DOWN) || ps2x.ButtonPressed(PSB_PAD_UP)){
    if(ps2x.ButtonPressed(PSB_PAD_UP)) {
      // Increase speed
      wait_factor = (wait_factor - 50 < wait_factor) ? wait_factor - 50 : 0;
#ifdef DEBUG_LEDS
      Serial.println("Pressed pad up");
      Serial.print("Wait factor: ");
      Serial.println(wait_factor);    
#endif
    }
    else{
      // Decrease speed
      wait_factor = (wait_factor + 50 > wait_factor) ? wait_factor + 50: 255;
#ifdef DEBUG_LEDS
      Serial.println("Pressed pad down");
      Serial.print("Wait factor: ");
      Serial.println(wait_factor);
#endif
    }
    flash(0x0000FF,200);
    delay(100+wait_factor*3);
    flash(0x0000FF,200);
    delay(500);
  }
  
/********************** Blocking Cases ********************************/  
  else if(ps2x.ButtonPressed(PSB_SELECT)) {
    uint8_t LY, LX, RY, RX;
    // Select RBG colors from joystic values
#ifdef DEBUG_LEDS
    Serial.println("Ly\tLx\tRy\tRx");
#endif
    delay(50);
    ps2x.read_gamepad();
    while(!ps2x.ButtonPressed(PSB_L1)){
      //exit loop pressing L1
      if (ps2x.ButtonPressed(PSB_START)){
    // Turn all off if START is pressed after SELECT
#ifdef DEBUG_LEDS
        Serial.println("all off");
#endif
        effect = WAIT;
        LY = 0;
        LX = 0;
        RY = 0;
        RX = 0;
        break;
        }
      LY = ps2x.Analog(PSS_LY);
      LX = ps2x.Analog(PSS_LX);
      RY = ps2x.Analog(PSS_RY);
      RX = ps2x.Analog(PSS_RX);
#ifdef DEBUG_LEDS
      Serial.print(LY, DEC);
      Serial.print("\t");
      Serial.print(LX, DEC); 
      Serial.print("\t");
      Serial.print(RY, DEC); 
      Serial.print("\t");
      Serial.println(RX, DEC);
#endif
      // Set colors
      all_on(CRGB(LY, LX, RY));
      R = LY;
      B = LX;
      G = RY;
      
      // Read gamepad for 
      ps2x.read_gamepad();
      FastLED.delay(50);
    }
#ifdef DEBUG_LEDS
    Serial.println("done choosing colors");
#endif
    // Acknowledge selection
    flash(CRGB(LY, LX, RY),500);
    delay(500);
    flash(CRGB(LY, LX, RY),500);
    all_on(CRGB(LY, LX, RY));
    R = LY;
    G = LX;
    B = RY;
    // Stay on with that color
    effects = WAIT;
    continuous_flow = false;
  }
  else if(ps2x.ButtonPressed(PSB_TRIANGLE)) {
#ifdef DEBUG_LEDS
    Serial.println("Pressed triangle");
#endif
    // Fade between colors
    effects = FADE;
    continuous_flow = false;
  }
  else if(ps2x.ButtonPressed(PSB_CIRCLE)) {
#ifdef DEBUG_LEDS
    Serial.println("Pressed circle");
#endif
    // Rainbows and Palettes
    effects = RAINBOW;
    continuous_flow = false;
  }
  else if(ps2x.ButtonPressed(PSB_CROSS)) {
#ifdef DEBUG_LEDS
    Serial.println("Pressed cross");
#endif
    // Fast effects, flashes, and explosions
    effects = FLASH;
    continuous_flow = false;
  }
  else if(ps2x.ButtonPressed(PSB_SQUARE)) {
#ifdef DEBUG_LEDS
    Serial.println("Pressed square");
#endif
    // Sound sensitive routine
  }

#endif
