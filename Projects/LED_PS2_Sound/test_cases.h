#ifndef TEST_CASES_H
#define TEST_CASES_H

  // Effect testing

// START: Centered Circular Equilizer
  if (repeats < 200) {
    continuous_flow = false;
    eq = 2*analogRead(ENVELOPE_PIN);
    if(eq > SOFT_SOUND) eq -= SOFT_SOUND;
    if (eq < NUM_LEDS/8 - 3){
      for (uint16_t led_offset = 0; led_offset < NUM_LEDS; led_offset += NUM_LEDS/4){
        led = led_offset;
        for (; led <= led_offset + NUM_LEDS/8 - eq -3; led++)
          strip[led] = CRGB::Black;
        for (; led <= led_offset + NUM_LEDS/8 - eq; led++)
          strip[led] = color2;
        for (; led <= led_offset + NUM_LEDS/8 + eq; led++)
          strip[led] = color1;
        for (; led <= led_offset + NUM_LEDS/8 + eq + 3; led++)
          strip[led] = color2;
        for (; led <= led_offset + NUM_LEDS/4; led++)
          strip[led] = CRGB::Black;
      }
      FastLED.show();
    }
    else
      all_on(random_color());
    // FastLED.delay(10);
  }
  else{
      continuous_flow = true;
      repeats = 0;
      color0 = random_color();
      color1 = random_color();
      color2 = random_color();
  }
// END

// START: Centered Circular Equilizer
  if (repeats < 200) {
    continuous_flow = false;
    for (uint16_t led_offset = 0; led_offset < NUM_LEDS; led_offset += NUM_LEDS/4){
      eq = 2*analogRead(ENVELOPE_PIN);
      if(eq > SOFT_SOUND) eq -= SOFT_SOUND;
      if (eq < NUM_LEDS/8 - 3){
        all_off(led_offset, led_offset + NUM_LEDS/8 - eq -3);
        all_on(color1, led_offset + NUM_LEDS/8 - eq -3, led_offset + NUM_LEDS/8 - eq);
        all_on(color2, led_offset + NUM_LEDS/8 - eq, led_offset + NUM_LEDS/8 + eq);
        all_on(color1, led_offset + NUM_LEDS/8 + eq, led_offset + NUM_LEDS/8 + eq + 3);
        all_off(led_offset + NUM_LEDS/8 + eq + 3, led_offset + NUM_LEDS/4);
      }
      else
        all_on(random_color(),led_offset,led_offset + NUM_LEDS/4);
    }
  }
  else{
      continuous_flow = true;
      repeats = 0;
      color0 = random_color();
      color1 = random_color();
      color2 = random_color();
  }
// END

// START: Circular Equilizer
  if (repeats < 200) {
    continuous_flow = false;
    eq = 4*analogRead(ENVELOPE_PIN);
    if(eq > SOFT_SOUND) eq -= SOFT_SOUND;
    if (eq < NUM_LEDS/4-3){
      all_on(color2, 0, eq);
      all_on(color1, eq, eq + 2);
      all_off(eq + 3, NUM_LEDS/4);
    }
    else all_on(color0,0,NUM_LEDS/4);
    
    eq = 4*analogRead(ENVELOPE_PIN);
    if(eq > SOFT_SOUND) eq -= SOFT_SOUND;
    if (eq < NUM_LEDS/4-3){
      all_off(NUM_LEDS/4,  NUM_LEDS/2 - eq - 3);
      all_on(color1, NUM_LEDS/2 - eq - 3, NUM_LEDS/2 - eq);
      all_on(color2, NUM_LEDS/2 - eq, NUM_LEDS/2);
    }
    else all_on(color0,NUM_LEDS/4, NUM_LEDS/2);
    
    eq = 4*analogRead(ENVELOPE_PIN);
    if(eq > SOFT_SOUND) eq -= SOFT_SOUND;
    if (eq < NUM_LEDS/4-3){
      all_on(color2, NUM_LEDS/2, NUM_LEDS/2 + eq);
      all_on(color1, NUM_LEDS/2 + eq, NUM_LEDS/2 + eq + 2);
      all_off(NUM_LEDS/2 + eq + 3, 3*NUM_LEDS/4);
    }
    else all_on(color0,NUM_LEDS/2, 3*NUM_LEDS/4);
    
    eq = 4*analogRead(ENVELOPE_PIN);
    if(eq > SOFT_SOUND) eq -= SOFT_SOUND;
    if (eq < NUM_LEDS/4-3){
      all_off(3*NUM_LEDS/4,NUM_LEDS - eq -3);
      all_on(color1, NUM_LEDS - eq - 3, NUM_LEDS - eq);
      all_on(color2, NUM_LEDS - eq, NUM_LEDS);
    }
    else all_on(color0,3*NUM_LEDS/4, NUM_LEDS);
  }
  else{
      continuous_flow = true;
      repeats = 0;
      color0 = random_color();
      color1 = random_color();
      color2 = random_color();
  }
// END

// START: Equilizer on full strip
  if (repeats < 200) {
    continuous_flow = false;
    eq = 4*analogRead(ENVELOPE_PIN);
    if(eq > SOFT_SOUND)
      eq -= SOFT_SOUND;
    if (eq < LOUD_SOUND){
      all_on(color2, 0, eq);
      all_on(color1, eq, eq + 2);
      all_off(eq + 3, NUM_LEDS/2 - eq - 3);
      all_on(color1, NUM_LEDS/2 - eq - 3, NUM_LEDS/2 - eq);
      all_on(color2, NUM_LEDS/2 - eq, NUM_LEDS/2 + eq);
      all_on(color1, NUM_LEDS/2 + eq, NUM_LEDS/2 + eq + 2);
      all_off(NUM_LEDS/2 + eq + 3, NUM_LEDS -  eq - 3);
      all_on(color1, NUM_LEDS - eq - 3, NUM_LEDS - eq);
      all_on(color2, NUM_LEDS - eq, NUM_LEDS);
    }
    else
      flash(CRGB::Red,100);
  }
  else{
      continuous_flow = true;
      repeats = 0;
      color0 = random_color();
      color1 = random_color();
      color2 = random_color();
  }
// END

// START: Equilizer on half strip
  if (repeats < 200) {
    continuous_flow = false;
    eq = analogRead(ENVELOPE_PIN);
    if(eq > SOFT_SOUND)
      eq -= SOFT_SOUND;
    if (eq > LOUD_SOUND)
      flash_and_dim(random_color(),150,5);
    else{
      all_on(color0,0,eq);
      all_off(eq+1,NUM_LEDS-eq-1);
      all_on(color1,NUM_LEDS-eq,NUM_LEDS);
    }
    if(beat_count >= 10){
      rainbow();
      FastLED.delay(1000);
      all_off();
      beat_count = 0;
    }
  }
  else{
      continuous_flow = true;
      repeats = 0;
      color0 = random_color();
      color1 = random_color();
      color2 = random_color();
  }
// END

// START: Scroll Colors sound is brightness
  if (repeats < 200) {
    continuous_flow = false;
    eq = 2*analogRead(ENVELOPE_PIN);
    if (eq < LOUD_SOUND) eq -= 10;
    color_hsv.hue=repeats; color_hsv.sat=255; color_hsv.val=eq;
    hsv2rgb_spectrum(color_hsv,color0);
    all_on(color0);
  }
  else {
    repeats = 0;
    continuous_flow = true;
  }
// END

// START: Single color sound is brightness
  if (repeats < 200) {
    continuous_flow = false;
    eq = map(analogRead(ENVELOPE_PIN),0,1023,0,255);
    if (eq > LOUD_SOUND)
      eq = 255;
    else if (eq > SOFT_SOUND) eq +=25;
    color_hsv.hue=200; color_hsv.sat=255; color_hsv.val=eq;
    hsv2rgb_spectrum(color_hsv,color1);
    all_on(color1);
  }
  else {
    repeats = 0;
    continuous_flow = true;
  }
// END

// START:
  flash_and_dim(random_color(),10*wait_factor,10,10);
// END

// START:
  led = random(0,NUM_LEDS-1);
  explosion(random_color(), strip[led], led, random(10,50),false);
  for (uint8_t i= 0; i< 4; i++)
    rotate();
// END

// START:
  rainbow();
  FastLED.delay(1000);
  backup();
  all_off();
  FastLED.delay(2000);
  restore();
// END

// START:
  flash_grow(random_color(), 0,NUM_LEDS/8);
  FastLED.delay(1000);
// END

// START:
  for (uint8_t i= 0; i< 25; i++){
    all_on(random_color());
    FastLED.delay(1000);
  }
// END

// START: 
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
// END

// START:
  palette(random(1,15));
// END

// START:
  color_mixer(CRGB(0x000005),CRGB(0x090885),4*NUM_LEDS/5, NUM_LEDS-1);
  color_mixer(CRGB(0x090885),CRGB(0x000005),3*NUM_LEDS/5,4*NUM_LEDS/5);
  color_mixer(CRGB(0x000005),CRGB(0x090885),2*NUM_LEDS/5,3*NUM_LEDS/5);
  color_mixer(CRGB(0x090885),CRGB(0x000005),NUM_LEDS/5,2*NUM_LEDS/5);
  color_mixer(CRGB(0x000005),CRGB(0x090885),0,NUM_LEDS/5);
  FastLED.delay(1000);
  shift_strip(NUM_LEDS,100,0,NUM_LEDS-1);
// END

// START:
  rainbow();
  FastLED.delay(1000);
  shift_strip(NUM_LEDS,100,0,NUM_LEDS-1);
  shift_strip(NUM_LEDS,80,0,NUM_LEDS-1);
  
  shift_strip(NUM_LEDS,50,0,NUM_LEDS-1);
  shift_strip(NUM_LEDS,0,0,NUM_LEDS-1);
  
  for (uint8_t i= 0; i< 25; i++)
    rotate();
// END

// START:
  wipe_color(CRGB(0, 255, 0), 10, NUM_LEDS, 0); // Green
  
  wipe_color(CRGB(0, 0, 255), 10, 0, NUM_LEDS-1); // Blue
  
  wipe_color(CRGB(255, 0, 0), 10, NUM_LEDS, 0); // Red
// END

// START:
  flash_and_dim(THEME_COLORS[0],100,100,10,0,NUM_LEDS-1);
  FastLED.delay(300);
  
  flash_and_dim(THEME_COLORS[1],150,120,10,0,NUM_LEDS-1);
  FastLED.delay(100);
  
  flash_and_dim(THEME_COLORS[2],150,150,10,0,NUM_LEDS-1);
  FastLED.delay(100);
  
  flash(THEME_COLORS[3],1000);
  FastLED.delay(200);
  
  flash_and_dim(THEME_COLORS[4],150,18,8,0,NUM_LEDS-1);
// END

// START:
  if (repeats < 15){
    divided_inwards(random_color(),random_color(),10);
    continuous_flow = false;
    repeats++;
  }
  else{
    continuous_flow = true;
    repeats=0;
  }
// END

// START: 
  blend(THEME_COLORS[1],80,10,0,NUM_LEDS-1);
  FastLED.delay(1000);
// END

// START:
  color_mixer(THEME_COLORS[2],CRGB::Black,0,NUM_LEDS-1);
  shift_strip(NUM_LEDS,10,NUM_LEDS-1,0);
// END

// START:
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
// END

// START:
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
// END

// START:
  blend(CRGB::Black,50,10,0,NUM_LEDS-1);
  FastLED.delay(1000);
// END

// START:
  flash(THEME_COLORS[3],500,3*NUM_LEDS/5, 4*NUM_LEDS/5);
  FastLED.delay(500);
  
  flash(THEME_COLORS[4],500,4*NUM_LEDS/5, NUM_LEDS-1);
  FastLED.delay(500);
// END

// START:
  all_on(THEME_COLORS[0],4*NUM_LEDS/5, NUM_LEDS-1);
  all_on(THEME_COLORS[1],3*NUM_LEDS/5,4*NUM_LEDS/5);
  all_on(THEME_COLORS[2],2*NUM_LEDS/5,3*NUM_LEDS/5);
  all_on(THEME_COLORS[3],NUM_LEDS/5,2*NUM_LEDS/5);
  all_on(THEME_COLORS[4],0,NUM_LEDS/5);
  FastLED.delay(1000);
  all_off();
// END

// START:
  flash(THEME_COLORS[0],500,0,NUM_LEDS/5);
  FastLED.delay(1000);
  
  flash(THEME_COLORS[1],500, NUM_LEDS/5,2*NUM_LEDS/5);
  FastLED.delay(400);
  
  flash(THEME_COLORS[2],500,2*NUM_LEDS/5, 3*NUM_LEDS/5);
  FastLED.delay(350);
// END

// START:
  blend(CRGB(0x030250),50,10,0,NUM_LEDS-1);
  FastLED.delay(1000);
  all_off();
// END

// START:
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
// END

// START:
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
// END

// START:
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
// END

// START: 
  color_mixer(THEME_COLORS[4],CRGB::Black,0,NUM_LEDS-1);
  shift_strip(3*NUM_LEDS,5,0,NUM_LEDS-1);
  all_off();
// END

// START:
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
// END

// START:
  if (repeats < 15){
    divided_outwards(random_color(),random_color(),10);
    continuous_flow = false;
    repeats++;
  }
  else{
    continuous_flow = true;
    repeats=0;
  }
// END

// START:   
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
// END

// START:
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
// END

// START: 
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
// END

// START:
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
// END

// START:
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
// END

// START: 
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
// END

// START:      
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
// END

// START: 
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
// END

#endif
