void demo_effect() {

  // Demo effect

  wipe_color(strip.Color(255, 0, 0), 5, 0, NUM_LEDS); // Red
  wipe_color(strip.Color(0, 255, 0), 5, NUM_LEDS,0); // Green
  wipe_color(strip.Color(0, 0, 255), 5, 0, NUM_LEDS); // Blue
  rainbow(20);
  // rainbowCycle(20);
  //theaterChaseRainbow(200); // takes very long to finish

  // Tested effect

  static_commet(strip.Color(100,255,255), 100);
  cometa(strip.Color(200, 100, 80), 0, 5, 15);
  fade_color_deprecated(0x890712,5);
  flash(0x832190,500);
  flash_and_dim(0xEEEEEE,50,18,8);
  delay(1000);
  flash_and_dim(0xEE00EE,50,18,8,0,10);
  delay(1000);
  color_mixer(0xFF00FF,0x000000,2,150);
  stars_individual(10,10,0x00F3FF,0x000000);
  uint32_t colors2[] = {0xFF0000,0x00FF00,0x0000FF};  cross_fade(colors2,3,100);
  three_fades(0x00FF00,0xFF0000,0x0000FF,10);
  uint32_t colors[NUM_LEDS]; colors[0]=0x00; for(int l=1;l<NUM_LEDS;l++) colors[l]=colors[l-1]+0xF; scroller(colors,NUM_LEDS,NUM_LEDS/2,10,false);


  // Effects not finished
 // stars_overlapping(100,100,random_color(),0x000000);
stars_individual(10,10,0x00F3FF,0x00000f);

  // Various flashes

  flash(random_color(),250,NUM_LEDS/2+NUM_LEDS/4, NUM_LEDS);
  flash(random_color(),200,NUM_LEDS/2, NUM_LEDS/2+NUM_LEDS/4);
  flash(random_color(),300, 0, NUM_LEDS/4);
  flash(random_color(),300, 0, NUM_LEDS/4);
  flash_and_dim(random_color(),10,15,8, 0, NUM_LEDS);
  flash_and_dim(random_color(),100,15,8, 0, NUM_LEDS);
  flash_and_dim(random_color(),100,15,8, 0, NUM_LEDS);
  colors[0]=random_color(); for(int l=1;l<NUM_LEDS;l++) colors[l]=colors[l-1]-0x5; scroller(colors,NUM_LEDS,200,10,true);
  colors[0]=random_color(); for(int l=1;l<NUM_LEDS;l++) colors[l]=colors[l-1]-0x5; scroller(colors,NUM_LEDS,50,10,false);

}

void slow_routine(){
  // Let's create routines
  uint32_t tonos[] = { 0x900100,0x000200,0x013300,0xFF8001,0x990300,0xCC0066,0xCC0066};
  cross_fade(tonos,7,100,3000);
  all_off();
  fade_to(0xCC0066,0x003400,120);
  fade_to(0x103400,0x030001,120);
  stars_individual(10,70,0x00F330,0x000001);
  
}

void fast_flashes(){
  uint32_t colors[NUM_LEDS];
  flash(random_color(),250,NUM_LEDS/2+NUM_LEDS/4, NUM_LEDS);
  flash(random_color(),200,NUM_LEDS/2, NUM_LEDS/2+NUM_LEDS/4);
  flash(random_color(),300, 0, NUM_LEDS/4);
  flash(random_color(),300, 0, NUM_LEDS/4);
  flash_and_dim(random_color(),10,15,8, 0, NUM_LEDS);
  flash_and_dim(random_color(),100,15,8, 0, NUM_LEDS);
  flash_and_dim(random_color(),100,15,8, 0, NUM_LEDS);
  for(int i = 2; i < 7; i++){
    colors[0]=random_color(); for(int l=1;l<NUM_LEDS;l++) colors[l]=colors[l-1]-0x5; scroller(colors,NUM_LEDS,i*10,i-2,true);
    colors[0]=random_color(); for(int l=1;l<NUM_LEDS;l++) colors[l]=colors[l-1]-0x5; scroller(colors,NUM_LEDS,i*10,i-2,false);
  }
  all_off();
  delay(200);
  for (int i = 0; i<  10; i++){
    flash(0x000500,50, 0, NUM_LEDS);
    flash(0x000005,100, 0, NUM_LEDS);
  }
  for (int i = 10; i<  20; i++){
    flash(0x100510,i*10, 0, NUM_LEDS);
    flash(0x000005,i*10, 0, NUM_LEDS);
    flash(0x090000,i*10, 0, NUM_LEDS);
  }
  for (int i = 1; i<  15; i++){
    flash(0x103510,100, 0, NUM_LEDS);
    flash(0x100305,100, 0, NUM_LEDS);
    flash(0x090110,100, 0, NUM_LEDS);
  }
  flash_and_dim(0x073982,300,50,8, 0, NUM_LEDS);
  flash_and_dim(0x170902,300,50,8, 0, NUM_LEDS);
  flash_and_dim(0x808080,300,50,8, 0, NUM_LEDS);
  delay(1000);
}

/********************** PS2 Cases *****************************************/
void loop(){
  ps2x.read_gamepad(); //read controller
  
  // Cases Control
  if(ps2x.ButtonPressed(PSB_START)){
    if (continuous_flow){
      if (continuous_family_flow){
        // Was green turns yellow
        continuous_family_flow = false;
        flash(0xFFFF00,500);
        flash(0xFFFF00,500);
      }
      else {
        // was yellow turns red
        continuous_flow = false;
        flash(0xFF0000,500);
        flash(0xFF0000,500);
      }
    else{
      // was red turns green
      continuous_family_flow = true;
      continuous_flow =  true;
    }
#ifdef DEBUG
    Serial.print("flow: ");
    Serial.print(continuous_flow);
    Serial.print("\tfamily flow: ");
    Serial.println(continuous_family_flow);
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
      if (ps2x.ButtonPressed(PSB_START)){
    // Turn all off if START is pressed after SELECT
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
    for(uint8_t i = 0; i < 2; i++){
      all_off();
      delay(500);
      all_on(strip.Color(LY, LX, RY));
      delay(500);

    }
    // Stay on with that color
    while(!ps2x.ButtonPressed(PSB_START)){
      ps2x.read_gamepad();
      delay(100);
    }
    
  }
  // Effects Family Control
  else if(ps2x.ButtonPressed(PSB_TRIANGLE)) {
#ifdef DEBUG
    Serial.println("Released triangle");
#endif
    effect = TRIANGLE_INDEX;
  }
  else if(ps2x.ButtonPressed(PSB_CIRCLE)) {
#ifdef DEBUG
    Serial.println("Released circle");
#endif
    effect = CIRCLE_INDEX;
  }
  else if(ps2x.ButtonPressed(PSB_CROSS)) {
#ifdef DEBUG
    Serial.println("Released cross");
#endif
    effect = CROSS_INDEX;
  }
  else if(ps2x.ButtonPressed(PSB_SQUARE)) {
#ifdef DEBUG
    Serial.println("Released square");
#endif
    effect = SQUARE_INDEX;
  }
  else if(ps2x.ButtonPressed(PSB_L1)) {
#ifdef DEBUG
    Serial.println("Released L1");
#endif
    effect = L1_INDEX;
  }
  else if(ps2x.ButtonPressed(PSB_L2)) {
#ifdef DEBUG
    Serial.println("Released L2");
#endif
    effect = L2_INDEX;
  }
  else if(ps2x.ButtonPressed(PSB_L3)) {
#ifdef DEBUG
    Serial.println("Released L3");
#endif
    effect = L3_INDEX;
  }
  else if(ps2x.ButtonPressed(PSB_R1)) {
#ifdef DEBUG
    Serial.println("Released R1");
#endif
    effect = R1_INDEX;
  }
  else if(ps2x.ButtonPressed(PSB_R2)) {
#ifdef DEBUG
    Serial.println("Released R2");
#endif
    effect = R2_INDEX;
  }
  else if(ps2x.ButtonPressed(PSB_R3)) {
#ifdef DEBUG
    Serial.println("Released R3");
#endif
    effect = R3_INDEX;
  }
  else if(ps2x.ButtonPressed(PSB_PAD_LEFT)) {
#ifdef DEBUG
    Serial.println("Released pad left");
#endif
    effect -= 2;
  }
  else if(ps2x.ButtonPressed(PSB_PAD_RIGHT)) {
#ifdef DEBUG
    Serial.println("Released pad right");
#endif
    effect++;
  }
  
  // Speed control
  if(ps2x.ButtonPressed(PSB_PAD_DOWN) || ps2x.ButtonPressed(PSB_PAD_UP)){
    if(ps2x.ButtonPressed(PSB_PAD_UP)) {
      if (wait_factor < 255) wait_factor += 20;
#ifdef DEBUG
      Serial.println("Released pad up");
      Serial.print("Wait factor: ");
      Serial.println(wait_factor);    
#endif
    }
    else{
      if (wait_factor > 0) wait_factor -= 20;
#ifdef DEBUG
      Serial.println("Released pad down");
      Serial.print("Wait factor: ");
      Serial.println(wait_factor);
#endif
    }
    flash(0x0000FF,200);
    delay(100+wait_factor*3);
    flash(0x0000FF,200);
  }
  
  // Cases and Effects
#ifdef DEBUG
    Serial.print("Current effect: ");
    Serial.println(effect);
#endif  
  switch (effect) {
    // Start of Family of Effects
    case TRIANGLE_INDEX-1:
    
      if(continuous_flow) effect = continuous_family_flow ? R3_INDEX: effect++; break;
    case CIRCLE_INDEX-1:
    
      if(continuous_flow) effect = continuous_family_flow ? TRIANGLE_INDEX: effect++; break;
    case CROSS_INDEX-1:
    
      if(continuous_flow) effect = continuous_family_flow ? CIRCLE_INDEX: effect++; break;
    case SQUARE_INDEX-1:
    
      if(continuous_flow) effect = continuous_family_flow ? CROSS_INDEX: effect++; break;
    case L1_INDEX-1:
    
      if(continuous_flow) effect = continuous_family_flow ? SQUARE_INDEX: effect++; break;
    case L2_INDEX-1:
    
      if(continuous_flow) effect = continuous_family_flow ? L1_INDEX: effect++; break;
    case L3_INDEX-1:
    
      if(continuous_flow) effect = continuous_family_flow ? L2_INDEX: effect++; break;
    case R1_INDEX-1:
    
      if(continuous_flow) effect = continuous_family_flow ? L3_INDEX: effect++; break;
    case R2_INDEX-1:
    
      if(continuous_flow) effect = continuous_family_flow ? R1_INDEX: effect++; break;
    case R3_INDEX-1:
    
      if(continuous_flow) effect = continuous_family_flow ? R2_INDEX: effect++; break;
    case TRIANGLE_INDEX-1:
    
      if(continuous_flow) effect = continuous_family_flow ? R3_INDEX: effect++; break;
    case 0:
      stars_individual(2,70,0x00F330,0x000001);   
      if(continuous_flow) effect++; break;
    case 1:
      wipe_color(strip.Color(255, 0, 0), 5, 0, NUM_LEDS); // Red
      if(continuous_flow) effect++; break;
    case 2:
      wipe_color(strip.Color(0, 255, 0), 5, NUM_LEDS,0); // Green
      if(continuous_flow) effect++; break;
    case 3:
      wipe_color(strip.Color(0, 0, 255), 5, 0, NUM_LEDS); // Blue
      if(continuous_flow) effect++; break;
    case 4:
      rainbow(20);
      if(continuous_flow) effect++; break;
    case 5:
      static_commet(strip.Color(100,255,255), 100);
      if(continuous_flow) effect++; break;
    case 6:
      //cometa(strip.Color(200, 100, 80), 0, 5, 15);
      if(continuous_flow) effect++; break;
    case 7:
      fade_color_deprecated(0x890712,5);
      if(continuous_flow) effect++; break;
    case 8:
      flash(0x832190,500);
      if(continuous_flow) effect++; break;
    case 9:
      flash_and_dim(0xEEEEEE,50,18,8);
      //delay(1000);
      if(continuous_flow) effect++; break;
    case 10:
      flash_and_dim(0xEE00EE,50,18,8,0,100);
      //delay(1000);
      if(continuous_flow) effect++; break;
    case 11:
      color_mixer(0xFF00FF,0x000000,2,150);
      if(continuous_flow) effect++; break;
    case 12:
      stars_individual(10,10,0x00F3FF,0x000000);
      if(continuous_flow) effect++; break;
    case 13:
//      colors[0] = 0xFF0000;
//      colors[1] = 0x00FF00;
//      colors[2] = 0x0000FF;
//      cross_fade(colors,3,10,10);
      if(continuous_flow) effect++; break; 
    case 14:
      three_fades(0x00FF00,0xFF0000,0x0000FF,10);
      if(continuous_flow) effect++; break;
//    case 15:
//      uint32_t colors[NUM_LEDS]; colors[0]=0x00; for(int l=1;l<NUM_LEDS;l++) colors[l]=colors[l-1]+0xF; scroller(colors,NUM_LEDS,NUM_LEDS/2,10,false);
//      if(continuous_flow) effect++; break;
//    case 16:
//      stars_individual(10,10,0x00F3FF,0x00000f);
//      if(continuous_flow) effect++; break;
//    case 17:
//      flash(random_color(),250,NUM_LEDS/2+NUM_LEDS/4, NUM_LEDS);
//      if(continuous_flow) effect++; break;
//    case 18:
//      flash(random_color(),200,NUM_LEDS/2, NUM_LEDS/2+NUM_LEDS/4);
//      if(continuous_flow) effect++; break;
//    case 19:
//      flash(random_color(),300, 0, NUM_LEDS/4);
//      if(continuous_flow) effect++; break;
//    case 20:
//      flash(random_color(),300, 0, NUM_LEDS/4);
//      if(continuous_flow) effect++; break;
//    case 21:
//      flash_and_dim(random_color(),10,15,8, 0, NUM_LEDS);
//      if(continuous_flow) effect++; break;
//    case 22:
//      flash_and_dim(random_color(),100,15,8, 0, NUM_LEDS);
//      if(continuous_flow) effect++; break;
//    case 23:
//      flash_and_dim(random_color(),100,15,8, 0, NUM_LEDS);
//      if(continuous_flow) effect++; break;
//    case 24:
//        colors[0]=random_color(); for(int l=1;l<NUM_LEDS;l++) colors[l]=colors[l-1]-0x5; scroller(colors,NUM_LEDS,200,10,true);
//      if(continuous_flow) effect++; break;
//    case 25:
//        colors[0]=random_color(); for(int l=1;l<NUM_LEDS;l++) colors[l]=colors[l-1]-0x5; scroller(colors,NUM_LEDS,50,10,false);
//      if(continuous_flow) effect++; break;
//    case 255:
//      // Set colors
//      all_off();
//      if(continuous_flow) effect++; break;
    case 26:
      
      if(continuous_flow) effect++; break;
    case 27:
      
      if(continuous_flow) effect++; break;
    case 28:
      
      if(continuous_flow) effect++; break;
    case 29:
      
      if(continuous_flow) effect++; break;
    case 30:
      
      if(continuous_flow) effect++; break;
    case 31:
      
      if(continuous_flow) effect++; break;
    case 32:
      
      if(continuous_flow) effect++; break;
    case 33:
      
      if(continuous_flow) effect++; break;
    case 34:
      
      if(continuous_flow) effect++; break;
    case 35:
      
      if(continuous_flow) effect++; break;
    case 36:
      
      if(continuous_flow) effect++; break;
    case 37:
      
      if(continuous_flow) effect++; break;
    case 38:
      
      if(continuous_flow) effect++; break;
    case 39:
      
      if(continuous_flow) effect++; break;
    case 40:
      
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
    case 255:
      
      if(continuous_flow) effect++; break;
    default:
#ifdef DEBUG    
      Serial.println("default case");
#endif      
      all_off();
      effect = 0; 
  }
}

/*
 * TO DO:
 * - Check functionality on
 * -- up Light up acknowledge when pressing buttons
 * --- START button
 * --- Speed
 * - Check Loop within family of effects
 * - finish 255 effects

*/
