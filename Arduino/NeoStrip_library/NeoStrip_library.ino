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

uint32_t dim_color_deprecated(uint32_t color, uint8_t width) {
   return (((color & 0xFF0000)/width) & 0xFF0000) + (((color & 0x00FF00)/width) & 0x00FF00) + (((color & 0x0000FF)/width) & 0x0000FF);
}

// Improved dimmer, that takes a decrement value, chunk, from each of the r,g,b values.
// Takes care of underflow by setting respective value to 0
uint32_t dim_color(uint32_t color, uint32_t chunk) {
  uint32_t r = (color & 0xFF0000) > (chunk << 16) ? (color - (chunk << 16)) & 0xFF0000 : 0x000000;
  uint32_t g = (color & 0x00FF00) > (chunk << 8) ? (color - (chunk << 8)) & 0x00FF00 : 0x000000;
  uint32_t b = (color & 0x0000FF) > chunk ? (color - chunk) & 0x0000FF : 0x000000;
  return r+g+b;
}

uint32_t color_to_target(const uint32_t current_color, const uint32_t target_color, uint32_t chunk){
// Increase current color to target color by adding increments of size chunk
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
    color = dim_color_deprecated(color,2);
  }
  strip.show();
}

void static_commet2(uint32_t color, uint8_t tail_shortness){
  // for tail_shortness the shorted the value, the longer it is
  for (int led = 0; led < NUM_LEDS; led++){ 
    strip.setPixelColor(led,color);
    color = dim_color(color,tail_shortness);
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
    color = dim_color(color,chunk);
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
void color_mixer(const uint32_t color1,const uint32_t color2,const uint16_t led1,const uint16_t led2){
  uint32_t chunk = 255/(led2 - led1);
  uint32_t color = color1;
  for(uint16_t led=led1; led < led2; led++){
    strip.setPixelColor(led, color);
    color = color_to_target(color,color2,chunk);
  }
  strip.show();
}

void star(const utin16_t led, uint8_t wait =100,conts uint32_t star_color = 0x00FFFF,const uint32_t background_color = 0x000000){
  uint32_t color = background_color;
  // shine
  while (color != star_color){
    strip.setPixelColor(led,color);
    strip.show();
    color = color_to_target(color, star_color, 5);
    delay(wait);
  } 
  
  // die out
  while (color != background_color){
    strip.setPixelColor(led,color);
    strip.show();
    color = color_to_target(color, background_color, 5);
    delay(wait);
  }
}

void stars_individual(uint8_t wait =100,conts uint32_t star_color = 0x00FFFF,const uint32_t background_color = 0x000000){

}

void stars_overlapping(uint16_t cues = 100, uint8_t wait = 100, uint32_t star_color = 0x00FFFF, uint32_t background_color = 0x000000) {
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

void knight_rider(uint32_t color, uint16_t wait, uint8_t head_size, uint8_t tail_shortness) {
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

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint16_t wait) {
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

/***************** Accidentally created cool effects *********************/

void trencitos(uint16_t cycles, uint16_t wait, uint8_t width, uint32_t color) {
  uint32_t values[NUM_LEDS];
  
  // create static values array
  values[NUM_LEDS] = color;
  for(int v = NUM_LEDS; v > 0; v--){
    values[v-1] = dim_color_deprecated(values[v-1], width);
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
  
  // add random seed
  randomSeed(analogRead(1));
}

void loop() {
   
  // Demo effects
  //colorWipe(strip.Color(255, 0, 0), 5); // Red
  // colorWipe(strip.Color(0, 255, 0), 5); // Green
  //colorWipe(strip.Color(0, 0, 255), 5); // Blue
  //rainbow(20);
  ///rainbowCycle(20);
  //theaterChaseRainbow(200);
  
  // Tested effects
  // static_commet2(strip.Color(100,255,255), 100);
  // knight_rider(strip.Color(200, 100, 80), 0, 5, 15);
  // fade_color(0x890712,5);
  // flash(0x832190,500);
  // flash_and_dim(0xEEEEEE,50,18,8);
  // flash_and_dim(0xEE00EE,50,18,8,0,10); 
  // color_mixer(0xFF00FF,0x000000,2,150);  
  
  // Effects not finished  
  stars();
}
