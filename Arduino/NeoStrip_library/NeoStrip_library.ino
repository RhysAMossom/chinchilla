#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUM_LEDS 60*4

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

/********************** Basic Functions **************************/

void all_off() {
  for( int i = 0; i<NUM_LEDS; i++)
    strip.setPixelColor(i, 0x000000);
  strip.show();
}
void all_on(uint32_t color){
  for( int i = 0; i<NUM_LEDS; i++)
    strip.setPixelColor(i, color);
  strip.show();
}

uint32_t dim_color(uint32_t color, uint8_t width) {
   return (((color & 0xFF0000)/width) & 0xFF0000) + (((color & 0x00FF00)/width) & 0x00FF00) + (((color & 0x0000FF)/width) & 0x0000FF);
}

// Improved dimmer, that takes a decrement value, chunk, from each of the r,g,b values.
// Takes care of underflow by setting respective value to 0
uint32_t dim_color2(uint32_t color, uint32_t chunk) {
  uint32_t r = (color & 0xFF0000) > (chunk << 16) ? (color - (chunk << 16)) & 0xFF0000 : 0x000000;
  uint32_t b = (color & 0x00FF00) > (chunk << 8) ? (color - (chunk << 8)) & 0x00FF00 : 0x000000;
  uint32_t g = (color & 0x0000FF) > chunk ? (color - chunk) & 0x0000FF : 0x000000;
  return r+b+g;
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

/********************** Simple Effects **************************/
// Fill the dots one after the other with a color
void colorWipe(uint32_t color, uint16_t wait) {
  for(uint16_t led = 0; led < NUM_LEDS; led++) {
      strip.setPixelColor(led, color);
      strip.show();
      delay(wait);
  }
}

void static_commet(uint32_t color){
  for (int led = 0; led < NUM_LEDS; led++){ 
    strip.setPixelColor(led,color);
    color = dim_color(color,2);
  }
  strip.show();
}

void static_commet2(uint32_t color, uint8_t tail_shortness){
  // for tail_shortness the shorted the value, the longer it is
  for (int led = 0; led < NUM_LEDS; led++){ 
    strip.setPixelColor(led,color);
    color = dim_color2(color,tail_shortness);
  }
  strip.show();
}

void flash(uint32_t color, uint16_t wait, uint16_t first = 0, uint16_t last = NUM_LEDS){
  all_off();
  for(uint16_t led = first; led < last; led++)
    strip.setPixelColor(led, color);
  strip.show();
  delay(wait);
  all_off();
}

void flash_and_dim(uint32_t color, uint16_t wait, uint16_t wait_dim, uint32_t chunk, uint16_t first = 0, uint16_t last = NUM_LEDS){
  all_off();
  for(uint16_t led = first; led < last; led++)
    strip.setPixelColor(led, color);
  strip.show();
  delay(wait);
  while (color > 0x000000){
    color = dim_color2(color,chunk);
    for(uint16_t led = first; led < last; led++)
      strip.setPixelColor(led, color);
    strip.show();
    delay(wait_dim);
  } 
}

void fade_color(uint32_t color, uint16_t wait) {
  uint8_t rgbColour[3];
 
  rgbColour[0] = color & 0xFF0000;
  rgbColour[1] = color & 0x00FF00;
  rgbColour[2] = color & 0x0000FF;
   
  // Choose the colours to increment and decrement.
  for (uint8_t decColour = 0; decColour < 3; decColour += 1) {
    uint8_t incColour = decColour == 2 ? 0 : decColour + 1;
     
    // cross-fade the two colours.
    for(uint8_t i = 0; i < 255; i += 1) {
      rgbColour[decColour] -= 1;
      rgbColour[incColour] += 1;
      for(uint16_t led = 0; led < NUM_LEDS; led++)
        strip.setPixelColor(led,strip.Color(rgbColour[0], rgbColour[1], rgbColour[2]));
      strip.show();
      delay(wait);
    }
  }
}

/********************** Complex Effects **************************/

void stars(uint8_t cycles, uint8_t wait = 10) {
  // common variables
  const uint8_t increment = 5; 
  
  // add random seed
  randomSeed(analogRead(0));
    
  // Populate stars
  bool leds_on[NUM_LEDS];
  uint8_t leds_cues[NUM_LEDS];
  uint32_t leds_target_colors[NUM_LEDS];
  uint32_t leds_current_colors[NUM_LEDS];
  
  for(uint16_t led = 0; led < NUM_LEDS; led++){
    if (random(0,255) < 255/2){
      leds_on[led] = false;
      // these values are never used
      leds_cues[led]=0; 
      leds_target_colors[led] = 0;
      leds_current_colors[led] = 0;
    }
    else {
      leds_on[led] = true;
      leds_cues[led] = random(0,cycles);
      leds_target_colors[led] = 0x674513; //random(0,0xFFFFFF);
      leds_current_colors[led] = 0;
    }
  }
  
  // Run cycles
  for(uint16_t cycle = 0; cycle <= cycles; cycle++){
    for(uint16_t led = 0; led < NUM_LEDS; led++){
      if (leds_on[led] && leds_cues[led] >= cycle){
        strip.setPixelColor(led, leds_current_colors[led]);
        // increment or decrement color
        leds_current_colors[led] = color_to_target(leds_current_colors[led], leds_target_colors[led], chunk);
        // if we reached target, make the new target to turn off
        if (leds_current_colors[led] == leds_target_colors[led])
          leds_target_colors[led] = 0x000000;
          
        // All current colors start as 0x000000 but since the comparison happens after
        // calling color_to_target we may assume than when the current color == 0x000000 we are off
        if (leds_current_colors[led] == 0x000000)
          leds_on[led] = false;
        
      }
    }
    strip.show(); // could be done inside or outside loop
    delay(wait);
  }

/*
Leds_color = black, blue, red, fusia, black,white, black, black
Leds-brightness : 0,0,....,0
Leds_cues : 0, 100, 40, 55,67,19,73,22,74,78,98,54...
For cycle in cycles:
  For led in leds:
    If led.on and led.cue :: cycle:
      Led.write(led.color,led.brightness)
      Led.refresh
      Led.brightness += led.brightness_increment
      If led.brightness == max_brightness or == min_brightness:
        Led.brightness_increment : - led.brightness_icrement
    delay(d)
 */
}

void knight_rider(uint32_t color, uint16_t wait, uint8_t head_size, uint8_t tail_shortness) {
  // for tail_shortness the smaller the value the longer the tail
  uint32_t values[NUM_LEDS];
  
  // create static values array
  values[0] = color;
  uint16_t v = 1;
  for(; v <= head_size; v++)
    values[v] = color;
    
  for(; v < NUM_LEDS; v++)
    values[v] = dim_color2(values[v-1], tail_shortness);
    //    values[v] = dim_color(values[v-1], 2);
  
  // color LEDs
  for(uint16_t offset = 0; offset < NUM_LEDS; offset++){
    for(uint16_t led = 0; led < NUM_LEDS; led++){
      strip.setPixelColor(led,values[(led+offset)%(NUM_LEDS-1)]);
    }
    strip.show();
    delay(wait);
  }

}

// Rainbows
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

/***************** Accidentally created cool effects *********************/

void trencitos(uint16_t cycles, uint16_t wait, uint8_t width, uint32_t color) {
  uint32_t values[NUM_LEDS];
  
  // create static values array
  values[NUM_LEDS] = color;
  for(int v = NUM_LEDS; v > 0; v--){
    values[v-1] = dim_color(values[v-1], width);
  }
  
  // Cycles
  for(int i = 0; i < cycles; i++){
    for (int count = 0; count < NUM_LEDS; count++) {
      for(int led = 0; led < NUM_LEDS; led++){
        strip.setPixelColor(led,values[(count+led) % NUM_LEDS]);
      }
      strip.show();
      delay(wait);
    }
  }
}

/********************** Arduino Functions **************************/


void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  
  //all_off();
  
  // Demo effects
  //colorWipe(strip.Color(255, 0, 0), 5); // Red
  //colorWipe(strip.Color(0, 255, 0), 5); // Green
  //colorWipe(strip.Color(0, 0, 255), 5); // Blue
  //rainbow(20);
  ///rainbowCycle(20);

  // Tested effects
  // static_commet2(strip.Color(100,255,255), 100);
  // knight_rider(strip.Color(200, 100, 80), 0, 5, 15);
  // fade_color(0x890712,5);
  // flash(0x832190,500);
  // flash_and_dim(0xEEEEEE,50,18,8);
  // flash_and_dim(0xEE00EE,50,18,8,0,10); 
  
  // Effects not finished  


  stars(1000,10);
}
