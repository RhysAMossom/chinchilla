/*
 * LED & Sound with PS2 control strip program
 * Author: Carlos Chinchilla
 * 2013-2014
 

*/

/********************** State Machine *********************************/
//#define TESTING_EFFECT
#ifndef TESTING_EFFECT
void loop(){
  ps2x.read_gamepad(); //read controller
  
/********************** Non-Blocking Cases ****************************/
  if(ps2x.ButtonPressed(PSB_START)){
    //Toggle effect continuity
    continuous_flow = !continuous_flow;
  }
    else if(ps2x.ButtonPressed(PSB_L1)) {
#ifdef DEBUG
    Serial.println("Pressed L1");
#endif
    // Flash random color
  }
  else if(ps2x.ButtonPressed(PSB_L2)) {
#ifdef DEBUG
    Serial.println("Pressed L2");
#endif
    // Flash from center to outside
  }
  else if(ps2x.ButtonPressed(PSB_L3)) {
#ifdef DEBUG
    Serial.println("Pressed L3");
#endif
    // Wipe with brightness control
  }
  else if(ps2x.ButtonPressed(PSB_R1)) {
#ifdef DEBUG
    Serial.println("Pressed R1");
#endif
    // Explosion
  }
  else if(ps2x.ButtonPressed(PSB_R2)) {
#ifdef DEBUG
    Serial.println("Pressed R2");
#endif
    // Single Dot
  }
  else if(ps2x.ButtonPressed(PSB_R3)) {
#ifdef DEBUG
    Serial.println("Pressed R3");
#endif
    // Shift strip drawing and adjust brightness
  }
  else if(ps2x.ButtonPressed(PSB_PAD_LEFT)) {
#ifdef DEBUG
    Serial.println("Pressed pad left");
#endif
    // Previous effect
    effect -= 2;
  }
  else if(ps2x.ButtonPressed(PSB_PAD_RIGHT)) {
#ifdef DEBUG
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
#ifdef DEBUG
      Serial.println("Pressed pad up");
      Serial.print("Wait factor: ");
      Serial.println(wait_factor);    
#endif
    }
    else{
      // Decrease speed
      wait_factor = (wait_factor + 50 > wait_factor) ? wait_factor + 50: 255;
#ifdef DEBUG
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
#ifdef DEBUG
    Serial.println("Ly\tLx\tRy\tRx");
#endif
    delay(50);
    ps2x.read_gamepad();
    while(!ps2x.ButtonPressed(PSB_SQUARE)){
      if (ps2x.ButtonPressed(PSB_CROSS)){
    // Turn all off if CROSS is pressed after SELECT
#ifdef DEBUG
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
#ifdef DEBUG
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
      // Read gamepad for 
      ps2x.read_gamepad();
      FastLED.delay(50);
    }
#ifdef DEBUG
    Serial.println("done choosing colors");
#endif
    // Acknowledge selection
    flash(CRGB(LY, LX, RY),500);
    delay(500);
    flash(CRGB(LY, LX, RY),500);
    all_on(CRGB(LY, LX, RY));
    // Stay on with that color
    while(!ps2x.ButtonPressed(PSB_START)){
      ps2x.read_gamepad();
      delay(100);
    }
    
  }
  else if(ps2x.ButtonPressed(PSB_TRIANGLE)) {
#ifdef DEBUG
    Serial.println("Pressed triangle");
#endif
    // Fade between colors
  }
  else if(ps2x.ButtonPressed(PSB_CIRCLE)) {
#ifdef DEBUG
    Serial.println("Pressed circle");
#endif
    // Rainbows and Palettes
  }
  else if(ps2x.ButtonPressed(PSB_CROSS)) {
#ifdef DEBUG
    Serial.println("Pressed cross");
#endif
    // Fast effects, flashes, and explosions
  }
  else if(ps2x.ButtonPressed(PSB_SQUARE)) {
#ifdef DEBUG
    Serial.println("Pressed square");
#endif
    // Sound sensitive routine
  }
  
/********************** Main Effects Routine **************************/  
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

  // Choose effect
  switch (effect) {
    // Handle theme boundaries
    case WAIT:
      // Wait for next serial command
      if(continuous_flow) effect++; break;
      
    case THEME_CHOOSER:
      switch(theme){
        case 0: //Red
          THEME_COLORS[0] = 0xFF0000;
          THEME_COLORS[1] = 0xA00000;
          THEME_COLORS[2] = 0x551010;
          THEME_COLORS[3] = 0xB01010;
          THEME_COLORS[4] = 0xDF4040;
          break;
        case 1: //Blue
          THEME_COLORS[0] = 0x3914AF;
          THEME_COLORS[1] = 0x111CB4;
          THEME_COLORS[2] = 0x060955;
          THEME_COLORS[3] = 0x247BFD;
          THEME_COLORS[4] = 0x0526DE;
          break;
        case 2: //Green
          THEME_COLORS[0] = 0x39E639;
          THEME_COLORS[1] = 0x00CC00;
          THEME_COLORS[2] = 0x002D00;
          THEME_COLORS[3] = 0x07E507;
          THEME_COLORS[4] = 0x269926;
          break;
        case 3: //Yellow
          THEME_COLORS[0] = 0xFFE500;
          THEME_COLORS[1] = 0xA69500;
          THEME_COLORS[2] = 0xFFF173;
          THEME_COLORS[3] = 0xFFFF00;
          THEME_COLORS[4] = 0xBFB130;
          break;
        case 4: // Purple
          THEME_COLORS[0] = 0x8001A0;
          THEME_COLORS[1] = 0xF000B0;
          THEME_COLORS[2] = 0x68006C;
          THEME_COLORS[3] = 0xFF00FF;
          THEME_COLORS[4] = 0x300021;
          break;
        case 5: //Fire
          THEME_COLORS[0] = 0x440000;
          THEME_COLORS[1] = 0xFF0500;
          THEME_COLORS[2] = 0xFF7300;
          THEME_COLORS[3] = 0xFFFF00;
          THEME_COLORS[4] = 0x771300;
          break;
        case 6: // Ice
          THEME_COLORS[0] = 0x44CCCC;
          THEME_COLORS[1] = 0x3AA6B0;
          THEME_COLORS[2] = 0xFF73FF;
          THEME_COLORS[3] = 0x3F3F3F;
          THEME_COLORS[4] = 0x0079AF;
          break;
        default: // Random color
          THEME_COLORS[0] = random_color();
          THEME_COLORS[1] = random_color();
          THEME_COLORS[2] = random_color();
          THEME_COLORS[3] = random_color();
          THEME_COLORS[4] = random_color();
          theme = 0;
      }
      if(continuous_themes) theme++; effect++; break;
    case RAINBOW:
      rainbow();
      delay(2000);
      if (repeats < 3){
        shift_strip(NUM_LEDS,20);
        continuous_flow = false;
        repeats++;
      }
      else{
        continuous_flow = true;
        repeats=0;
      }
      if(continuous_flow) effect++; break;
    case FLASH:
      flash(CRGB(R,G,B),500);
      delay(2000);
      if(continuous_flow) effect++; break;
    case WIPE:
      wipe_color(CRGB(R,G,B),5);
      wipe_color(CRGB::Black,5);
      if(continuous_flow) effect++; break;

    case 5:
          move_palette( random(1,10), NUM_LEDS,100, NUM_LEDS-1,0);
          
      if(continuous_flow) effect++; break;
    case 6:
          color_mixer(CRGB(0x000005),CRGB(0x090885),4*NUM_LEDS/5, NUM_LEDS-1);
          
      if(continuous_flow) effect++; break;
    case 7:
          color_mixer(CRGB(0x090885),CRGB(0x000005),3*NUM_LEDS/5,4*NUM_LEDS/5);
          
      if(continuous_flow) effect++; break;
    case 8:
          color_mixer(CRGB(0x000005),CRGB(0x090885),2*NUM_LEDS/5,3*NUM_LEDS/5);
          
      if(continuous_flow) effect++; break;
    case 9:
          color_mixer(CRGB(0x090885),CRGB(0x000005),NUM_LEDS/5,2*NUM_LEDS/5);
          
      if(continuous_flow) effect++; break;
    case 10:
          color_mixer(CRGB(0x000005),CRGB(0x090885),0,NUM_LEDS/5);
          FastLED.delay(1000);
          shift_strip(NUM_LEDS,100,0,NUM_LEDS-1);
          
      if(continuous_flow) effect++; break;
    case 11:
          rainbow();
          FastLED.delay(1000);
          shift_strip(NUM_LEDS,100,0,NUM_LEDS-1);
          shift_strip(NUM_LEDS,80,0,NUM_LEDS-1);
          shift_strip(NUM_LEDS,50,0,NUM_LEDS-1);
          shift_strip(NUM_LEDS,0,0,NUM_LEDS-1);
          
      if(continuous_flow) effect++; break;
    case 12:
          wipe_color(CRGB(0, 255, 0), 10, NUM_LEDS, 0); // Green
          
      if(continuous_flow) effect++; break;
    case 13:
          wipe_color(CRGB(0, 0, 255), 10, 0, NUM_LEDS-1); // Blue
          
      if(continuous_flow) effect++; break;
    case 14:
          wipe_color(CRGB(255, 0, 0), 10, NUM_LEDS, 0); // Red
          
      if(continuous_flow) effect++; break;
    case 15:
          flash_and_dim(THEME_COLORS[0],100,100,10,0,NUM_LEDS-1);
          FastLED.delay(300);
          
      if(continuous_flow) effect++; break;
    case 16:
          flash_and_dim(THEME_COLORS[1],150,120,10,0,NUM_LEDS-1);
          FastLED.delay(100);
          
      if(continuous_flow) effect++; break;
    case 17:
          flash_and_dim(THEME_COLORS[2],150,150,10,0,NUM_LEDS-1);
          FastLED.delay(100);
          
      if(continuous_flow) effect++; break;
    case 18:
          flash(THEME_COLORS[3],1000);
          FastLED.delay(200);
          
      if(continuous_flow) effect++; break;
    case 19:
          flash_and_dim(THEME_COLORS[4],150,18,8,0,NUM_LEDS-1);
          
      if(continuous_flow) effect++; break;
    case 20:
          if (repeats < 15){
            divided_inwards(random_color(),random_color(),10);
            continuous_flow = false;
            repeats++;
          }
          else{
            continuous_flow = true;
            repeats=0;
          }
          
      if(continuous_flow) effect++; break;
    case 21:
          blend(THEME_COLORS[1],80,10,0,NUM_LEDS-1);
          FastLED.delay(1000);
          
      if(continuous_flow) effect++; break;
    case 22:
          color_mixer(THEME_COLORS[2],CRGB::Black,0,NUM_LEDS-1);
          shift_strip(NUM_LEDS,10,NUM_LEDS-1,0);
          
      if(continuous_flow) effect++; break;
    case 23:
          explosion(THEME_COLORS[3],CRGB::Black,random(NUM_LEDS-1),15,false);
          FastLED.delay(500);
          
      if(continuous_flow) effect++; break;
    case 24:
          explosion(THEME_COLORS[1],CRGB::Black,random(NUM_LEDS-1),25,false);
          FastLED.delay(1000);
          
      if(continuous_flow) effect++; break;
    case 25:
          explosion(THEME_COLORS[0],CRGB::Black,random(NUM_LEDS-1),10,false);
          FastLED.delay(100);
          
      if(continuous_flow) effect++; break;
    case 26:
          explosion(THEME_COLORS[0],CRGB::Black,random(NUM_LEDS-1),10,false);
          FastLED.delay(1000);
          
      if(continuous_flow) effect++; break;
    case 27:
          explosion(THEME_COLORS[2],CRGB::Black,random(NUM_LEDS-1),10,false);
          FastLED.delay(100);
          
      if(continuous_flow) effect++; break;
    case 28:
          shift_strip(NUM_LEDS/6,70,0,NUM_LEDS-1);
          
      if(continuous_flow) effect++; break;
    case 29:
          shift_strip(NUM_LEDS/4,40,NUM_LEDS-1,0);
          explosion(THEME_COLORS[3],CRGB::Black,random(NUM_LEDS-1),35,false);
          
      if(continuous_flow) effect++; break;
    case 30:
          shift_strip(NUM_LEDS/2,35,0,NUM_LEDS-1);
          
      if(continuous_flow) effect++; break;
    case 31:
          shift_strip(NUM_LEDS,30,NUM_LEDS-1,0);
          explosion(THEME_COLORS[2],CRGB::Black,random(NUM_LEDS-1),35,false);
          
      if(continuous_flow) effect++; break;
    case 32:
          shift_strip(NUM_LEDS/2,25,0,NUM_LEDS-1);
          
      if(continuous_flow) effect++; break;
    case 33:
          shift_strip(NUM_LEDS/4,20,NUM_LEDS-1,0);
          explosion(THEME_COLORS[4],CRGB::Black,random(NUM_LEDS-1),25,false);
          
      if(continuous_flow) effect++; break;
    case 34:
          shift_strip(3*NUM_LEDS,15,NUM_LEDS-1,0);
          
      if(continuous_flow) effect++; break;
    case 35:
          blend(CRGB::Black,50,10,0,NUM_LEDS-1);
          FastLED.delay(1000);
          
      if(continuous_flow) effect++; break;
    case 36:
          flash(THEME_COLORS[3],500,3*NUM_LEDS/5, 4*NUM_LEDS/5);
          FastLED.delay(500);
          
      if(continuous_flow) effect++; break;
    case 37:
          flash(THEME_COLORS[4],500,4*NUM_LEDS/5, NUM_LEDS-1);
          FastLED.delay(500);
          
      if(continuous_flow) effect++; break;
    case 38:
          all_on(THEME_COLORS[0],4*NUM_LEDS/5, NUM_LEDS-1);
          all_on(THEME_COLORS[1],3*NUM_LEDS/5,4*NUM_LEDS/5);
          all_on(THEME_COLORS[2],2*NUM_LEDS/5,3*NUM_LEDS/5);
          all_on(THEME_COLORS[3],NUM_LEDS/5,2*NUM_LEDS/5);
          all_on(THEME_COLORS[4],0,NUM_LEDS/5);
          FastLED.delay(1000);
          all_off();
          
      if(continuous_flow) effect++; break;
    case 39:
          flash(THEME_COLORS[0],500,0,NUM_LEDS/5);
          FastLED.delay(1000);
          
      if(continuous_flow) effect++; break;
    case 40:
          flash(THEME_COLORS[1],500, NUM_LEDS/5,2*NUM_LEDS/5);
          FastLED.delay(400);
          
      if(continuous_flow) effect++; break;
    case 41:
          flash(THEME_COLORS[2],500,2*NUM_LEDS/5, 3*NUM_LEDS/5);
          FastLED.delay(350);
          
      if(continuous_flow) effect++; break;
    case 42:
          blend(CRGB(0x030250),50,10,0,NUM_LEDS-1);
          FastLED.delay(1000);
          all_off();
          
      if(continuous_flow) effect++; break;
    case 43:
          flash(THEME_COLORS[3],500,3*NUM_LEDS/5, 4*NUM_LEDS/5);
          FastLED.delay(500);
          
      if(continuous_flow) effect++; break;
    case 44:
          flash(THEME_COLORS[4],500,4*NUM_LEDS/5, NUM_LEDS-1);
          FastLED.delay(500);
          
      if(continuous_flow) effect++; break;
    case 45:
          flash(THEME_COLORS[0],500,0,NUM_LEDS/5);
          FastLED.delay(100);
          
      if(continuous_flow) effect++; break;
    case 46:
          flash(THEME_COLORS[2],500,2*NUM_LEDS/5, 3*NUM_LEDS/5);
          FastLED.delay(150);
          
      if(continuous_flow) effect++; break;
    case 47:
          flash(THEME_COLORS[3],500,3*NUM_LEDS/5, 4*NUM_LEDS/5);
          FastLED.delay(150);
          
      if(continuous_flow) effect++; break;
    case 48:
          flash(THEME_COLORS[4],500,4*NUM_LEDS/5, NUM_LEDS-1);
          FastLED.delay(100);
          
      if(continuous_flow) effect++; break;
    case 49:
          flash(THEME_COLORS[0],500,0,NUM_LEDS/5);
          FastLED.delay(100);
          
      if(continuous_flow) effect++; break;
    case 50:
          flash(THEME_COLORS[1],500, NUM_LEDS/5,2*NUM_LEDS/5);
          FastLED.delay(100);
          
      if(continuous_flow) effect++; break;
    case 51:
          flash(THEME_COLORS[2],500,2*NUM_LEDS/5, 3*NUM_LEDS/5);
          FastLED.delay(100);
          
      if(continuous_flow) effect++; break;
    case 52:
          flash(THEME_COLORS[3],500,3*NUM_LEDS/5, 4*NUM_LEDS/5);
          FastLED.delay(100);
          
      if(continuous_flow) effect++; break;
    case 53:
          flash(THEME_COLORS[4],500,4*NUM_LEDS/5, NUM_LEDS-1);
          FastLED.delay(100);
          
      if(continuous_flow) effect++; break;
    case 54:
          flash(THEME_COLORS[0],500,0,NUM_LEDS/5);
          FastLED.delay(10);
          
      if(continuous_flow) effect++; break;
    case 55:
          flash(THEME_COLORS[1],500, NUM_LEDS/5,2*NUM_LEDS/5);
          FastLED.delay(10);
          
      if(continuous_flow) effect++; break;
    case 56:
          flash(THEME_COLORS[2],450,2*NUM_LEDS/5, 3*NUM_LEDS/5);
          FastLED.delay(10);
          
      if(continuous_flow) effect++; break;
    case 57:
          flash(THEME_COLORS[3],450,3*NUM_LEDS/5, 4*NUM_LEDS/5);
          FastLED.delay(10);
          
      if(continuous_flow) effect++; break;
    case 58:
          flash(THEME_COLORS[4],450,4*NUM_LEDS/5, NUM_LEDS-1);
          FastLED.delay(10);
          
      if(continuous_flow) effect++; break;
    case 59:
          flash(THEME_COLORS[0],350,0,NUM_LEDS/5);
          
      if(continuous_flow) effect++; break;
    case 60:
          flash(THEME_COLORS[1],350, NUM_LEDS/5,2*NUM_LEDS/5);
          
      if(continuous_flow) effect++; break;
    case 61:
          flash(THEME_COLORS[2],400,2*NUM_LEDS/5, 3*NUM_LEDS/5);
          
      if(continuous_flow) effect++; break;
    case 62:
          flash(THEME_COLORS[3],300,3*NUM_LEDS/5, 4*NUM_LEDS/5);
          
      if(continuous_flow) effect++; break;
    case 63:
          flash(THEME_COLORS[4],300,4*NUM_LEDS/5, NUM_LEDS-1);
          
      if(continuous_flow) effect++; break;
    case 64:
          flash(THEME_COLORS[0],200,0,NUM_LEDS/5);
          
      if(continuous_flow) effect++; break;
    case 65:
          flash(THEME_COLORS[1],200, NUM_LEDS/5,2*NUM_LEDS/5);
          
      if(continuous_flow) effect++; break;
    case 66:
          flash(THEME_COLORS[2],100,2*NUM_LEDS/5, 3*NUM_LEDS/5);
          
      if(continuous_flow) effect++; break;
    case 67:
          flash(THEME_COLORS[3],100,3*NUM_LEDS/5, 4*NUM_LEDS/5);
          
      if(continuous_flow) effect++; break;
    case 68:
          flash(THEME_COLORS[4],50,4*NUM_LEDS/5, NUM_LEDS-1);
          
      if(continuous_flow) effect++; break;
    case 69:
          if (repeats < 15){
            flash(THEME_COLORS[0],75,0,NUM_LEDS/5);
            flash(THEME_COLORS[1],75, NUM_LEDS/5,2*NUM_LEDS/5);
            flash(THEME_COLORS[2],75,2*NUM_LEDS/5, 3*NUM_LEDS/5);
            flash(THEME_COLORS[3],75,3*NUM_LEDS/5, 4*NUM_LEDS/5);
            flash(THEME_COLORS[4],75,4*NUM_LEDS/5, NUM_LEDS-1);
            continuous_flow = false;
            repeats++;
          }
          else{
            continuous_flow = true;
            repeats=0;
          }
          
      if(continuous_flow) effect++; break;
    case 70:
          color_mixer(THEME_COLORS[4],CRGB::Black,0,NUM_LEDS-1);
          shift_strip(3*NUM_LEDS,5,0,NUM_LEDS-1);
          all_off();
          
      if(continuous_flow) effect++; break;
    case 71:
          if (repeats < 4){
            wipe_color(CRGB(0x044000<<repeats), 50, 0, 3*NUM_LEDS/8);
            wipe_color(CRGB(0x044000<<repeats), 50,NUM_LEDS,5*NUM_LEDS/8);
            explosion(CRGB::Black,THEME_COLORS[2],random(NUM_LEDS-1),100,false);
            shake();
            continuous_flow = false;
            repeats++;
          }
          else{
            continuous_flow = true;
            repeats=0;
          }
          
      if(continuous_flow) effect++; break;
    case 72:
          if (repeats < 15){
            divided_outwards(random_color(),random_color(),10);
            continuous_flow = false;
            repeats++;
          }
          else{
            continuous_flow = true;
            repeats=0;
          }
            
      if(continuous_flow) effect++; break;
    case 73:
          wipe_color(CRGB::Black, 25, NUM_LEDS,0);
          
      if(continuous_flow) effect++; break;
    case 74:
          wipe_color(THEME_COLORS[1],10,NUM_LEDS/6,5*NUM_LEDS/6);
          
      if(continuous_flow) effect++; break;
    case 75:
          wipe_color(CRGB(0x001515),10,NUM_LEDS/2,3*NUM_LEDS/6);
          
      if(continuous_flow) effect++; break;
    case 76:
          wipe_color(CRGB(0x502112),10,4*NUM_LEDS/6,NUM_LEDS-1);
          
      if(continuous_flow) effect++; break;
    case 77:
          wipe_color(THEME_COLORS[1],10,NUM_LEDS/10,NUM_LEDS/3);
          
      if(continuous_flow) effect++; break;
    case 78:
          wipe_color(CRGB(0xF5F000),10,2*NUM_LEDS/6,3*NUM_LEDS/6);
          
      if(continuous_flow) effect++; break;
    case 79:
          wipe_color(CRGB(0x1031F2),10,NUM_LEDS,5*NUM_LEDS/8);
          
      if(continuous_flow) effect++; break;
    case 80:
          wipe_color(CRGB(0xF020D1),10,0,NUM_LEDS/4);
          
      if(continuous_flow) effect++; break;
    case 81:
          wipe_color(CRGB(0x00F510),5,3*NUM_LEDS/4,NUM_LEDS/4);
          
      if(continuous_flow) effect++; break;
    case 82:
          all_off(2*NUM_LEDS/5,3*NUM_LEDS/5);
          
      if(continuous_flow) effect++; break;
    case 83:
          if (repeats < 15){
            divided_inwards(random_color(),random_color(),10);
            divided_outwards(random_color(),random_color(),10);
            continuous_flow = false;
            repeats++;
          }
          else{
            continuous_flow = true;
            repeats=0;
          }
          
      if(continuous_flow) effect++; break;
    case 84:
          flash(THEME_COLORS[4],500,2*NUM_LEDS/5,3*NUM_LEDS/5);
          explosion(THEME_COLORS[0],CRGB::Black,random(NUM_LEDS-1),10,false);
          
      if(continuous_flow) effect++; break;
    case 85:
          flash(THEME_COLORS[3],500,2*NUM_LEDS/5,3*NUM_LEDS/5);
          explosion(THEME_COLORS[2],CRGB::Black,random(NUM_LEDS-1),10,false);
          
      if(continuous_flow) effect++; break;
    case 86:
          flash(THEME_COLORS[0],500,2*NUM_LEDS/5,3*NUM_LEDS/5);
          explosion(THEME_COLORS[1],CRGB::Black,random(NUM_LEDS-1),10,false);
          
      if(continuous_flow) effect++; break;
    case 87:
          flash(THEME_COLORS[2],500,2*NUM_LEDS/5,3*NUM_LEDS/5);
          explosion(THEME_COLORS[3],CRGB::Black,random(NUM_LEDS-1),10,false);
          
      if(continuous_flow) effect++; break;
    case 88:
          flash(THEME_COLORS[1],500,2*NUM_LEDS/5,3*NUM_LEDS/5);
          explosion(THEME_COLORS[4],CRGB::Black,random(NUM_LEDS-1),10,false);
          
      if(continuous_flow) effect++; break;
    case 89:
          blend(THEME_COLORS[2],75,5,0,NUM_LEDS-1);
          FastLED.delay(2000);
          
      if(continuous_flow) effect++; break;
    case 90:
          blend(THEME_COLORS[3],55,5,0,NUM_LEDS-1);
          FastLED.delay(4000);
          
      if(continuous_flow) effect++; break;
    case 91:
          blend(THEME_COLORS[1],65,5,0,NUM_LEDS-1);
          FastLED.delay(3000);
          
      if(continuous_flow) effect++; break;
    case 92:
          blend(THEME_COLORS[4],45,5,0,NUM_LEDS-1);
          FastLED.delay(5000);
          
      if(continuous_flow) effect++; break;
    case 93:
          blend(THEME_COLORS[0],35,5,0,NUM_LEDS-1);
          FastLED.delay(1000);
          
      if(continuous_flow) effect++; break;
    case 94:
          blend(CRGB::Black,25,5,0,NUM_LEDS-1);
          
      if(continuous_flow) effect++; break;
    case 95:
          if (repeats < 25){
            cross_over(random_color(),random_color(),10);
            explosion(THEME_COLORS[4],CRGB::Black,random(NUM_LEDS-1),10,false);
            explosion(THEME_COLORS[1],CRGB::Black,random(NUM_LEDS-1),10,false);
            explosion(THEME_COLORS[2],CRGB::Black,random(NUM_LEDS-1),10,false);
            explosion(THEME_COLORS[3],CRGB::Black,random(NUM_LEDS-1),10,false);
            continuous_flow = false;
            repeats++;
          }
          else{
            continuous_flow = true;
            repeats=0;
          }
          
      if(continuous_flow) effect++; break;
    case 96:
          if (repeats < 25){
            flash_and_dim(random_color(),100-2*repeats,18,8,0,NUM_LEDS-1);
            FastLED.delay(700-(repeats*repeats));
            continuous_flow = false;
            repeats++;
          }
          else{
            continuous_flow = true;
            repeats=0;
          }
               
      if(continuous_flow) effect++; break;
    case 97:
          if (repeats < 25){
            flash_and_dim(random_color(),100,18,8,0,NUM_LEDS-1);
            FastLED.delay(200);
            continuous_flow = false;
            repeats++;
          }
          else{
            continuous_flow = true;
            repeats=0;
          }
          
      if(continuous_flow) effect++; break;
    case 98:
          if (repeats < 5){
                color_mixer(random_color(),random_color(),4*NUM_LEDS/5, NUM_LEDS-1);
                color_mixer(random_color(),random_color(),3*NUM_LEDS/5,4*NUM_LEDS/5);
                color_mixer(random_color(),random_color(),2*NUM_LEDS/5,3*NUM_LEDS/5);
                color_mixer(random_color(),random_color(),NUM_LEDS/5,2*NUM_LEDS/5);
                color_mixer(random_color(),random_color(),0,NUM_LEDS/5);
                FastLED.delay(2000);
                rainbow();
                FastLED.delay(2000);
                continuous_flow = false;
            repeats++;
          }
          else{
            continuous_flow = true;
            repeats=0;
          }     
      if(continuous_flow) effect++; break;
    case 255:
      effect = 5; break;      
    default:
#ifdef DEBUG_LEDS    
      Serial.println("default case");
#endif      
      all_off();
      effect = 5; 
  }
}

#else
void loop(){
  // Effect testing
  for (uint8_t i= 0; i< 25; i++){
    all_on(random_color());
    FastLED.delay(1000);
  }
  
  rainbow();
  if(repeats < 255){
    brightness = analogRead(ENVELOPE_PIN);
    FastLED.setBrightness(10*brightness);
    FastLED.show(); // is this necessary?
    continuous_flow = false;
    repeats++;
  }
  else{
    continuous_flow = true;
    repeats=0;
  }

  palette(random(1,15));

  if (repeats <10){
    continuous_flow = false;
    repeats++;
  }
  else{
    continuous_flow = true;
    repeats=0;
  }
  
  
  color_mixer(CRGB(0x000005),CRGB(0x090885),4*NUM_LEDS/5, NUM_LEDS-1);
  
  color_mixer(CRGB(0x090885),CRGB(0x000005),3*NUM_LEDS/5,4*NUM_LEDS/5);
  
  color_mixer(CRGB(0x000005),CRGB(0x090885),2*NUM_LEDS/5,3*NUM_LEDS/5);
  
  color_mixer(CRGB(0x090885),CRGB(0x000005),NUM_LEDS/5,2*NUM_LEDS/5);
  
  color_mixer(CRGB(0x000005),CRGB(0x090885),0,NUM_LEDS/5);
  FastLED.delay(1000);
  shift_strip(NUM_LEDS,100,0,NUM_LEDS-1);
  
  rainbow();
  FastLED.delay(1000);
  shift_strip(NUM_LEDS,100,0,NUM_LEDS-1);
  shift_strip(NUM_LEDS,80,0,NUM_LEDS-1);
  shift_strip(NUM_LEDS,50,0,NUM_LEDS-1);
  shift_strip(NUM_LEDS,0,0,NUM_LEDS-1);
  
  wipe_color(CRGB(0, 255, 0), 10, NUM_LEDS, 0); // Green
  
  wipe_color(CRGB(0, 0, 255), 10, 0, NUM_LEDS-1); // Blue
  
  wipe_color(CRGB(255, 0, 0), 10, NUM_LEDS, 0); // Red
  
  flash_and_dim(THEME_COLORS[0],100,100,10,0,NUM_LEDS-1);
  FastLED.delay(300);
  
  flash_and_dim(THEME_COLORS[1],150,120,10,0,NUM_LEDS-1);
  FastLED.delay(100);
  
  flash_and_dim(THEME_COLORS[2],150,150,10,0,NUM_LEDS-1);
  FastLED.delay(100);
  
  flash(THEME_COLORS[3],1000);
  FastLED.delay(200);
  
  flash_and_dim(THEME_COLORS[4],150,18,8,0,NUM_LEDS-1);
  
  if (repeats < 15){
    divided_inwards(random_color(),random_color(),10);
    continuous_flow = false;
    repeats++;
  }
  else{
    continuous_flow = true;
    repeats=0;
  }
  
  blend(THEME_COLORS[1],80,10,0,NUM_LEDS-1);
  FastLED.delay(1000);
  
  color_mixer(THEME_COLORS[2],CRGB::Black,0,NUM_LEDS-1);
  shift_strip(NUM_LEDS,10,NUM_LEDS-1,0);
  
  explosion(THEME_COLORS[3],CRGB::Black,random(NUM_LEDS-1),15,false);
  FastLED.delay(500);
  
  explosion(THEME_COLORS[1],CRGB::Black,random(NUM_LEDS-1),25,false);
  FastLED.delay(1000);
  
  explosion(THEME_COLORS[0],CRGB::Black,random(NUM_LEDS-1),10,false);
  FastLED.delay(100);
  
  explosion(THEME_COLORS[0],CRGB::Black,random(NUM_LEDS-1),10,false);
  FastLED.delay(1000);
  
  explosion(THEME_COLORS[2],CRGB::Black,random(NUM_LEDS-1),10,false);
  FastLED.delay(100);
  
  shift_strip(NUM_LEDS/6,70,0,NUM_LEDS-1);
  
  shift_strip(NUM_LEDS/4,40,NUM_LEDS-1,0);
  explosion(THEME_COLORS[3],CRGB::Black,random(NUM_LEDS-1),25,false);
  
  shift_strip(NUM_LEDS/2,35,0,NUM_LEDS-1);
  
  shift_strip(NUM_LEDS,30,NUM_LEDS-1,0);
  explosion(THEME_COLORS[2],CRGB::Black,random(NUM_LEDS-1),25,false);
  
  shift_strip(NUM_LEDS/2,25,0,NUM_LEDS-1);
  
  shift_strip(NUM_LEDS/4,20,NUM_LEDS-1,0);
  explosion(THEME_COLORS[4],CRGB::Black,random(NUM_LEDS-1),25,false);
  
  shift_strip(3*NUM_LEDS,15,NUM_LEDS-1,0);
  
  blend(CRGB::Black,50,10,0,NUM_LEDS-1);
  FastLED.delay(1000);
  
  flash(THEME_COLORS[3],500,3*NUM_LEDS/5, 4*NUM_LEDS/5);
  FastLED.delay(500);
  
  flash(THEME_COLORS[4],500,4*NUM_LEDS/5, NUM_LEDS-1);
  FastLED.delay(500);
  
  all_on(THEME_COLORS[0],4*NUM_LEDS/5, NUM_LEDS-1);
  all_on(THEME_COLORS[1],3*NUM_LEDS/5,4*NUM_LEDS/5);
  all_on(THEME_COLORS[2],2*NUM_LEDS/5,3*NUM_LEDS/5);
  all_on(THEME_COLORS[3],NUM_LEDS/5,2*NUM_LEDS/5);
  all_on(THEME_COLORS[4],0,NUM_LEDS/5);
  FastLED.delay(1000);
  all_off();
  
  flash(THEME_COLORS[0],500,0,NUM_LEDS/5);
  FastLED.delay(1000);
  
  flash(THEME_COLORS[1],500, NUM_LEDS/5,2*NUM_LEDS/5);
  FastLED.delay(400);
  
  flash(THEME_COLORS[2],500,2*NUM_LEDS/5, 3*NUM_LEDS/5);
  FastLED.delay(350);
  
  blend(CRGB(0x030250),50,10,0,NUM_LEDS-1);
  FastLED.delay(1000);
  all_off();
  
  flash(THEME_COLORS[3],500,3*NUM_LEDS/5, 4*NUM_LEDS/5);
  FastLED.delay(500);
  
  flash(THEME_COLORS[4],500,4*NUM_LEDS/5, NUM_LEDS-1);
  FastLED.delay(500);
  
  flash(THEME_COLORS[0],500,0,NUM_LEDS/5);
  FastLED.delay(100);
  
  flash(THEME_COLORS[2],500,2*NUM_LEDS/5, 3*NUM_LEDS/5);
  FastLED.delay(150);
  
  flash(THEME_COLORS[3],500,3*NUM_LEDS/5, 4*NUM_LEDS/5);
  FastLED.delay(150);
  
  flash(THEME_COLORS[4],500,4*NUM_LEDS/5, NUM_LEDS-1);
  FastLED.delay(100);
  
  flash(THEME_COLORS[0],500,0,NUM_LEDS/5);
  FastLED.delay(100);
  
  flash(THEME_COLORS[1],500, NUM_LEDS/5,2*NUM_LEDS/5);
  FastLED.delay(100);
  
  flash(THEME_COLORS[2],500,2*NUM_LEDS/5, 3*NUM_LEDS/5);
  FastLED.delay(100);
  
  flash(THEME_COLORS[3],500,3*NUM_LEDS/5, 4*NUM_LEDS/5);
  FastLED.delay(100);
  
  flash(THEME_COLORS[4],500,4*NUM_LEDS/5, NUM_LEDS-1);
  FastLED.delay(100);
  
  flash(THEME_COLORS[0],500,0,NUM_LEDS/5);
  FastLED.delay(10);
  
  flash(THEME_COLORS[1],500, NUM_LEDS/5,2*NUM_LEDS/5);
  FastLED.delay(10);
  
  flash(THEME_COLORS[2],450,2*NUM_LEDS/5, 3*NUM_LEDS/5);
  FastLED.delay(10);
  
  flash(THEME_COLORS[3],450,3*NUM_LEDS/5, 4*NUM_LEDS/5);
  FastLED.delay(10);
  
  flash(THEME_COLORS[4],450,4*NUM_LEDS/5, NUM_LEDS-1);
  FastLED.delay(10);
  
  flash(THEME_COLORS[0],350,0,NUM_LEDS/5);
  
  flash(THEME_COLORS[1],350, NUM_LEDS/5,2*NUM_LEDS/5);
  
  flash(THEME_COLORS[2],400,2*NUM_LEDS/5, 3*NUM_LEDS/5);
  
  flash(THEME_COLORS[3],300,3*NUM_LEDS/5, 4*NUM_LEDS/5);
  
  flash(THEME_COLORS[4],300,4*NUM_LEDS/5, NUM_LEDS-1);
  
  flash(THEME_COLORS[0],200,0,NUM_LEDS/5);
  
  flash(THEME_COLORS[1],200, NUM_LEDS/5,2*NUM_LEDS/5);
  
  flash(THEME_COLORS[2],100,2*NUM_LEDS/5, 3*NUM_LEDS/5);
  
  flash(THEME_COLORS[3],100,3*NUM_LEDS/5, 4*NUM_LEDS/5);
  
  flash(THEME_COLORS[4],50,4*NUM_LEDS/5, NUM_LEDS-1);
  
  if (repeats < 15){
    flash(THEME_COLORS[0],75,0,NUM_LEDS/5);
    flash(THEME_COLORS[1],75, NUM_LEDS/5,2*NUM_LEDS/5);
    flash(THEME_COLORS[2],75,2*NUM_LEDS/5, 3*NUM_LEDS/5);
    flash(THEME_COLORS[3],75,3*NUM_LEDS/5, 4*NUM_LEDS/5);
    flash(THEME_COLORS[4],75,4*NUM_LEDS/5, NUM_LEDS-1);
    continuous_flow = false;
    repeats++;
  }
  else{
    continuous_flow = true;
    repeats=0;
  }
  
  color_mixer(THEME_COLORS[4],CRGB::Black,0,NUM_LEDS-1);
  shift_strip(3*NUM_LEDS,5,0,NUM_LEDS-1);
  all_off();
  
  
  if (repeats < 4){
    wipe_color(CRGB(0x044000<<repeats), 50, 0, 3*NUM_LEDS/8);
    wipe_color(CRGB(0x044000<<repeats), 50,NUM_LEDS,5*NUM_LEDS/8);
    explosion(CRGB::Black,THEME_COLORS[2],random(NUM_LEDS-1),100,false);
    shake();
    continuous_flow = false;
    repeats++;
  }
  else{
    continuous_flow = true;
    repeats=0;
  }
  
  
  if (repeats < 15){
    divided_outwards(random_color(),random_color(),10);
    continuous_flow = false;
    repeats++;
  }
  else{
    continuous_flow = true;
    repeats=0;
  }
    
  wipe_color(CRGB::Black, 25, NUM_LEDS,0);
  
  wipe_color(THEME_COLORS[1],10,NUM_LEDS/6,5*NUM_LEDS/6);
  
  wipe_color(CRGB(0x001515),10,NUM_LEDS/2,3*NUM_LEDS/6);
  
  wipe_color(CRGB(0x502112),10,4*NUM_LEDS/6,NUM_LEDS-1);
  
  wipe_color(THEME_COLORS[1],10,NUM_LEDS/10,NUM_LEDS/3);
  
  wipe_color(CRGB(0xF5F000),10,2*NUM_LEDS/6,3*NUM_LEDS/6);
  
  wipe_color(CRGB(0x1031F2),10,NUM_LEDS,5*NUM_LEDS/8);
  
  wipe_color(CRGB(0xF020D1),10,0,NUM_LEDS/4);
  
  wipe_color(CRGB(0x00F510),5,3*NUM_LEDS/4,NUM_LEDS/4);
  
  all_off(2*NUM_LEDS/5,3*NUM_LEDS/5);
  
  if (repeats < 15){
    divided_inwards(random_color(),random_color(),10);
    divided_outwards(random_color(),random_color(),10);
    continuous_flow = false;
    repeats++;
  }
  else{
    continuous_flow = true;
    repeats=0;
  }
  
  flash(THEME_COLORS[4],500,2*NUM_LEDS/5,3*NUM_LEDS/5);
  explosion(THEME_COLORS[0],CRGB::Black,random(NUM_LEDS-1),10,false);
  
  flash(THEME_COLORS[3],500,2*NUM_LEDS/5,3*NUM_LEDS/5);
  explosion(THEME_COLORS[2],CRGB::Black,random(NUM_LEDS-1),10,false);
  
  flash(THEME_COLORS[0],500,2*NUM_LEDS/5,3*NUM_LEDS/5);
  explosion(THEME_COLORS[1],CRGB::Black,random(NUM_LEDS-1),10,false);
  
  flash(THEME_COLORS[2],500,2*NUM_LEDS/5,3*NUM_LEDS/5);
  explosion(THEME_COLORS[3],CRGB::Black,random(NUM_LEDS-1),10,false);
  
  flash(THEME_COLORS[1],500,2*NUM_LEDS/5,3*NUM_LEDS/5);
  explosion(THEME_COLORS[4],CRGB::Black,random(NUM_LEDS-1),10,false);
  
  blend(THEME_COLORS[2],75,5,0,NUM_LEDS-1);
  FastLED.delay(2000);
  
  blend(THEME_COLORS[3],55,5,0,NUM_LEDS-1);
  FastLED.delay(4000);
  
  blend(THEME_COLORS[1],65,5,0,NUM_LEDS-1);
  FastLED.delay(3000);
  
  blend(THEME_COLORS[4],45,5,0,NUM_LEDS-1);
  FastLED.delay(5000);
  
  blend(THEME_COLORS[0],35,5,0,NUM_LEDS-1);
  FastLED.delay(1000);
  
  blend(CRGB::Black,25,5,0,NUM_LEDS-1);
  
  if (repeats < 25){
    cross_over(random_color(),random_color(),10);
    explosion(THEME_COLORS[4],CRGB::Black,random(NUM_LEDS-1),10,false);
    explosion(THEME_COLORS[1],CRGB::Black,random(NUM_LEDS-1),10,false);
    explosion(THEME_COLORS[2],CRGB::Black,random(NUM_LEDS-1),10,false);
    explosion(THEME_COLORS[3],CRGB::Black,random(NUM_LEDS-1),10,false);
    continuous_flow = false;
    repeats++;
  }
  else{
    continuous_flow = true;
    repeats=0;
  }
  
  if (repeats < 25){
    flash_and_dim(random_color(),100-2*repeats,18,8,0,NUM_LEDS-1);
    FastLED.delay(700-(repeats*repeats));
    continuous_flow = false;
    repeats++;
  }
  else{
    continuous_flow = true;
    repeats=0;
  }
       
  if (repeats < 25){
    flash_and_dim(random_color(),100,18,8,0,NUM_LEDS-1);
    FastLED.delay(200);
    continuous_flow = false;
    repeats++;
  }
  else{
    continuous_flow = true;
    repeats=0;
  }
  
  if (repeats < 5){
        color_mixer(random_color(),random_color(),4*NUM_LEDS/5, NUM_LEDS-1);
        color_mixer(random_color(),random_color(),3*NUM_LEDS/5,4*NUM_LEDS/5);
        color_mixer(random_color(),random_color(),2*NUM_LEDS/5,3*NUM_LEDS/5);
        color_mixer(random_color(),random_color(),NUM_LEDS/5,2*NUM_LEDS/5);
        color_mixer(random_color(),random_color(),0,NUM_LEDS/5);
        FastLED.delay(2000);
        rainbow();
        FastLED.delay(2000);
        continuous_flow = false;
    repeats++;
  }
  else{
    continuous_flow = true;
    repeats=0;
  }
 
}
#endif
  

/*
 * TO DO:
 * - figure out speed
 * - Solder wires together
 * - Paletes:
 * -- Candy Cane
 * -- Green and Blue (Rainforest)
 * - Change license to closed source
*/
