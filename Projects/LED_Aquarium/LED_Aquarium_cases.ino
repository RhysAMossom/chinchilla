/*
 * LED & Sound with PS2 control strip program
 * Author: Carlos Chinchilla
 * 2013-2014
 

*/

void set_theme(uint8_t select_theme){
  theme = select_theme;
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
}

void next_theme(){
  set_theme(theme);
  theme++;
}

/********************** State Machine *********************************/
void loop(){
  digitalWrite(HEART_BEAT_PIN, !digitalRead(HEART_BEAT_PIN));
/********************** Main Effects Routine **************************/  
  next_theme();
  
#ifdef SERVO
  rainbow();
  FastLED.delay(1000);
  for (uint8_t a = SERVO_MIN; a <=SERVO_MAX; a++){
    servo.write(a);
    FastLED.delay(100);
  }
  for (uint8_t a = SERVO_MAX; a <=SERVO_MIN; a--){
    servo.write(a);
    FastLED.delay(100);
  }
  backup();
  all_off();
  FastLED.delay(2000);
  restore();
#endif

//  flash_and_dim(random_color(),10,10,10);
//  
//  uint16_t led = random(0,NUM_LEDS-1);
//  explosion(random_color(), strip[led], led, random(10,50),false);
//  flash_grow(random_color(), 0,NUM_LEDS/8);
//  FastLED.delay(1000);
//  
//  CRGB target_color, current_color = random_color();
//  for (uint8_t i= 0; i< 25; i++){
//    target_color = random_color();
//    fade_to(current_color, target_color);
//    current_color = target_color;
//    FastLED.delay(5000);
//  }
//
//  for (uint8_t i= 0; i< 25; i++){
//    palette(random(1,15));
//    shift_strip(NUM_LEDS,400);
//  }
//
//  //Blue water
//  for (uint8_t i= 0; i< 25; i++){
//    color_mixer(CRGB(0x000005),CRGB(0x090885),4*NUM_LEDS/5, NUM_LEDS-1);
//    color_mixer(CRGB(0x090885),CRGB(0x000005),3*NUM_LEDS/5,4*NUM_LEDS/5);
//    color_mixer(CRGB(0x000005),CRGB(0x090885),2*NUM_LEDS/5,3*NUM_LEDS/5);
//    color_mixer(CRGB(0x090885),CRGB(0x000005),NUM_LEDS/5,2*NUM_LEDS/5);
//    color_mixer(CRGB(0x000005),CRGB(0x090885),0,NUM_LEDS/5);
//    shift_strip(NUM_LEDS,250,0,NUM_LEDS-1);
//  }
//  
//  rainbow();
//  for (uint8_t i= 0; i< 25; i++){
//    shift_strip(NUM_LEDS,100,0,NUM_LEDS-1);
//    shift_strip(NUM_LEDS,80,0,NUM_LEDS-1);
//    shift_strip(NUM_LEDS,50,0,NUM_LEDS-1);
//    shift_strip(NUM_LEDS,0,0,NUM_LEDS-1);
//  }
//  
//  wipe_color(CRGB(0, 255, 0), 1500, NUM_LEDS, 0); // Green
//  
//  wipe_color(CRGB(0, 0, 255), 1500, 0, NUM_LEDS-1); // Blue
//  
//  wipe_color(CRGB(255, 0, 0), 1500, NUM_LEDS, 0); // Red
//  
//  flash_and_dim(THEME_COLORS[0],100,100,10,0,NUM_LEDS-1);
//  FastLED.delay(300);
//  
//  flash_and_dim(THEME_COLORS[1],150,120,10,0,NUM_LEDS-1);
//  FastLED.delay(100);
//  
//  flash_and_dim(THEME_COLORS[2],150,150,10,0,NUM_LEDS-1);
//  FastLED.delay(1000);
//  
//  flash(THEME_COLORS[3],100);
//  FastLED.delay(200);
//  
//  flash_and_dim(THEME_COLORS[4],150,18,8,0,NUM_LEDS-1);
//  
//  for (uint8_t i= 0; i < 150; i++){
//    divided_inwards(random_color(),random_color(),10);
//  }
//  
//  blend(THEME_COLORS[1],80,10,0,NUM_LEDS-1);
//  FastLED.delay(1000);
//  
//  color_mixer(THEME_COLORS[2],CRGB::Black,0,NUM_LEDS-1);
//  shift_strip(NUM_LEDS,10,NUM_LEDS-1,0);
//  
//  explosion(THEME_COLORS[3],CRGB::Black,random(NUM_LEDS-1),15,false);
//  FastLED.delay(500);
//  
//  explosion(THEME_COLORS[1],CRGB::Black,random(NUM_LEDS-1),25,false);
//  FastLED.delay(1000);
//  
//  explosion(THEME_COLORS[0],CRGB::Black,random(NUM_LEDS-1),10,false);
//  FastLED.delay(100);
//  
//  explosion(THEME_COLORS[0],CRGB::Black,random(NUM_LEDS-1),10,false);
//  FastLED.delay(1000);
//  
//  explosion(THEME_COLORS[2],CRGB::Black,random(NUM_LEDS-1),10,false);
//  FastLED.delay(100);
//  
//  shift_strip(NUM_LEDS/6,70,0,NUM_LEDS-1);
//  
//  shift_strip(NUM_LEDS/4,40,NUM_LEDS-1,0);
//  explosion(THEME_COLORS[3],CRGB::Black,random(NUM_LEDS-1),25,false);
//  
//  shift_strip(NUM_LEDS/2,35,0,NUM_LEDS-1);
//  
//  shift_strip(NUM_LEDS,30,NUM_LEDS-1,0);
//  explosion(THEME_COLORS[2],CRGB::Black,random(NUM_LEDS-1),25,false);
//  
//  shift_strip(NUM_LEDS/2,25,0,NUM_LEDS-1);
//  
//  shift_strip(NUM_LEDS/4,20,NUM_LEDS-1,0);
//  explosion(THEME_COLORS[4],CRGB::Black,random(NUM_LEDS-1),25,false);
//  
//  shift_strip(3*NUM_LEDS,15,NUM_LEDS-1,0);
//  
//  blend(CRGB::Black,50,10,0,NUM_LEDS-1);
//  FastLED.delay(1000);
  
//  flash(THEME_COLORS[3],500,3*NUM_LEDS/5, 4*NUM_LEDS/5);
//  FastLED.delay(500);
//  
//  flash(THEME_COLORS[4],500,4*NUM_LEDS/5, NUM_LEDS-1);
//  FastLED.delay(500);
//  
//  all_on(THEME_COLORS[0],4*NUM_LEDS/5, NUM_LEDS-1);
//  all_on(THEME_COLORS[1],3*NUM_LEDS/5,4*NUM_LEDS/5);
//  all_on(THEME_COLORS[2],2*NUM_LEDS/5,3*NUM_LEDS/5);
//  all_on(THEME_COLORS[3],NUM_LEDS/5,2*NUM_LEDS/5);
//  all_on(THEME_COLORS[4],0,NUM_LEDS/5);
//  FastLED.delay(1000);
//  all_off();
//  
//  flash(THEME_COLORS[0],500,0,NUM_LEDS/5);
//  FastLED.delay(1000);
//  
//  flash(THEME_COLORS[1],500, NUM_LEDS/5,2*NUM_LEDS/5);
//  FastLED.delay(400);
//  
//  flash(THEME_COLORS[2],500,2*NUM_LEDS/5, 3*NUM_LEDS/5);
//  FastLED.delay(350);
//  
//  blend(CRGB(0x030250),50,10,0,NUM_LEDS-1);
//  FastLED.delay(1000);
//  all_off();
//  
//  flash(THEME_COLORS[3],500,3*NUM_LEDS/5, 4*NUM_LEDS/5);
//  FastLED.delay(500);
//  
//  flash(THEME_COLORS[4],500,4*NUM_LEDS/5, NUM_LEDS-1);
//  FastLED.delay(500);
//  
//  flash(THEME_COLORS[0],500,0,NUM_LEDS/5);
//  FastLED.delay(100);
//  
//  flash(THEME_COLORS[2],500,2*NUM_LEDS/5, 3*NUM_LEDS/5);
//  FastLED.delay(150);
//  
//  flash(THEME_COLORS[3],500,3*NUM_LEDS/5, 4*NUM_LEDS/5);
//  FastLED.delay(150);
//  
//  flash(THEME_COLORS[4],500,4*NUM_LEDS/5, NUM_LEDS-1);
//  FastLED.delay(100);
//  
//  flash(THEME_COLORS[0],500,0,NUM_LEDS/5);
//  FastLED.delay(100);
//  
//  flash(THEME_COLORS[1],500, NUM_LEDS/5,2*NUM_LEDS/5);
//  FastLED.delay(100);
//  
//  flash(THEME_COLORS[2],500,2*NUM_LEDS/5, 3*NUM_LEDS/5);
//  FastLED.delay(100);
//  
//  flash(THEME_COLORS[3],500,3*NUM_LEDS/5, 4*NUM_LEDS/5);
//  FastLED.delay(100);
//  
//  flash(THEME_COLORS[4],500,4*NUM_LEDS/5, NUM_LEDS-1);
//  FastLED.delay(100);
//  
//  flash(THEME_COLORS[0],500,0,NUM_LEDS/5);
//  FastLED.delay(10);
//  
//  flash(THEME_COLORS[1],500, NUM_LEDS/5,2*NUM_LEDS/5);
//  FastLED.delay(10);
//  
//  flash(THEME_COLORS[2],450,2*NUM_LEDS/5, 3*NUM_LEDS/5);
//  FastLED.delay(10);
//  
//  flash(THEME_COLORS[3],450,3*NUM_LEDS/5, 4*NUM_LEDS/5);
//  FastLED.delay(10);
//  
//  flash(THEME_COLORS[4],450,4*NUM_LEDS/5, NUM_LEDS-1);
//  FastLED.delay(10);
//  
//  flash(THEME_COLORS[0],350,0,NUM_LEDS/5);
//  
//  flash(THEME_COLORS[1],350, NUM_LEDS/5,2*NUM_LEDS/5);
//  
//  flash(THEME_COLORS[2],400,2*NUM_LEDS/5, 3*NUM_LEDS/5);
//  
//  flash(THEME_COLORS[3],300,3*NUM_LEDS/5, 4*NUM_LEDS/5);
//  
//  flash(THEME_COLORS[4],300,4*NUM_LEDS/5, NUM_LEDS-1);
//  
//  flash(THEME_COLORS[0],200,0,NUM_LEDS/5);
//  
//  flash(THEME_COLORS[1],200, NUM_LEDS/5,2*NUM_LEDS/5);
//  
//  flash(THEME_COLORS[2],100,2*NUM_LEDS/5, 3*NUM_LEDS/5);
//  
//  flash(THEME_COLORS[3],100,3*NUM_LEDS/5, 4*NUM_LEDS/5);
//  
//  flash(THEME_COLORS[4],50,4*NUM_LEDS/5, NUM_LEDS-1);
//  
//for (uint8_t i= 0; i < 15; i++){
//    flash(THEME_COLORS[0],75,0,NUM_LEDS/5);
//    flash(THEME_COLORS[1],75, NUM_LEDS/5,2*NUM_LEDS/5);
//    flash(THEME_COLORS[2],75,2*NUM_LEDS/5, 3*NUM_LEDS/5);
//    flash(THEME_COLORS[3],75,3*NUM_LEDS/5, 4*NUM_LEDS/5);
//    flash(THEME_COLORS[4],75,4*NUM_LEDS/5, NUM_LEDS-1);
//  }
//  
//  color_mixer(THEME_COLORS[4],CRGB::Black,0,NUM_LEDS-1);
//  shift_strip(3*NUM_LEDS,5,0,NUM_LEDS-1);
//  all_off();
//  FastLED.delay(5000);
//  
//  for (uint8_t i= 0; i < 4; i++){
//    wipe_color(CRGB(0x044000 << i), 50, 0, 3*NUM_LEDS/8);
//    wipe_color(CRGB(0x044000 << i), 50,NUM_LEDS,5*NUM_LEDS/8);
//    explosion(CRGB::Black,THEME_COLORS[2],random(NUM_LEDS-1),100,false);
//    shake();
//  }
//  
//  
//  for (uint8_t i= 0; i < 15; i++){
//    divided_outwards(random_color(),random_color(),10);
//  }
//    
//  wipe_color(CRGB::Black, 25, NUM_LEDS,0);
//  
//  for (uint8_t i= 0; i < 15; i++){
//    divided_inwards(random_color(),random_color(),120);
//    divided_outwards(random_color(),random_color(),120);
//  }
//  
//  flash(THEME_COLORS[4],500,2*NUM_LEDS/5,3*NUM_LEDS/5);
//  explosion(THEME_COLORS[0],CRGB::Black,random(NUM_LEDS-1),10,false);
//  
//  flash(THEME_COLORS[3],500,2*NUM_LEDS/5,3*NUM_LEDS/5);
//  explosion(THEME_COLORS[2],CRGB::Black,random(NUM_LEDS-1),10,false);
//  
//  flash(THEME_COLORS[0],500,2*NUM_LEDS/5,3*NUM_LEDS/5);
//  explosion(THEME_COLORS[1],CRGB::Black,random(NUM_LEDS-1),10,false);
//  
//  flash(THEME_COLORS[2],500,2*NUM_LEDS/5,3*NUM_LEDS/5);
//  explosion(THEME_COLORS[3],CRGB::Black,random(NUM_LEDS-1),10,false);
//  
//  flash(THEME_COLORS[1],500,2*NUM_LEDS/5,3*NUM_LEDS/5);
//  explosion(THEME_COLORS[4],CRGB::Black,random(NUM_LEDS-1),10,false);
//  
//  blend(THEME_COLORS[2],75,5,0,NUM_LEDS-1);
//  FastLED.delay(2000);
//  
//  blend(THEME_COLORS[3],55,5,0,NUM_LEDS-1);
//  FastLED.delay(4000);
//  
//  blend(THEME_COLORS[1],65,5,0,NUM_LEDS-1);
//  FastLED.delay(3000);
//  
//  blend(THEME_COLORS[4],45,5,0,NUM_LEDS-1);
//  FastLED.delay(5000);
//  
//  blend(THEME_COLORS[0],35,5,0,NUM_LEDS-1);
//  FastLED.delay(1000);
//  
//  blend(CRGB::Black,25,5,0,NUM_LEDS-1);
//  
//  for (uint8_t i= 0; i < 25; i++){
//    cross_over(random_color(),random_color(),10);
//    explosion(THEME_COLORS[4],CRGB::Black,random(NUM_LEDS-1),10,false);
//    explosion(THEME_COLORS[1],CRGB::Black,random(NUM_LEDS-1),10,false);
//    explosion(THEME_COLORS[2],CRGB::Black,random(NUM_LEDS-1),10,false);
//    explosion(THEME_COLORS[3],CRGB::Black,random(NUM_LEDS-1),10,false);
//  }
//  
//  for (uint8_t i= 0; i < 25; i++){
//    flash_and_dim(random_color(),100-2*i,18,8,0,NUM_LEDS-1);
//    FastLED.delay(700-(i*i));
//  }
//       
//  for (uint8_t i= 0; i < 25; i++){
//    flash_and_dim(random_color(),100,18,8,0,NUM_LEDS-1);
//    FastLED.delay(200);
//  }
//  
//  for (uint8_t i= 0; i < 5; i++){
//    color_mixer(random_color(),random_color(),4*NUM_LEDS/5, NUM_LEDS-1);
//    color_mixer(random_color(),random_color(),3*NUM_LEDS/5,4*NUM_LEDS/5);
//    color_mixer(random_color(),random_color(),2*NUM_LEDS/5,3*NUM_LEDS/5);
//    color_mixer(random_color(),random_color(),NUM_LEDS/5,2*NUM_LEDS/5);
//    color_mixer(random_color(),random_color(),0,NUM_LEDS/5);
//    FastLED.delay(2000);
//    rainbow();
//    FastLED.delay(2000);
//  }
  
  all_off();
  for(uint8_t i = 0; i < NUM_THEMES; i++){
    for(uint8_t led = i*NUM_LEDS/NUM_THEMES; led < i*(1+ NUM_LEDS/NUM_THEMES); led++){
      strip[led] = THEME_COLORS[i];
    }
    FastLED.show();
    FastLED.delay(2000);
    shake();
  }
}

/*
 * TO DO:
 * - write water
 * - choose license
*/
