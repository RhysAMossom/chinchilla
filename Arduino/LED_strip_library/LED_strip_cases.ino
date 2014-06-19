/*
 * LED strip program
 * Author: Carlos Chinchilla
 * 2013-2014
 * 
 * CIDERWARE LICENSE
 * The code is free to use and modify iff working with author in an 
 * awesome project If you find the code useful and see the author
 * chinchillin' at a bar you may thank him with a cold apple cider.
*/

/********************** PS2 Cases *****************************************/
#ifndef TESTING_EFFECT
void loop(){
  ps2x.read_gamepad(); //read controller
  
  // Cases Control
  if(ps2x.ButtonPressed(PSB_START)){
    if (continuous_flow){
      if (continuous_themes){
        // Was green turns yellow
        continuous_themes = false;
        flash(0xFFFF00,500);
        delay(500);
        flash(0xFFFF00,500);
        delay(500);
      }
      else {
        // was yellow turns red
        continuous_flow = false;
        flash(0xFF0000,500);
        delay(500);
        flash(0xFF0000,500);
        delay(500);
      }
    }
    else{
      // was red turns green
      continuous_themes = true;
      continuous_flow =  true;
      flash(0x009900,500);
      delay(500);
      flash(0x009900,500);
      delay(500);
      }
#ifdef DEBUG
    Serial.print("flow: ");
    Serial.print(continuous_flow);
    Serial.print("\tfamily flow: ");
    Serial.println(continuous_themes);
#endif
  }

  else if(ps2x.ButtonPressed(PSB_SELECT)) {
    uint8_t LY, LX, RY, RX;
    // Select RBG colors from joystic values
#ifdef DEBUG
    Serial.println("Exit with R1\nLy\tLx\tRy\tRx");
#endif
    delay(50);
    ps2x.read_gamepad();
    while(!ps2x.ButtonPressed(PSB_R1)){
      if (ps2x.ButtonPressed(PSB_L1)){
    // Turn all off if L1 is pressed after SELECT
#ifdef DEBUG
      Serial.println("all off");
#endif
        effect = 255;
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
      all_on(strip.Color(LY, LX, RY));
      // Read gamepad for 
      ps2x.read_gamepad();
      delay(50);
    }
#ifdef DEBUG
    Serial.println("done choosing colors");
#endif
    // Acknowledge selection
    flash(strip.Color(LY, LX, RY),500);
    delay(500);
    flash(strip.Color(LY, LX, RY),500);
    all_on(strip.Color(LY, LX, RY));
    // Stay on with that color
    while(!ps2x.ButtonPressed(PSB_START)){
      ps2x.read_gamepad();
      delay(100);
    }
    
  }
  // Effects Family Control
  else if(ps2x.ButtonPressed(PSB_TRIANGLE)) {
#ifdef DEBUG
    Serial.println("Pressed triangle");
#endif
    effect = TRIANGLE_THEME;
  }
  else if(ps2x.ButtonPressed(PSB_CIRCLE)) {
#ifdef DEBUG
    Serial.println("Pressed circle");
#endif
    effect = CIRCLE_THEME;
  }
  else if(ps2x.ButtonPressed(PSB_CROSS)) {
#ifdef DEBUG
    Serial.println("Pressed cross");
#endif
    effect = CROSS_THEME;
  }
  else if(ps2x.ButtonPressed(PSB_SQUARE)) {
#ifdef DEBUG
    Serial.println("Pressed square");
#endif
    effect = SQUARE_THEME;
  }
  else if(ps2x.ButtonPressed(PSB_L1)) {
#ifdef DEBUG
    Serial.println("Pressed L1");
#endif
    effect = L1_THEME;
  }
  else if(ps2x.ButtonPressed(PSB_L2)) {
#ifdef DEBUG
    Serial.println("Pressed L2");
#endif
    effect = L2_THEME;
  }
  else if(ps2x.ButtonPressed(PSB_L3)) {
#ifdef DEBUG
    Serial.println("Pressed L3");
#endif
    effect = L3_THEME;
  }
  else if(ps2x.ButtonPressed(PSB_R1)) {
#ifdef DEBUG
    Serial.println("Pressed R1");
#endif
    effect = R1_THEME;
  }
  else if(ps2x.ButtonPressed(PSB_R2)) {
#ifdef DEBUG
    Serial.println("Pressed R2");
#endif
    effect = R2_THEME;
  }
  else if(ps2x.ButtonPressed(PSB_R3)) {
#ifdef DEBUG
    Serial.println("Pressed R3");
#endif
    effect = R3_THEME;
  }
  else if(ps2x.ButtonPressed(PSB_PAD_LEFT)) {
#ifdef DEBUG
    Serial.println("Pressed pad left");
#endif
    effect -= 2;
  }
  else if(ps2x.ButtonPressed(PSB_PAD_RIGHT)) {
#ifdef DEBUG
    Serial.println("Pressed pad right");
#endif
    effect++;
  }
  
  // Speed control
  if(ps2x.ButtonPressed(PSB_PAD_DOWN) || ps2x.ButtonPressed(PSB_PAD_UP)){
    if(ps2x.ButtonPressed(PSB_PAD_UP)) {
      // Increase speed
      wait_factor = (wait_factor - 50 < wait_factor) ? wait_factor - 50 : SPEED_L;
#ifdef DEBUG
      Serial.println("Pressed pad up");
      Serial.print("Wait factor: ");
      Serial.println(wait_factor);    
#endif
    }
    else{
      // Decrease speed
      wait_factor = (wait_factor + 50 > wait_factor) ? wait_factor + 50: SPEED_H;
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
  
  // Parse serial input
    uint8_t c_in, num_bytes = Serial.available();    
    c_in = Serial.read();
    
    if (c_in == UID) {
      switch (num_bytes) {
        case 0:
          break;
        case 3:
          c_in = Serial.read();
          switch(c_in) {
            case RANDOM_COLOR:
              all_on(random_color());
              effect = WAIT;
              continuous_flow = false;
#ifdef DEBUG
              Serial.println("random color");
#endif
              break;
            case RANDOM_EFFECT:
              effect = random(1,255);
              break;
            case RAINBOW_EFFECT:
              rainbow();
              effect = WAIT;
              continuous_flow = false;
              break;
#ifdef DEBUG
            default: 
              Serial.println("unhandled buffer size 1");
#endif
          }
          break;
        case 4:
          c_in = Serial.read();
          switch(c_in) {
            case SPEED:
              c_in = Serial.read();
              if (c_in ==  FAST){
                if(wait_factor - 50 < wait_factor)
                  wait_factor -= 50;
                else
                  wait_factor = SPEED_L;
                }
              else if(c_in == SLOW){
                if(wait_factor + 50 > wait_factor)
                  wait_factor += 50;
                else
                  wait_factor = SPEED_H;
                }
              else
                wait_factor = SPEED_M;
              break;
            case EFFECT:
              effect = Serial.read();
              break;
            case THEME_SELECT:
              theme = Serial.read();
              effect = THEME_CHOOSER;
              break;  
            case TOGGLE:
              continuous_flow = (Serial.read() == ON) ? true : false;
              break;
            case THEME_TOGGLE:
              continuous_themes = (Serial.read() == ON) ? true : false;
              break;
#ifdef DEBUG
            default:
              Serial.print("unhandled buffer size 2");
#endif
          }
          break;
        case 6:
          c_in = Serial.read();
          uint8_t R,G,B;
          R = Serial.read();
          G = Serial.read();
          B = Serial.read();
#ifdef DEBUG
          Serial.print("R: ");
          Serial.print(R);
          Serial.print(" G: ");
          Serial.print(G);
          Serial.print(" B: ");
          Serial.println(B);
          delay(1000);
#endif
          switch(c_in){
            case COLOR:
              effect = WAIT;
              continuous_flow = false;
              all_on(strip.Color(R,G,B));
              break;
            case FLASH_EFFECT:
              flash(strip.Color(R,G,B),500);
              delay(100);
              break;
            case WIPE_EFFECT:
              wipe_color(strip.Color(R,G,B),5);
              break;
#ifdef DEBUG
            default:
              Serial.print("unhandled buffer size 3");
#endif    
        }
          break;
        case 8:
          if (Serial.read() == FULL_PACKET) {
            effect = Serial.read();
            continuous_flow = (Serial.read() == ON) ? true : false;
            continuous_themes = (Serial.read() == ON) ? true : false;
            c_in = Serial.read();
            if (c_in ==  FAST){
              if(wait_factor - 50 < wait_factor)
                wait_factor -= 50;
              else
                wait_factor = SPEED_L;
              }
            else if(c_in == SLOW){
              if(wait_factor + 50 > wait_factor)
                wait_factor += 50;
              else
                wait_factor = SPEED_H;
              }
            else
              wait_factor = SPEED_M;
          }
#ifdef DEBUG
          else 
            Serial.println("unhandled buffer size 5");
#endif
          break;
#ifdef DEBUG
        default:
          Serial.print("unhandled buffer size ");
          Serial.println(num_bytes);
#endif
      }
    }
#ifdef DEBUG
      Serial.print("message not for me ");
      Serial.println(c_in);
#endif
    
    // Flush serial (since the flush opiton does not empty buffer anymore)
    Serial.read();
    num_bytes = Serial.available();
    while (num_bytes > 0){
#ifdef DEBUG
      Serial.print(num_bytes);
      Serial.println(" bytes in buffer");
#endif
      Serial.read();
      num_bytes = Serial.available();
    }
  
  // Cases and Effects
#ifdef DEBUG
    // Report status on global variables
    Serial.print("Current effect: ");
    Serial.print(effect);
    Serial.print(" Continuous effects: ");
    Serial.print(continuous_flow);
    Serial.print(" Continuous themes: ");
    Serial.print(continuous_themes);
    Serial.print(" Speed: ");
    if (wait_factor)
      Serial.println("fast");
    else
      Serial.println("slow");
#endif

  switch (effect) {
    case WAIT:
      // Wait for next serial command
      if(continuous_flow) effect++; break;
      
    case THEME_CHOOSER:
      switch(theme){
        case TRIANGLE_THEME:
          C1 = 0xFF0000;
          C2 = 0xA00000;
          C3 = 0x551010;
          C4 = 0xB01010;
          C5 = 0xDF4040;
          break;
        case CIRCLE_THEME:
          C1 = 0x3914AF;
          C2 = 0x412CB4;
          C3 = 0x0609FF;
          C4 = 0x447BFD;
          C5 = 0x0526DE;
          break;
        case CROSS_THEME:
          C1 = 0x39E639;
          C2 = 0x00CC00;
          C3 = 0x002D00;
          C4 = 0x07E507;
          C5 = 0x269926;
          break;
        case SQUARE_THEME:
          C1 = 0xFFE500;
          C2 = 0xA69500;
          C3 = 0xFFF173;
          C4 = 0xFFFF00;
          C5 = 0xBFB130;
          break;
        case L1_THEME:
          C1 = 0x8001A0;
          C2 = 0xF000B0;
          C3 = 0x68006C;
          C4 = 0xFF00FF;
          C5 = 0x300021;
          break;
        case L2_THEME:
          C1 = 0x440000;
          C2 = 0xFF0500;
          C3 = 0xFF7300;
          C4 = 0xFFFF00;
          C5 = 0x771300;
          break;
        case L3_THEME:
          C1 = 0x44CCCC;
          C2 = 0x3AA6B0;
          C3 = 0xFF73FF;
          C4 = 0x3F3F3F;
          C5 = 0x0079AF;
          break;
        case R1_THEME:
          C1 = 0x8001A0;
          C2 = 0xF000B0;
          C3 = 0x68006C;
          C4 = 0xFF00FF;
          C5 = 0x300021;
          break;
        case R2_THEME:
          C1 = 0x440000;
          C2 = 0xFF0500;
          C3 = 0xFF7300;
          C4 = 0xFFFF00;
          C5 = 0x771300;
          break;
        case R3_THEME:
          C1 = 0x44CCCC;
          C2 = 0x3AA6B0;
          C3 = 0xFF73FF;
          C4 = 0x3F3F3F;
          C5 = 0x0079AF;
          break;
        default:
          C1 = random_color();
          C2 = random_color();
          C3 = random_color();
          C4 = random_color();
          C5 = random_color();
          theme = RANDOM_THEME;
      }
        if(continuous_themes) theme++;
        effect++;
        break;

    case RAINBOW:
      rainbow();
      delay(2000);
      shift_strip(3*NUM_LEDS,20);
      if(continuous_flow) effect++; break;
    case 2:
      wipe_color(strip.Color(0, 255, 0), 15, NUM_LEDS, 0); // Green
      if(continuous_flow) effect++; break;
    case 3:
      wipe_color(strip.Color(0, 0, 255), 15, 0, NUM_LEDS); // Blue
      if(continuous_flow) effect++; break;
    case 4:
      wipe_color(strip.Color(255, 0, 0), 15, NUM_LEDS, 0); // Red
      if(continuous_flow) effect++; break;
    case 5:
      flash_and_dim(C1,100,100,10,0,NUM_LEDS);
      delay(300);
      if(continuous_flow) effect++; break;
    case 6:
      flash_and_dim(C2,50,120,10,0,NUM_LEDS);
      delay(100);      
      if(continuous_flow) effect++; break;
    case 7:
      flash_and_dim(C3,150,150,10,0,NUM_LEDS);
      delay(100);
      if(continuous_flow) effect++; break;
    case 8:
      flash(C4,1000);
      delay(200);
      if(continuous_flow) effect++; break;
    case 9:
      flash_and_dim(C5,50,18,8,0,NUM_LEDS);
      if(continuous_flow) effect++; break;
    case 10:
      blend(C2,80,10,0,NUM_LEDS-1);
      delay(1000);
      if(continuous_flow) effect++; break;
    case 11:
      color_mixer(C3,0x000000,0,NUM_LEDS);
      delay(1000);
      if(continuous_flow) effect++; break;
    case 12:
      explosion(C4,0x000000,random(NUM_LEDS),15,false);
      delay(500);
      if(continuous_flow) effect++; break;
    case 13:
      explosion(C2,0x000000,random(NUM_LEDS),25,false);
      delay(1000);
      if(continuous_flow) effect++; break; 
    case 14:
      explosion(C1,0x000000,random(NUM_LEDS),10,false);
      delay(100);
      if(continuous_flow) effect++; break;
    case 15:
      explosion(C1,0x000000,random(NUM_LEDS),10,false);
      delay(1000);
      if(continuous_flow) effect++; break;
    case 16:
      explosion(C3,0x000000,random(NUM_LEDS),10,false);
      delay(100);
      if(continuous_flow) effect++; break;
    case 17:
      shift_strip(NUM_LEDS/6,70,0,NUM_LEDS-1);
      if(continuous_flow) effect++; break;
    case 18:
      shift_strip(NUM_LEDS/4,40,NUM_LEDS-1,0);
      if(continuous_flow) effect++; break;
    case 19:
      shift_strip(NUM_LEDS/2,35,0,NUM_LEDS-1);
      if(continuous_flow) effect++; break;
    case 20:
      shift_strip(NUM_LEDS,30,NUM_LEDS-1,0);
      if(continuous_flow) effect++; break;
    case 21:
      shift_strip(NUM_LEDS/2,25,0,NUM_LEDS-1);
      if(continuous_flow) effect++; break;
    case 22:
      shift_strip(NUM_LEDS/4,20,NUM_LEDS-1,0);      
      if(continuous_flow) effect++; break;
    case 23:
      shift_strip(NUM_LEDS,15,NUM_LEDS-1,0);
      if(continuous_flow) effect++; break;
    case 24:
      blend(0x000000,50,10,0,NUM_LEDS-1);
      delay(1000);    
      if(continuous_flow) effect++; break;
    case 25:
      flash(C4,500,3*NUM_LEDS/5, 4*NUM_LEDS/5);
      delay(500);
      if(continuous_flow) effect++; break;
    case 26:
      flash(C5,500,4*NUM_LEDS/5, NUM_LEDS);
      delay(500);
      if(continuous_flow) effect++; break;
    case 27:
      all_on(C1,4*NUM_LEDS/5, NUM_LEDS);
      if(continuous_flow) effect++; break;
    case 28:
      all_on(C2,3*NUM_LEDS/5,4*NUM_LEDS/5);
      if(continuous_flow) effect++; break;
    case 29:
      all_on(C3,2*NUM_LEDS/5,3*NUM_LEDS/5);
      if(continuous_flow) effect++; break;
    case 30:
      all_on(C4,NUM_LEDS/5,2*NUM_LEDS/5);
      if(continuous_flow) effect++; break;
    case 31:
      all_on(C5,0,NUM_LEDS/5);
      delay(2000);    
      if(continuous_flow) effect++; break;
    case 32:
      all_on(C3,2*NUM_LEDS/5,3*NUM_LEDS/5);
      if(continuous_flow) effect++; break;
    case 33:
      all_on(C1,4*NUM_LEDS/5, NUM_LEDS);
      if(continuous_flow) effect++; break;
    case 34:
      flash(C1,500,0,NUM_LEDS/5);
      delay(1000);
      if(continuous_flow) effect++; break;
    case 35:
      flash(C2,500, NUM_LEDS/5,2*NUM_LEDS/5);
      delay(400);
      if(continuous_flow) effect++; break;
    case 36:
      flash(C3,500,2*NUM_LEDS/5, 3*NUM_LEDS/5);
      delay(350);
      if(continuous_flow) effect++; break;
    case 37:
      blend(0x030250,50,10,0,NUM_LEDS-1);
      delay(1000);
      if(continuous_flow) effect++; break;
    case 38:
      wipe_color(0x044000, 50, 0, NUM_LEDS);  
      if(continuous_flow) effect++; break;
    case 39:
      explosion(0x000000,C3,random(NUM_LEDS),100,false);
      if(continuous_flow) effect++; break;
    case 40:
      wipe_color(0x00000, 25, NUM_LEDS,0);
      if(continuous_flow) effect++; break;
    case 41:
      
      if(continuous_flow) effect++; break;
    case 42:
      
      if(continuous_flow) effect++; break;
    case 43:
      
      if(continuous_flow) effect++; break;
    case 44:
      
      if(continuous_flow) effect++; break;
    case 45:
      
      if(continuous_flow) effect++; break;
    case 46:
      
      if(continuous_flow) effect++; break;
    case 47:
      
      if(continuous_flow) effect++; break;
    case 48:
      
      if(continuous_flow) effect++; break;
    case 49:
      
      if(continuous_flow) effect++; break; 
    case 50:
      
      if(continuous_flow) effect++; break;
    case 51:
      
      if(continuous_flow) effect++; break;
    case 52:
      
      if(continuous_flow) effect++; break;
    case 53:
      
      if(continuous_flow) effect++; break;
    case 54:
      
      if(continuous_flow) effect++; break;
    case 55:
      
      if(continuous_flow) effect++; break;
    case 56:
      
      if(continuous_flow) effect++; break;
    case 57:
      
      if(continuous_flow) effect++; break;
    case 58:
      
      if(continuous_flow) effect++; break;
    case 59:
      
      if(continuous_flow) effect++; break;
    case 60:
      
      if(continuous_flow) effect++; break;
    case 61:
      
      if(continuous_flow) effect++; break;
    case 62:
      
      if(continuous_flow) effect++; break;
    case 63:
      
      if(continuous_flow) effect++; break;
    case 64:
      
      if(continuous_flow) effect++; break;
    case 65:
      
      if(continuous_flow) effect++; break;
    case 66:
      
      if(continuous_flow) effect++; break;
    case 67:
      
      if(continuous_flow) effect++; break;
    case 68:
      
      if(continuous_flow) effect++; break;
    case 69:
      
      if(continuous_flow) effect++; break;
    case 70:
      
      if(continuous_flow) effect++; break;
    case 71:
      
      if(continuous_flow) effect++; break;
    case 72:
      
      if(continuous_flow) effect++; break;
    case 73:
      
      if(continuous_flow) effect++; break;
    case 74:
      
      if(continuous_flow) effect++; break;
    case 75:
      
      if(continuous_flow) effect++; break;
    case 76:
      
      if(continuous_flow) effect++; break;
    case 77:
      
      if(continuous_flow) effect++; break;
    case 78:
      
      if(continuous_flow) effect++; break;
    case 79:
      
      if(continuous_flow) effect++; break;
    case 80:
      
      if(continuous_flow) effect++; break;
    case 81:
      
      if(continuous_flow) effect++; break;
    case 82:
      
      if(continuous_flow) effect++; break;
    case 83:
      
      if(continuous_flow) effect++; break;
    case 84:
      
      if(continuous_flow) effect++; break;
    case 85:
      
      if(continuous_flow) effect++; break;
    case 86:
      
      if(continuous_flow) effect++; break;
    case 87:
      
      if(continuous_flow) effect++; break;
    case 88:
      
      if(continuous_flow) effect++; break;
    case 89:
      
      if(continuous_flow) effect++; break;
    case 90:
      
      if(continuous_flow) effect++; break;
    case 91:
      
      if(continuous_flow) effect++; break;
    case 92:
      
      if(continuous_flow) effect++; break;
    case 93:
      
      if(continuous_flow) effect++; break;
    case 94:
      
      if(continuous_flow) effect++; break;
    case 95:
      
      if(continuous_flow) effect++; break;
    case 96:
      
      if(continuous_flow) effect++; break;
    case 97:
      
      if(continuous_flow) effect++; break;
    case 98:
      
      if(continuous_flow) effect++; break;
    case 99:
      
      if(continuous_flow) effect++; break;
    case 100:
      
      if(continuous_flow) effect++; break;
    case 101:
      
      if(continuous_flow) effect++; break;
    case 102:
      
      if(continuous_flow) effect++; break;
    case 103:
      
      if(continuous_flow) effect++; break;
    case 104:
      
      if(continuous_flow) effect++; break;
    case 105:
      
      if(continuous_flow) effect++; break;
    case 106:
      
      if(continuous_flow) effect++; break;
    case 107:
      
      if(continuous_flow) effect++; break;
    case 108:
      
      if(continuous_flow) effect++; break;
    case 109:
      
      if(continuous_flow) effect++; break;
    case 110:
      
      if(continuous_flow) effect++; break;
    case 111:
      
      if(continuous_flow) effect++; break;
    case 112:
      
      if(continuous_flow) effect++; break;
    case 113:
      
      if(continuous_flow) effect++; break;
    case 114:
      
      if(continuous_flow) effect++; break;
    case 115:
      
      if(continuous_flow) effect++; break;
    case 116:
      
      if(continuous_flow) effect++; break;
    case 117:
      
      if(continuous_flow) effect++; break;
    case 118:
      
      if(continuous_flow) effect++; break;
    case 119:
      
      if(continuous_flow) effect++; break;
    case 120:
      
      if(continuous_flow) effect++; break;
    case 121:
      
      if(continuous_flow) effect++; break;
    case 122:
      
      if(continuous_flow) effect++; break;
    case 123:
      
      if(continuous_flow) effect++; break;
    case 124:
      
      if(continuous_flow) effect++; break;
    case 125:
      
      if(continuous_flow) effect++; break;
    case 126:
      
      if(continuous_flow) effect++; break;
    case 127:
      
      if(continuous_flow) effect++; break;
    case 128:
      
      if(continuous_flow) effect++; break;
    case 129:
      
      if(continuous_flow) effect++; break;
    case 130:
      
      if(continuous_flow) effect++; break;
    case 131:
      
      if(continuous_flow) effect++; break;
    case 132:
      
      if(continuous_flow) effect++; break;
    case 133:
      
      if(continuous_flow) effect++; break;
    case 134:
      
      if(continuous_flow) effect++; break;
    case 135:
      
      if(continuous_flow) effect++; break;
    case 136:
      
      if(continuous_flow) effect++; break;
    case 137:
      
      if(continuous_flow) effect++; break;
    case 138:
      
      if(continuous_flow) effect++; break;
    case 139:
      
      if(continuous_flow) effect++; break;
    case 140:
      
      if(continuous_flow) effect++; break;
    case 141:
      
      if(continuous_flow) effect++; break;
    case 142:
      
      if(continuous_flow) effect++; break;
    case 143:
      
      if(continuous_flow) effect++; break;
    case 144:
      
      if(continuous_flow) effect++; break;
    case 145:
      
      if(continuous_flow) effect++; break;
    case 146:
      
      if(continuous_flow) effect++; break;
    case 147:
      
      if(continuous_flow) effect++; break;
    case 148:
      
      if(continuous_flow) effect++; break;
    case 149:
      
      if(continuous_flow) effect++; break;
    case 150:
      
      if(continuous_flow) effect++; break;
    case 151:
      
      if(continuous_flow) effect++; break;
    case 152:
      
      if(continuous_flow) effect++; break;
    case 153:
      
      if(continuous_flow) effect++; break;
    case 154:
      
      if(continuous_flow) effect++; break;
    case 155:
      
      if(continuous_flow) effect++; break;
    case 156:
      
      if(continuous_flow) effect++; break;
    case 157:
      
      if(continuous_flow) effect++; break;
    case 158:
      
      if(continuous_flow) effect++; break;
    case 159:
      
      if(continuous_flow) effect++; break;
    case 160:
      
      if(continuous_flow) effect++; break;
    case 161:
      
      if(continuous_flow) effect++; break;
    case 162:
      
      if(continuous_flow) effect++; break;
    case 163:
      
      if(continuous_flow) effect++; break;
    case 164:
      
      if(continuous_flow) effect++; break;
    case 165:
      
      if(continuous_flow) effect++; break;
    case 166:
      
      if(continuous_flow) effect++; break;
    case 167:
      
      if(continuous_flow) effect++; break;
    case 168:
      
      if(continuous_flow) effect++; break;
    case 169:
      
      if(continuous_flow) effect++; break;
    case 170:
      
      if(continuous_flow) effect++; break;
    case 171:
      
      if(continuous_flow) effect++; break;
    case 172:
      
      if(continuous_flow) effect++; break;
    case 173:
      
      if(continuous_flow) effect++; break;
    case 174:
      
      if(continuous_flow) effect++; break;
    case 175:
      
      if(continuous_flow) effect++; break;
    case 176:
      
      if(continuous_flow) effect++; break;
    case 177:
      
      if(continuous_flow) effect++; break;
    case 178:
      
      if(continuous_flow) effect++; break;
    case 179:
      
      if(continuous_flow) effect++; break;
    case 180:
      
      if(continuous_flow) effect++; break;
    case 181:
      
      if(continuous_flow) effect++; break;
    case 182:
      
      if(continuous_flow) effect++; break;
    case 183:
      
      if(continuous_flow) effect++; break;
    case 184:
      
      if(continuous_flow) effect++; break;
    case 185:
      
      if(continuous_flow) effect++; break;
    case 186:
      
      if(continuous_flow) effect++; break;
    case 187:
      
      if(continuous_flow) effect++; break;
    case 188:
      
      if(continuous_flow) effect++; break;
    case 189:
      
      if(continuous_flow) effect++; break;
    case 190:
      
      if(continuous_flow) effect++; break;
    case 191:
      
      if(continuous_flow) effect++; break;
    case 192:
      
      if(continuous_flow) effect++; break;
    case 193:
      
      if(continuous_flow) effect++; break;
    case 194:
      
      if(continuous_flow) effect++; break;
    case 195:
      
      if(continuous_flow) effect++; break;
    case 196:
      
      if(continuous_flow) effect++; break;
    case 197:
      
      if(continuous_flow) effect++; break;
    case 198:
      
      if(continuous_flow) effect++; break;
    case 199:
      
      if(continuous_flow) effect++; break;
    case 200:
      
      if(continuous_flow) effect++; break;
    case 201:
      
      if(continuous_flow) effect++; break;
    case 202:
      
      if(continuous_flow) effect++; break;
    case 203:
      
      if(continuous_flow) effect++; break;
    case 204:
      
      if(continuous_flow) effect++; break;
    case 205:
      
      if(continuous_flow) effect++; break;
    case 206:
      
      if(continuous_flow) effect++; break;
    case 207:
      
      if(continuous_flow) effect++; break;
    case 208:
      
      if(continuous_flow) effect++; break;
    case 209:
      
      if(continuous_flow) effect++; break;
    case 210:
      
      if(continuous_flow) effect++; break;
    case 211:
      
      if(continuous_flow) effect++; break;
    case 212:
      
      if(continuous_flow) effect++; break;
    case 213:
      
      if(continuous_flow) effect++; break;
    case 214:
      
      if(continuous_flow) effect++; break;
    case 215:
      
      if(continuous_flow) effect++; break;
    case 216:
      
      if(continuous_flow) effect++; break;
    case 217:
      
      if(continuous_flow) effect++; break;
    case 218:
      
      if(continuous_flow) effect++; break;
    case 219:
      
      if(continuous_flow) effect++; break;
    case 220:
      
      if(continuous_flow) effect++; break;
    case 221:
      
      if(continuous_flow) effect++; break;
    case 222:
      
      if(continuous_flow) effect++; break;
    case 223:
      
      if(continuous_flow) effect++; break;
    case 224:
      
      if(continuous_flow) effect++; break;
    case 225:
      
      if(continuous_flow) effect++; break;
    case 226:
      
      if(continuous_flow) effect++; break;
    case 227:
      
      if(continuous_flow) effect++; break;
    case 228:
      
      if(continuous_flow) effect++; break;
    case 229:
      
      if(continuous_flow) effect++; break;
    case 230:
      
      if(continuous_flow) effect++; break;
    case 231:
      
      if(continuous_flow) effect++; break;
    case 232:
      
      if(continuous_flow) effect++; break;
    case 233:
      
      if(continuous_flow) effect++; break;
    case 234:
      
      if(continuous_flow) effect++; break;
    case 235:
      
      if(continuous_flow) effect++; break;
    case 236:
      
      if(continuous_flow) effect++; break;
    case 237:
      
      if(continuous_flow) effect++; break;
    case 238:
      
      if(continuous_flow) effect++; break;
    case 239:
      
      if(continuous_flow) effect++; break;
    case 240:
      
      if(continuous_flow) effect++; break;
    case 241:
      
      if(continuous_flow) effect++; break;
    case 242:
      
      if(continuous_flow) effect++; break;
    case 243:
      
      if(continuous_flow) effect++; break;
    case 244:
      
      if(continuous_flow) effect++; break;
    case 245:
      
      if(continuous_flow) effect++; break;
    case 246:
      
      if(continuous_flow) effect++; break;
    case 247:
      
      if(continuous_flow) effect++; break;
    case 248:
      
      if(continuous_flow) effect++; break;
    case 249:
      
      if(continuous_flow) effect++; break;
    case 250:
      
      if(continuous_flow) effect++; break;
    case 251:
      
      if(continuous_flow) effect++; break;
    case 252:
      
      if(continuous_flow) effect++; break;
    case 253:
      
      if(continuous_flow) effect++; break;
    case 254:
      
      if(continuous_flow) effect++; break;
    default:
#ifdef DEBUG    
      Serial.println("default case");
#endif      
      all_off();
      effect = 0; 
  }
}

#else
void loop(){
  // Effect testing
  /* DROP
  static_commet(0x0000ED,15);
  delay(5000);*/
 
  
  wipe_color(random_color(),0);
  explosion(0x003900, 0, NUM_LEDS/2,15,false);
  delay(100);
  explosion(0x390000, 0, random(NUM_LEDS),10,false);
  delay(500);
  explosion(0x000039, 0, random(NUM_LEDS),25,false);
  delay(1000);
  explosion(0x094500, 0, random(NUM_LEDS),5,false);
  delay(100);
  explosion(0x395500, 0, NUM_LEDS/3,15,false);
  delay(500);
  explosion(0x330039, 0, NUM_LEDS*(3/4),15,false);
  delay(1000);
  
  set_brightness(false,0x30);
  delay(3000);
  
  shift_strip(100,100,0,NUM_LEDS-1);
  shift_strip(30,10,NUM_LEDS-1,0);
  
  for (uint8_t i = 0; i < 20; i+=2){
    shift_strip(i,50,0,NUM_LEDS-1);
    shift_strip(i,50,NUM_LEDS-1,0);
    if(i < 10)
      explosion(0x030401<<i/2, 0, random(NUM_LEDS),15,false);
  }
  
  wipe_color(0x33FF33,0,NUM_LEDS,0);
  wipe_color(0x898080,0,0,NUM_LEDS/3);
  wipe_color(0x000066,0,NUM_LEDS*(3/4),NUM_LEDS/2);
  wipe_color(0xFFFF03,0);
  wipe_color(0xCC0000,0,NUM_LEDS,0);
  wipe_color(0x99FFFF,0);
  for (uint16_t i = 0; i < NUM_LEDS-10; i+= 10){
    wipe_color(0x090F3F<<i/10,0,0,NUM_LEDS -i);
  }
  delay(3000);
  for (uint8_t i = 0; i < 10; i++){
    shift_strip(random(200),0,0,NUM_LEDS-1);
    shift_strip(random(200),0,NUM_LEDS-1,0);
    
  }
  for (uint8_t i = 0; i < 10; i++)
    explosion(strip.Color(random(8),random(8),random(8)), 0, random(NUM_LEDS),15,false);
  delay(1000);
 
  
  //single_flash(strip.Color(random(10),random(10),random(10)),50);
  blend(0x070723,100);
  delay(3000);
  all_off();
  delay(3000);
}
#endif
  

/*
 * TO DO:
 * - finish 255 effects
 * - PICK COLORS FOR R1 R2 R3 THEMES
*/
