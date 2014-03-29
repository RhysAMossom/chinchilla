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
/* Cases will be devided as follows. 
  0-REGULAR_EFFECT: regular routines
  REGULAR_EFFECTS-254: special effect
  255: setup colors  
*/

void loop(){
  ps2x.read_gamepad(); //read controller
  
  // Cases Control
  if(ps2x.ButtonReleased(PSB_START)){
    // Start demo effect
#ifdef DEBUG
    Serial.println("Starting demo effect");
#endif
    continuous_flow = !continuous_flow;
  }

  else if(ps2x.ButtonReleased(PSB_SELECT)) {
    // Select RBG colors from joystic values
#ifdef DEBUG
    Serial.println("Ly\tLx\tRy\tRx");
#endif
    delay(50);
    ps2x.read_gamepad();
    while(!ps2x.ButtonReleased(PSB_SELECT)){
      uint8_t LY, LX, RY, RX;
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
  }
  else if(ps2x.ButtonReleased(PSB_TRIANGLE)) {
#ifdef DEBUG
    Serial.println("Released triangle");
#endif
    effect = TRIANGLE_INDEX;
  }
  else if(ps2x.ButtonReleased(PSB_CIRCLE)) {
#ifdef DEBUG
    Serial.println("Released circle");
#endif
    effect = CIRCLE_INDEX;
  }
  else if(ps2x.ButtonReleased(PSB_CROSS)) {
#ifdef DEBUG
    Serial.println("Released cross");
#endif
    effect = CROSS_INDEX;
  }
  else if(ps2x.ButtonReleased(PSB_SQUARE)) {
#ifdef DEBUG
    Serial.println("Released square");
#endif
    effect = SQUARE_INDEX;
  }
  else if(ps2x.ButtonReleased(PSB_L1)) {
#ifdef DEBUG
    Serial.println("Released L1");
#endif
    effect = L1_INDEX;
  }
  else if(ps2x.ButtonReleased(PSB_L2)) {
#ifdef DEBUG
    Serial.println("Released L2");
#endif
    effect = L2_INDEX;
  }
  else if(ps2x.ButtonReleased(PSB_L3)) {
#ifdef DEBUG
    Serial.println("Released L3");
#endif
    effect = L3_INDEX;
  }
  else if(ps2x.ButtonReleased(PSB_R1)) {
#ifdef DEBUG
    Serial.println("Released R1");
#endif
    effect = R1_INDEX;
  }
  else if(ps2x.ButtonReleased(PSB_R2)) {
#ifdef DEBUG
    Serial.println("Released R2");
#endif
    effect = R2_INDEX;
  }
  else if(ps2x.ButtonReleased(PSB_R3)) {
#ifdef DEBUG
    Serial.println("Released R3");
#endif
    effect = R3_INDEX;
  }
  else if(ps2x.ButtonReleased(PSB_PAD_LEFT)) {
#ifdef DEBUG
    Serial.println("Released pad left");
#endif
    effect--;
  }
  else if(ps2x.ButtonReleased(PSB_PAD_RIGHT)) {
#ifdef DEBUG
    Serial.println("Released pad right");
#endif
    effect++;
  }
  
  // Speed control
  if(ps2x.ButtonReleased(PSB_PAD_UP)) {
#ifdef DEBUG
    Serial.println("Released pad up");
#endif
    
    if (wait_factor < 255) wait_factor++;
  }
  else if(ps2x.ButtonReleased(PSB_PAD_DOWN)) {
#ifdef DEBUG
    Serial.println("Released pad down");
#endif
    if (wait_factor > 0) wait_factor--;
  }
  
  //switch (effect) {
    //case 0:
      //stars_individual(2,70,0x00F330,0x000001);   
      //if(!continuous_flow) effect++; break;
    //case 1:
      //wipe_color(strip.Color(255, 0, 0), 5, 0, NUM_LEDS); // Red
      //if(!continuous_flow) effect++; break;
    //case 2:
      //wipe_color(strip.Color(0, 255, 0), 5, NUM_LEDS,0); // Green
      //if(!continuous_flow) effect++; break;
    //case 3:
      //wipe_color(strip.Color(0, 0, 255), 5, 0, NUM_LEDS); // Blue
      //if(!continuous_flow) effect++; break;
    //case 4:
      //rainbow(20);
      //if(!continuous_flow) effect++; break;
    //case 5:
      //static_commet(strip.Color(100,255,255), 100);
      //if(!continuous_flow) effect++; break;
    //case 6:
      //cometa(strip.Color(200, 100, 80), 0, 5, 15);
      //if(!continuous_flow) effect++; break;
    //case 7:
      //fade_color_deprecated(0x890712,5);
      //if(!continuous_flow) effect++; break;
    //case 8:
      //flash(0x832190,500);
      //if(!continuous_flow) effect++; break;
    //case 9:
      //flash_and_dim(0xEEEEEE,50,18,8);
      //delay(1000);
      //if(!continuous_flow) effect++; break;
    //case 10:
      //flash_and_dim(0xEE00EE,50,18,8,0,100);
      //delay(1000);
      //if(!continuous_flow) effect++; break;
    //case 11:
      //color_mixer(0xFF00FF,0x000000,2,150);
      //if(!continuous_flow) effect++; break;
    //case 12:
      //stars_individual(10,10,0x00F3FF,0x000000);
      //if(!continuous_flow) effect++; break;
    //case 13:
      //{
        //uint32_t colors2[] = {0xFF0000,0x00FF00,0x0000FF};  cross_fade(colors2,3,10,10);
      //if(!continuous_flow) effect++; break; 
      //}
    //case 14:
      //three_fades(0x00FF00,0xFF0000,0x0000FF,10);
      //if(!continuous_flow) effect++; break;
    //case 15:
      //{
        //uint32_t colors[NUM_LEDS]; colors[0]=0x00; for(int l=1;l<NUM_LEDS;l++) colors[l]=colors[l-1]+0xF; scroller(colors,NUM_LEDS,NUM_LEDS/2,10,false);
      //}
      //if(!continuous_flow) effect++; break;
    //case 16:
      //stars_individual(10,10,0x00F3FF,0x00000f);
      //if(!continuous_flow) effect++; break;
    //case 17:
      //flash(random_color(),250,NUM_LEDS/2+NUM_LEDS/4, NUM_LEDS);
      //if(!continuous_flow) effect++; break;
    //case 18:
      //flash(random_color(),200,NUM_LEDS/2, NUM_LEDS/2+NUM_LEDS/4);
      //if(!continuous_flow) effect++; break;
    //case 19:
      //flash(random_color(),300, 0, NUM_LEDS/4);
      //if(!continuous_flow) effect++; break;
    //case 20:
      //flash(random_color(),300, 0, NUM_LEDS/4);
      //if(!continuous_flow) effect++; break;
    //case 21:
      //flash_and_dim(random_color(),10,15,8, 0, NUM_LEDS);
      //if(!continuous_flow) effect++; break;
    //case 22:
      //flash_and_dim(random_color(),100,15,8, 0, NUM_LEDS);
      //if(!continuous_flow) effect++; break;
    //case 23:
      //flash_and_dim(random_color(),100,15,8, 0, NUM_LEDS);
      //if(!continuous_flow) effect++; break;
    //case 24:
      //{
        //uint32_t colors[NUM_LEDS];
        //colors[0]=random_color(); for(int l=1;l<NUM_LEDS;l++) colors[l]=colors[l-1]-0x5; scroller(colors,NUM_LEDS,200,10,true);
      //}
      //if(!continuous_flow) effect++; break;
    //case 25:
      //{
        //uint32_t colors[NUM_LEDS];
        //colors[0]=random_color(); for(int l=1;l<NUM_LEDS;l++) colors[l]=colors[l-1]-0x5; scroller(colors,NUM_LEDS,50,10,false);
      //}
      //if(!continuous_flow) effect++; break;
    //case 255:
      //// Set colors
      //all_off();
      ///*/
      //while(!analogRead(ENTER)){
        //uint8_t r = map(analogRead(R_POT),0,255,0,1024);
        //uint8_t g = map(analogRead(G_POT),0,255,0,1024);
        //uint8_t b = map(analogRead(B_POT),0,255,0,1024);
        //for(uint16_t led = 0; led < NUM_LEDS; led++)
          //strip.setPixelColor(led,strip.Color(r,g,b));
        //strip.show()      
      //}
      //*/
    //default:
      //all_off();
  //}
}
