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

#define DEBUG

/********************** PS2 Controller library and variables *******/
#include "PS2X_lib.h" //for v1.6
#define PS2_DAT 13  //14 data
#define PS2_CMD 11  //15 command
#define PS2_SEL 10  //16 attention
#define PS2_CLK 12  //17 clock

// - pressures = analog reading of push-butttons 
// - rumble    = motor rumbling
#define pressures   false
#define rumble      false

PS2X ps2x; // create PS2 Controller Class
// The library does not support hot pluggable controllers. 
// You must always either restart your Arduino after you connect the controller, 
// or call config_gamepad(pins) again after connecting the controller.

/********************** LED strip library and variables **********/
#include <Adafruit_NeoPixel.h>

#define STRIP_PIN 6 // Signal Pin that controls strip
#define NUM_LEDS 60*3

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, STRIP_PIN, NEO_GRB + NEO_KHZ800);
/********************** Effects variables ************************/
#include "protocol.h"
#define WAIT    0
#define THEME_CHOOSER 1
#define RAINBOW 255

uint32_t C1,C2,C3,C4,C5; // Theme colors
uint8_t theme = RANDOM_THEME; // theme Counter
uint8_t effect = 0; // Effect Counter

#define SPEED_L 0
#define SPEED_M 128
#define SPEED_H 255
uint8_t wait_factor = SPEED_M;
// Flag when set, one effect will be followed by the other 
// else, only one effect or one family of effects will play
bool continuous_flow = true;
bool continuous_themes = true;

/********************** Basic Functions **************************/

void all_on(uint32_t color, uint16_t led1 = 0, uint16_t led2 = NUM_LEDS){
  // all inclusive leds in [leds1,leds2] light up to a color
  for( int i = led1; i < led2; i++)
    strip.setPixelColor(i, color);
  strip.show();
}

void all_off(uint16_t led1 = 0, uint16_t led2 = NUM_LEDS) {
  // all inclusive leds in [leds1,leds2] turn off
  all_on(0x000000,led1,led2);
}

void fade_to(const uint32_t current_color, const uint32_t target_color,int16_t wait = 100, uint16_t led1 = 0, uint16_t led2 = NUM_LEDS-1){
  // all inclusive leds in [leds1,leds2] light up from a color to a color
  uint32_t color = current_color;
  while (color != target_color){
    for(uint16_t i = led1; i <= led2; i++)
      strip.setPixelColor(i, color);
    strip.show();
    color = color_to_target(color, target_color, 10);
    delay(wait);
  }
}

void shift_strip(uint16_t steps = 1, uint16_t wait = 100, uint16_t led1 = 0, uint16_t led2 = NUM_LEDS-1){
  // Take drawon sequence and shift it many steps, wait between each step, from led1 to led2 inclusive
  int16_t increment = (led1 <= led2) ? 1 : -1;
  
  for (uint16_t s = 0; s <= steps; s++){ 
    uint32_t color1 = strip.getPixelColor(led1);
    for(uint16_t led = led1; led != led2 + increment; led += increment) {
      strip.setPixelColor(led, strip.getPixelColor(led + increment));
    }
    strip.setPixelColor(led2,color1);
    strip.show();
    delay(wait);
  }
}

/********************** Color-returning Functions **************************/

uint32_t random_color(){
  // Return a random color
  uint32_t color = 0;
  color += random(0xFF);
  color = color << 8;
  color += random(0xFF);
  color = color << 8;
  return  color + random(0xFF);
}

uint32_t dim_color(const uint32_t color,const uint32_t chunk) {
  // Improved dimmer, that takes a decrement value, chunk, from each of the r,g,b values.
  // Takes care of underflow by setting respective value to 0
  uint32_t r = (color & 0xFF0000) > (chunk << 16) ? (color - (chunk << 16)) & 0xFF0000 : 0x000000;
  uint32_t g = (color & 0x00FF00) > (chunk << 8) ? (color - (chunk << 8)) & 0x00FF00 : 0x000000;
  uint32_t b = (color & 0x0000FF) > chunk ? (color - chunk) & 0x0000FF : 0x000000;
  return r+g+b;
}

uint32_t color_to_target(const uint32_t current_color, const uint32_t target_color, uint32_t chunk){
  // Increase or decrease current color value to target color by increments of size chunk and return result
  chunk = chunk & 0x0000FF;
  uint32_t current = current_color & 0x0000FF;
  uint32_t target = target_color & 0x0000FF;
  uint32_t r,g,b;

  if(target > current && target - chunk > current)
    b = (current + chunk) & 0x0000FF;
  else if(target < current && target + chunk < current)
    b = (current - chunk) & 0x0000FF;
  else
    b = target;

  chunk = chunk << 8;
  current = current_color & 0x00FF00;
  target = target_color & 0x00FF00;
  if(target > current && target - chunk > current)
    g = (current + chunk) & 0x00FF00;
  else if(target < current && target + chunk < current)
    g = (current - chunk) & 0x00FF00;
  else
    g = target;

  chunk = chunk << 8;
  current = current_color & 0xFF0000;
  target = target_color & 0xFF0000;
  if(target > current && target - chunk > current)
    r = (current + chunk) & 0xFF0000;
  else if(target < current && target + chunk < current)
    r = (current - chunk) & 0xFF0000;
  else
    r = target;

  return r+g+b;
}

uint32_t Wheel(byte WheelPos) {
  // Input a value 0 to 255 to get a color value.
  // The colours are a transition r - g - b - back to r.
  if(WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

/********************** Simple Effects **************************/
// Fill the dots one after the other with a color
void wipe_color(uint32_t color, uint16_t wait, uint16_t led1 = 0, uint16_t led2 = NUM_LEDS-1) {
  int16_t increment = (led1 <= led2) ? 1 : -1;

  for(uint16_t led = led1; led != led2; led += increment) {
    strip.setPixelColor(led, color);
    strip.show();
    delay(wait);
  }
}

void static_commet(uint32_t color, uint8_t tail_shortness){
  // for tail_shortness the shorted the value, the longer it is
  for (int led = 0; led < NUM_LEDS; led++){ 
    strip.setPixelColor(led,color);
    color = dim_color(color,tail_shortness);
  }
  strip.show();
}

void flash(uint32_t color, uint16_t wait, uint16_t led1 = 0, uint16_t led2 = NUM_LEDS){
  // Quick flash
  all_off();
  for(uint16_t led = led1; led < led2; led++)
    strip.setPixelColor(led, color);
  strip.show();
  delay(wait);
  all_off();
}

void flash_and_dim(uint32_t color, uint16_t wait, uint16_t wait_dim, uint32_t chunk, uint16_t led1 = 0, uint16_t led2 = NUM_LEDS){
  // Quick flash and slow dimmer
  all_off();
  for(uint16_t led = led1; led < led2; led++)
    strip.setPixelColor(led, color);
  strip.show();
  delay(wait);
  while (color > 0x000000){
    color = dim_color(color,chunk);
    for(uint16_t led = led1; led < led2; led++)
      strip.setPixelColor(led, color);
    strip.show();
    delay(wait_dim);
  } 
}

void single_flash(uint32_t color = 0, uint8_t wait = 5, uint16_t led1 = 0, uint16_t led2 = NUM_LEDS-1){
  // single LED flashing on current drawn sequence
  int16_t increment = (led1 <= led2) ? 1 : -1;
  for (uint16_t led = led1; led != led2; led += increment){
    uint32_t color_temp = strip.getPixelColor(led);
    strip.setPixelColor(led,color);
    strip.show();
    delay(wait);
    strip.setPixelColor(led,color_temp);
    strip.show();
  }
}

/********************** Complex Effects **************************/
void set_brightness(bool increase = false, uint32_t chunk = 10, uint16_t led1 = 0, uint16_t led2 = NUM_LEDS-1){
  // set brightness of current drawn sequence
  // NOTE: because of overflow, this is destructive (i.e. color cannot be recovered)
  uint32_t color_target = increase ? 0xFFFFFF : 0x000000;

  for(uint16_t led=led1; led <= led2; led++){
    uint32_t color = strip.getPixelColor(led);
    strip.setPixelColor(led,color_to_target(color,color_target,chunk));
  }
  strip.show();
}

void blend(uint32_t color, uint8_t wait=50, uint32_t chunk = 10, uint16_t led1 = 0, uint16_t led2 = NUM_LEDS-1){
  // blend current drawn sequence to a color
  uint32_t color_temp;
  bool done = false;
  
  while (!done){
    done = true;
    for(uint16_t led=led1; led <= led2; led++){
      color_temp = strip.getPixelColor(led);
      if (color_temp != color){
        strip.setPixelColor(led,color_to_target(color_temp,color,chunk));
        done = false;
      }
    }
    strip.show();
    delay(wait);
  }
}

void color_mixer(const uint32_t color1,const uint32_t color2,const uint16_t led1,const uint16_t led2){
  // mix colors along strip
  uint32_t chunk = 255/(led2 - led1);
  uint32_t color = color1;
  for(uint16_t led=led1; led < led2; led++){
    strip.setPixelColor(led, color);
    color = color_to_target(color,color2,chunk);
  }
  strip.show();
}

void three_fades(uint32_t color1, uint32_t color2, uint32_t color3, uint16_t wait){
  // interlaced fades of three colors. This is deprecated, use cross_fade
  uint32_t c1 = 0x000000;
  uint32_t c2 = 0x000000;
  uint32_t c3 = 0x000000;

  all_off();

  // shine color 1
  while (c1 != color1){
    c1 = color_to_target(c1, color1, 10);
    for(uint16_t led = 0;led<NUM_LEDS;led+=3)
      strip.setPixelColor(led,c1);
    strip.show();

    delay(wait);
  } 

  // shine color 2, die out color 1
  while (c1 != 0x000000 || c2 != color2){
    c1 = color_to_target(c1, 0x000000, 10);
    c2 = color_to_target(c2, color2, 10);
    for(uint16_t led = 0; led < NUM_LEDS-3; led+=3){
      strip.setPixelColor(led,c1);
      strip.setPixelColor(led+1,c2);
    }
    strip.show();
    delay(wait);
  }

  // shine color 3, die out color 2
  while (c2 != 0x000000 || c3 != color3){
    c2 = color_to_target(c2, 0x000000, 10);
    c3 = color_to_target(c3, color3, 10);
    for(uint16_t led = 0; led < NUM_LEDS-3; led+=3){
      strip.setPixelColor(led+1,c2);
      strip.setPixelColor(led+2,c3);
    }
    strip.show();
    delay(wait);
  } 

  // die out color 3
  while (c3 != 0x000000){
    c3 = color_to_target(c3, 0x000000, 10);
    for(uint16_t led = 2; led < NUM_LEDS-3; led+=3){
      strip.setPixelColor(led,c3);
    }
    strip.show();
    delay(wait);
  } 
}

void cross_fade(uint32_t * colors, uint8_t num_colors, int16_t wait = 100, int16_t wait_on = 0){ // pass array colors
  // interlaced fades from various colors of a list
  bool killA = false; // decides to kill A when true else kills B
  uint32_t colorA = 0x000000;
  uint32_t colorB = 0x000000;
  all_off();

  // shine color A
  for(uint8_t i = 0; i < num_colors; i++){
    if (killA) {
      while (colorA != 0x000000 || colorB != colors[i]){
        colorA = color_to_target(colorA, 0x000000, 10);
        colorB = color_to_target(colorB, colors[i], 10);
        for(uint16_t led = 0; led < NUM_LEDS-1; led+=2){
          strip.setPixelColor(led,colorA);
          strip.setPixelColor(led+1,colorB);
        }
        strip.show();
        delay(wait);
      }
      killA = !killA;
      delay(wait_on - wait);
    }
    else {
      while (colorA != colors[i] || colorB != 0x000000){
        colorA = color_to_target(colorA, colors[i], 10);
        colorB = color_to_target(colorB, 0x000000, 10);
        for(uint16_t led = 0; led < NUM_LEDS-1; led+=2){
          strip.setPixelColor(led,colorA);
          strip.setPixelColor(led+1,colorB);
        }
        strip.show();
        delay(wait);
      }
      killA = !killA;
      delay(wait_on - wait);
    }
  }
}

void star(const uint16_t led, uint8_t wait =10,const uint32_t star_color = 0x00FFFF,const uint32_t background_color = 0x000000){
  // single star shine
  uint32_t color = background_color;
  all_on(background_color);
  // shine
  while (color != star_color){
    strip.setPixelColor(led,color);
    strip.show();
    color = color_to_target(color, star_color, 10);
    delay(random(wait));
  }

  // die out
  while (color != background_color){
    strip.setPixelColor(led,color);
    strip.show();
    color = color_to_target(color, background_color, 10);
    delay(random(wait));
  }
}

void stars_individual(uint8_t number_stars, uint8_t wait =10, const uint32_t star_color = 0x00FFFF,const uint32_t background_color = 0x000000){
  // Call a number of stars, one shining at a time, on a section of the stripo
  for(uint8_t star_count = 0; star_count < number_stars; star_count++){
    star(random(NUM_LEDS),wait,star_color,background_color);
  }
}

void stars_overlapping(uint16_t cues = 100, uint8_t wait = 100, uint32_t star_color = 0x00F30F, uint32_t background_color = 0x000000) {
  // shinning stars overalapped
  all_on(background_color);
  // common variables
  const uint32_t increment = 5; 

  // Populate stars
  uint16_t stars_on = 0;
  bool leds_on[NUM_LEDS];
  uint8_t leds_cues[NUM_LEDS];
  uint32_t leds_target_colors[NUM_LEDS];
  uint32_t leds_current_colors[NUM_LEDS];

  for(uint16_t led = 0; led < NUM_LEDS; led++){
    if (random(cues) > cues/10){
      leds_on[led] = false;
      // these values are never used
      leds_cues[led]=0;
      leds_target_colors[led] = 0;
      leds_current_colors[led] = 0;
    }
    else {
      leds_on[led] = true;
      leds_cues[led] = cues - random(cues);// TODO: improve sequence of queues given.
      leds_target_colors[led] = star_color;
      leds_current_colors[led] = background_color;
      stars_on++;
    }
  }

  // Run cycles
  uint16_t cue = 0;
  while(cue <= cues && stars_on > 0){
    for(uint16_t led = 0; led < NUM_LEDS; led++){
      if (leds_on[led] && leds_cues[led] >= cue){
        strip.setPixelColor(led, leds_current_colors[led]);
        // increment or decrement color
        leds_current_colors[led] = color_to_target(leds_current_colors[led], leds_target_colors[led], increment);
        // if we reached target, make the new target to turn off
        if (leds_current_colors[led] == leds_target_colors[led])
          leds_target_colors[led] = background_color;
        // All current colors start as background_color but since the comparison happens after
        // calling color_to_target we may assume than when the current color == 0x000000 we are off
        if (leds_current_colors[led] == background_color){
          leds_on[led] = false;
          stars_on--;
        }

      }
      else
        strip.setPixelColor(led,background_color);
    }
    strip.show(); // could be done inside or outside loop
    cue++;
    delay(wait);
  }
  all_on(background_color);
}

void cometa(uint32_t color = strip.Color(200, 100, 80), uint16_t wait = 0, uint8_t head_size = 5, uint8_t tail_shortness = 15) {
  // Similar to knigh_rider, head fades to black
  // for tail_shortness the smaller the value the longer the tail
  uint32_t values[NUM_LEDS];

  // create static values array
  values[0] = color;
  uint16_t v = 1;
  for(; v <= head_size; v++)
    values[v] = color;

  for(; v < NUM_LEDS; v++)
    values[v] = dim_color(values[v-1], tail_shortness);
  //    values[v] = dim_color_deprecated(values[v-1], 2);

  // color LEDs
  for(uint16_t offset = 0; offset < NUM_LEDS; offset++){
    for(uint16_t led = 0; led < NUM_LEDS; led++){
      strip.setPixelColor(led,values[(led+offset)%(NUM_LEDS-1)]);
    }
    strip.show();
    delay(wait);
  }

}

void explosion(uint32_t color, uint32_t background_color, uint16_t start = NUM_LEDS/2, uint16_t length = 15, bool set_back = true){
  // Simulate an explosion of size 2* length
  if(set_back)
    all_on(background_color);

  uint32_t c0 = background_color;
  while (c0 != color){
    strip.setPixelColor(start, c0);
    strip.show();
    delay(random(3)*10);
    c0 = color_to_target(c0, color, 5);
  }
  strip.setPixelColor(start-1, c0);
  strip.setPixelColor(start+1, c0);
  strip.show();
  delay(5);
  uint8_t i = 0;
  while(i <= length){
    strip.setPixelColor(start-i % NUM_LEDS,color);
    strip.setPixelColor(start+i % NUM_LEDS,color);
    strip.show();
    delay(random(1,3) * 10);
    i += random(3);
  }
}

void fireworks(const uint32_t background_color){
  uint8_t num_fireworks = random(1,5);
  for(uint8_t f = 0; f <= num_fireworks; f++){
    explosion(random_color(),background_color, random(NUM_LEDS), 30, false);
    delay(random(1,5)*150);
  }
  all_on(background_color);
}

void rainbow(uint16_t led1 = 0, uint16_t led2 = NUM_LEDS-1) {
  // Draw rainbot evenly distrubuted from led1 to led 2
  int16_t increment = (led1 <= led2) ? 1 : -1;
  int16_t block_size = (led1 <= led2) ? led2 - led1 + 1 : led1 - led2 + 1;
  
  for(uint16_t led = led1; led != led2 + increment; led += increment) {
    strip.setPixelColor(led, Wheel(((led * 256 / block_size)) & 255));
  }
  strip.show();
}

void theater_chase_rainbow(uint16_t wait=50) {
  //Theatre-style crawling lights with rainbow effect
  for (uint8_t j=0; j < 256; j++) { // cycle all 256 colors in the wheel
    for (uint8_t q=0; q < 3; q++) {
      for (uint8_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255)); //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0); //turn every third pixel off
      }
    }
  }
}
