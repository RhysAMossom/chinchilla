/*
 * LED & Sound with PS2 control strip program
 * Author: Carlos Chinchilla
 * 2013-2014
 * 
 
*/

#define DEBUG_LEDS
/********************** LED strip library and variables **********/
#include <FastLED.h>

#define HEART_BEAT_PIN 13
// 44 pixels per fins, 3 fins per Arduino board
// 148 pixels per ribs, 2 ribs per Arduino board

#define NUM_LEDS 15
#define STRIP_PIN 6// Signal Pin that controls strip
#define LED_TYPE    WS2812
#define COLOR_ORDER RGB
CRGB strip[NUM_LEDS];
CRGB backup_strip[NUM_LEDS];

/********************** PS2 controller library and variables ******/
#include "PS2X_lib.h"
#define PS2_DAT 12  //data (brown)
#define PS2_CMD 10  // command (orange)
#define PS2_SEL 9  // attention (yellow)
#define PS2_CLK 11  // clock (blue)

// - pressures = analog reading of push-butttons 
// - rumble    = motor rumbling
#define pressures   false
#define rumble      false

PS2X ps2x; // create PS2 Controller Class

/********************** Servo variables **************************/
#include <Servo.h> 
 
Servo servo;
#define SERVO_PIN 5
#define SERVO_MIN 0
#define SERVO_MAX 180

/********************** Effects variables *************************/
#define WAIT    0
#define THEME_CHOOSER 1
#define RAINBOW 2
#define FLASH 3
#define FADE 4

uint8_t R,G,B;
uint8_t brightness = 255;
#define NUM_THEMES 5
CRGB THEME_COLORS[NUM_THEMES]; // Theme colors
uint8_t theme = 0; // Theme Counter
uint8_t effect = 5; // Effect Counter
uint8_t wait_factor = 5; // Used for speed Counter
uint8_t repeats = 0; // Repeats Counter to avoid blocking loops in state machine

// Flag when set, one effect will be followed by the other 
// else, only one effect or one family of effects will play
bool continuous_flow = true;
bool continuous_themes = true;

/********************** Basic Functions **************************/
void all_on(CRGB color, uint16_t led1 = 0, uint16_t led2 = NUM_LEDS-1){
  // all inclusive leds in [leds1,leds2] light up to a color
  for(int i = led1; i <= led2; i++)
    strip[i] = color;
  FastLED.show();
}

void all_off(uint16_t led1 = 0, uint16_t led2 = NUM_LEDS-1) {
  // all inclusive leds in [leds1,leds2] turn off
  all_on(CRGB(0x000000),led1,led2);
}

void fade_to(const CRGB current_color, const CRGB target_color,int16_t wait = 100, uint16_t led1 = 0, uint16_t led2 = NUM_LEDS-1){
  // all inclusive leds in [leds1,leds2] light up from a color to a color
  CRGB color = current_color;
  while (color != target_color){
    for(uint16_t i = led1; i <= led2; i++)
      strip[i] = color;
    FastLED.show();
    color = color_to_target(color, target_color, 10);
    FastLED.delay(wait);
  }
  // Don't forget the last color step
  for(uint16_t i = led1; i <= led2; i++)
    strip[i] = color;
}

void shift_strip(uint16_t steps = 1, uint16_t wait = 100, uint16_t led1 = 0, uint16_t led2 = NUM_LEDS-1){
  // Take drawn sequence and shift it many steps, wait between each step, from led1 to led2 inclusive
  int16_t increment = (led1 <= led2) ? 1 : -1;
  for (uint16_t s = 0; s <= steps; s++){ 
    CRGB color1 = strip[led1];
    for(uint16_t led = led1; led != led2; led += increment) {
      strip[led] =  strip[led + increment];
    }
    strip[led2] = color1;
    FastLED.show();
    FastLED.delay(wait);
  }
}

void backup(uint16_t led1 = 0, uint16_t led2 = NUM_LEDS-1){
  // Backup strip drawing to be recovered later
  for(uint16_t led = led1; led <= led2; led++) {
      backup_strip[led] = strip[led];
  }
}

void restore(uint16_t led1 = 0, uint16_t led2 = NUM_LEDS-1){
  // Restore and show previously backed up strip drawing
  for(uint16_t led = led1; led <= led2; led++) {
      strip[led] = backup_strip[led];
  }
  FastLED.show();
}

void shake(uint16_t cycles = 10, uint16_t amplitude = 10, uint16_t wait = 5, uint16_t led1 = 0, uint16_t led2 = NUM_LEDS-1){
  while(cycles > 0){
    cycles--;
    shift_strip(random(1,amplitude),wait,0,NUM_LEDS-1);
    FastLED.delay(10+random(wait));
    shift_strip(random(1,amplitude),wait,NUM_LEDS-1,0);
  }
}

/********************** Color-returning Functions **************************/

CRGB random_color(uint8_t saturation = 200, uint8_t value=200){
  // Return a random color
  return CHSV(random(0,255), saturation, value);
}

CRGB dim_color(CRGB color, uint8_t chunk) {
  // Improved dimmer, that takes a decrement value, chunk, from each of the r,g,b values.
  // Takes care of underflow by setting respective value to 0

  uint8_t r = color.r > chunk ? color.r - chunk : 0x000000;
  uint8_t g = color.g > chunk ? color.g - chunk : 0x000000;
  uint8_t b = color.b > chunk ? color.b - chunk : 0x000000;  
  return CRGB(r,g,b);
}

CRGB color_to_target(CRGB current_color, CRGB target_color, uint8_t chunk){
  // Increase or decrease current color value to target color by increments of size chunk and return result
  CRGB color;
  for (uint8_t i =0; i < 3; i++){
    if(target_color[i] > current_color[i] && target_color[i] - chunk > current_color[i])
      color[i] = current_color[i] + chunk;
    else if(target_color[i] < current_color[i] && target_color[i] + chunk < current_color[i])
      color[i] = current_color[i] - chunk;
    else
      color[i] = target_color[i];
  }
  return color;
}

CRGB Wheel(byte WheelPos) {
  // Input a value 0 to 255 to get a color value.
  // The colours are a transition r - g - b - back to r.
  if(WheelPos < 85) {
    return CRGB(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return CRGB(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return CRGB(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

/********************** Simple Effects **************************/
// Fill the dots one after the other with a color
void wipe_color(CRGB color, uint16_t wait, uint16_t led1 = 0, uint16_t led2 = NUM_LEDS-1) {
  return;
  int16_t increment = (led1 <= led2) ? 1 : -1;

  for(uint16_t led = led1; led != led2 + increment; led += increment) {
    strip[led] = color;
    FastLED.show();
    FastLED.delay(wait);
  }
}

void flash(CRGB color, uint16_t wait, uint16_t led1 = 0, uint16_t led2 = NUM_LEDS-1){
  // Quick flash
  all_off(led1,led2);
  for(uint16_t led = led1; led <= led2; led++)
    strip[led] = color;
  FastLED.show();
  FastLED.delay(wait);
  all_off(led1,led2);
}

void flash_and_dim(CRGB color, uint16_t wait, uint16_t wait_dim, uint8_t chunk, uint16_t led1 = 0, uint16_t led2 = NUM_LEDS-1){
  // Quick flash and slow dimmer
  all_off(led1,led2);
  for(uint16_t led = led1; led <= led2; led++)
    strip[led] = color;
  FastLED.show();
  FastLED.delay(wait);
  while (color[0] > 0x000000){
    color = dim_color(color,chunk);
    for(uint16_t led = led1; led <= led2; led++)
      strip[led] = color;
    FastLED.show();
    FastLED.delay(wait_dim);
  } 
}

void single_flash(CRGB color, uint16_t wait = 5, uint16_t led1 = 0, uint16_t led2 = NUM_LEDS-1){
  // single LED flashing on current drawn sequence
  int16_t increment = (led1 <= led2) ? 1 : -1;
  for (uint16_t led = led1; led != led2; led += increment){
    CRGB color_temp = strip[led];
    strip[led] = color;
    FastLED.show();
    FastLED.delay(wait);
    strip[led] = color_temp;
    FastLED.show();
  }
}

void flash_grow(CRGB color, uint16_t wait = 5,uint8_t start = NUM_LEDS/8, uint8_t length = NUM_LEDS/8){
  for(uint16_t offset=0; offset < length; offset+=2){
    strip[start + offset] = color;
    strip[start - offset] = color;
    strip[start + offset +1] = color;
    strip[start - offset -1] = color;
    FastLED.show();
    FastLED.delay(wait);
  }
  fade_to(color,CRGB::Black,0,start-length,start+length);
}

/********************** Complex Effects **************************/

void blend(CRGB color, uint16_t wait=50, uint8_t chunk = 10, uint16_t led1 = 0, uint16_t led2 = NUM_LEDS-1){
  // blend current drawn sequence to a color
  CRGB color_temp;
  bool done = false;
  
  while (!done){
    done = true;
    for(uint16_t led=led1; led <= led2; led++){
      color_temp = strip[led];
      if (color_temp != color){
        strip[led] = color_to_target(color_temp,color,chunk);
        done = false;
      }
    }
    FastLED.show();
    FastLED.delay(wait);
  }
}

void color_mixer(CRGB color1, CRGB color2, uint16_t led1 = 0,uint16_t led2 = NUM_LEDS-1){
  // mix colors along strip
  CRGB color = color1;
  for(uint16_t led=led1; led <= led2; led++){
    strip[led] = color;
    color = color_to_target(color,color2,10);
  }
  FastLED.show();
}

void star(const uint16_t led, uint16_t wait =10,const CRGB star_color = CRGB(0x00FFFF),const CRGB background_color = CRGB(0x000000)){
  // single star shine
  CRGB color = background_color;
  all_on(background_color);
  // shine
  while (color != star_color){
    strip[led] = color;
    FastLED.show();
    color = color_to_target(color, star_color, 10);
    FastLED.delay(random(wait));
  }

  // die out
  while (color != background_color){
    strip[led] = color;
    FastLED.show();
    color = color_to_target(color, background_color, 10);
    FastLED.delay(random(wait));
  }
}

void explosion(CRGB color, CRGB background_color, uint16_t start = NUM_LEDS/2, uint16_t length = 40, bool set_back = true){
  // Simulate an explosion of size 2* length
  if(set_back)
    all_on(background_color);
  
  // light up from background color to color
  CRGB c0 = background_color;
  while (c0 != color){
    strip[start] = c0;
    FastLED.show();
    FastLED.delay(random(2)*5);
    c0 = color_to_target(c0, color, 5);
  }
  strip[start-1] = c0;
  strip[start+1] = c0;
  FastLED.show();
  FastLED.delay(5);
  uint16_t led = 2;
  uint16_t i = 0;
  // Modulo is does not work with FastLED library
  while(i <= length){
    i += random(3,10);
    led = (start > i) ? start - i : led;
    strip[led] = color;
    led = (start + i) < NUM_LEDS ? start + i : led;
    strip[led] = color;
    FastLED.show();
    FastLED.delay(random(1,3) * 10);
  }
}

void rainbow(uint16_t led1 = 0, uint16_t led2 = NUM_LEDS-1) {
  // Draw rainbot evenly distrubuted from led1 to led 2
  int16_t increment = (led1 <= led2) ? 1 : -1;
  int16_t block_size = (led1 <= led2) ? led2 - led1 + 1 : led1 - led2 + 1;
  
  for(uint16_t led = led1; led != led2 + increment; led += increment) {
    strip[led] = Wheel(((led * 256 / block_size)) & 255);
  }
  FastLED.show();
}

void divided_outwards(CRGB color1, CRGB color2, uint16_t wait=10) {
  for(uint16_t led = 0; led < NUM_LEDS/2; led++){
    strip[NUM_LEDS/2 + led] = color1;
    strip[NUM_LEDS/2 - led] = color2;
    FastLED.show();
    FastLED.delay(wait);
  }
}

void divided_inwards(CRGB color1, CRGB color2, uint16_t wait=10) {
  for(uint16_t led = 0; led <= NUM_LEDS/2; led++){
    strip[0 + led] = color1;
    strip[NUM_LEDS - led] = color2;
    FastLED.show();
    FastLED.delay(wait);
  }
}

void cross_over(CRGB color1, CRGB color2, uint16_t wait=10) {
  divided_outwards(color1,color2,wait);
  FastLED.delay(wait);
  divided_inwards(color1,color2,wait);
}

void palette(uint8_t palette_num, uint16_t led1=0, uint16_t led2 = NUM_LEDS-1){
  int16_t increment = (led1 <= led2) ? 1 : -1;
  uint8_t color_index = 0;
  CRGBPalette16 current_palette = RainbowColors_p;
  TBlendType    current_blending = BLEND;
  palette_num = palette_num %10;
  
  switch(palette_num){
    case 1:
      current_palette = RainbowStripeColors_p; current_blending = NOBLEND; break;
    case 2:
      current_palette = RainbowStripeColors_p; current_blending = BLEND; break;
    case 3:
      current_palette = CloudColors_p; current_blending = BLEND; break;
    case 4:
      current_palette = PartyColors_p; current_blending = BLEND; break;
    case 5:
      current_palette = OceanColors_p; current_blending = BLEND; break;
    case 6:
      current_palette = LavaColors_p; current_blending = BLEND; break;
    case 7:
      current_palette = ForestColors_p; current_blending = BLEND; break;
    case 8:
      current_palette = PartyColors_p; current_blending = BLEND; break;
    default:
      current_palette = RainbowColors_p; current_blending = BLEND;
  }
 
  for(uint16_t led = led1; led != led2 + increment; led += increment) {
    strip[led] = ColorFromPalette(current_palette, color_index, brightness, current_blending);
    color_index +=5;
  }
  FastLED.show();
}
