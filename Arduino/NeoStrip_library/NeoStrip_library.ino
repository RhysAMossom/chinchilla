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

/********************** Simple Effects **************************/
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

/********************** Complex Effects **************************/

void stars(uint8_t cycles, uint8_t wait = 10) {
  // common variables
  uint8_t max_brigtness = 255;
  uint8_t min_brigtness = 0;
  uint8_t brightness_increment = 5;
  
  // Populate stars
  bool leds_on[NUM_LEDS];
  uint8_t leds_brightness[NUM_LEDS];
  uint8_t leds_cues[NUM_LEDS];
  uint32_t leds_colors[NUM_LEDS];
  randomSeed(analogRead(0));
  for(uint16_t led = 0; led < NUM_LEDS; led++){
    leds_brightness[led] = 0;
    if (random(0,255) < 255/2){
      leds_on[led] = false;
      leds_cues[led]=0; // this element in array is never used
    }
    else {
      leds_on[led] = true;
      leds_cues[led] = random(0,cycles);
    }
  }
  
  // Run cycles
  for(uint16_t cycle = 0; cycle <= cycles; cycle++){
    for(uint16_t led = 0; led < NUM_LEDS; led++){
      if (leds_on[led] && leds_cues[led] <= cycle){
        strip.setPixelColor(led, leds_colors[led] && leds_brightness[led]);
        strip.show(); // could be done inside or outside loop, TO DO: change effects
        leds_brightness[led] += brightness_increment;
        if (leds_brightness[led] >= max_brigtness) {
          leds_brightness[led] = - brightness_increment;
        }
        else if(leds_brightness[led] <= min_brigtness){
          leds_cues[led] = false;
        }
      }
    }
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

void knight_rider(uint16_t wait, uint8_t width, uint32_t color) {
  uint32_t values[NUM_LEDS];
  
  // create static values array
  values[0] = color;
  uint16_t v = 1;
  for(; v <= width; v++)
    values[v] = color;
    
  for(; v < NUM_LEDS; v++)
    values[v] = dim_color(values[v-1], 2);
  
  // color LEDs
  for(uint16_t offset = 0; offset < NUM_LEDS; offset++){
    for(uint16_t led = 0; led < NUM_LEDS; led++){
      strip.setPixelColor(led,values[(led+offset)%(NUM_LEDS-1)]);
    }
    strip.show();
    delay(wait);
  }

}

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

// Cycles - one cycle is scanning through all pixels left then right (or right then left)
// Speed - how fast one cycle is (32 with 16 pixels is default KnightRider speed)
// Width - how wide the trail effect is on the fading out LEDs. The original display used
// light bulbs, so they have a persistance when turning off. This creates a trail.
// Effective range is 2 - 8, 4 is default for 16 pixels. Play with this.
// Color - 32-bit packed RGB color value. All pixels will be this color.
// knightRider(cycles, speed, width, color);
void knightRider(uint16_t cycles, uint16_t wait, uint8_t width, uint32_t color) {
  uint32_t old_val[NUM_LEDS]; // up to 256 lights!
  // Larson time baby!
  for(int i = 0; i < cycles; i++){
    for (int count = 1; count < NUM_LEDS; count++) {
      strip.setPixelColor(count, color);
//      strip.show();
      old_val[count] = color;
      for(int x = count; x > 0; x--) {
        old_val[x-1] = dim_color(old_val[x-1], width);
        strip.setPixelColor(x-1, old_val[x-1]);
        strip.show();
      }
      delay(wait);
    }
    for (int count = NUM_LEDS-1; count >= 0; count--) {
      strip.setPixelColor(count, color); strip.show();
      delay(wait);
      old_val[count] = color;
      for(int x = count; x<= NUM_LEDS; x++) {
        old_val[x-1] = dim_color(old_val[x-1], width);
        strip.setPixelColor(x+1, old_val[x+1]); 
        strip.show();
      }
    }
  }
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

void static_commet(uint32_t color){
  for (int led = 0; led < NUM_LEDS; led++){ 
    strip.setPixelColor(led,color);
    color = dim_color(color,2);
  }
  strip.show();
}

/********************** Arduino Functions **************************/


void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  
  all_off();
  delay(1000);
  //colorWipe(strip.Color(255, 0, 0), 5); // Red
  //colorWipe(strip.Color(0, 255, 0), 5); // Green
  //colorWipe(strip.Color(0, 0, 255), 5); // Blue
  rainbow(20);
  delay(1000);
  rainbowCycle(20);

  knight_rider(10, 10, strip.Color(0, 200, 80));
  //stars(10,10);
}
