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

/********************** Interrupt elements**************************/
// NOTE: arduino mega has 5 interrupts, the UNO has 2.
#define EFFECT_CHANGER_PIN 2;
volatile uint8_t effect_index = 0;

void increment_effect()
{
  effect_index++;
}

/********************** Basic Functions **************************/

void all_off(uint16_t led1 = 0, uint16_t led2 = NUM_LEDS-1) {
  // all inclusive leds in [leds1,leds2] turn off
  for( int i = led1; i <= led2; i++)
    strip.setPixelColor(i, 0x000000);
  strip.show();
}

void all_on(uint32_t color, uint16_t led1 = 0, uint16_t led2 = NUM_LEDS-1){
   // all inclusive leds in [leds1,leds2] light up to a color
  for( int i = 0; i<NUM_LEDS; i++)
    strip.setPixelColor(i, color);
  strip.show();
}

void fade_to(const uint32_t current_color, const uint32_t target_color,int16_t wait = 100, uint16_t led1 = 0, uint16_t led2 = NUM_LEDS-1){
  // all inclusive leds in [leds1,leds2] light up from a color to a color
  uint32_t color = current_color;
  while (color != target_color){
    for(int i = led1; i <= led2; i++)
      strip.setPixelColor(i, color);
    strip.show();
    color = color_to_target(color, target_color, 10);
    delay(wait);
  }
}

void scroller(uint32_t * colors, uint8_t num_colors,uint16_t steps = 0, int16_t wait = 100, bool left_to_right = true){
  // Create an array of color values, preferably the same size as LED pixes, and scroll through it.
  if (steps == 0)
    steps == num_colors;
  if(left_to_right){
    for(uint16_t offset = 0; offset < steps; offset++){
      for(uint16_t led = 0; led < NUM_LEDS; led++){
        strip.setPixelColor(led,colors[(led+offset)%(num_colors-1)]);
      }
      strip.show();
      delay(wait);
    }
  }
  else{
    for(uint16_t offset = steps; offset > 0; offset--){
      for(uint16_t led = 0; led < NUM_LEDS; led++){
        strip.setPixelColor(led,colors[(led+offset)%(num_colors-1)]);
      }
      strip.show();
      delay(wait);
    }
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

uint32_t dim_color_deprecated(uint32_t color, uint8_t width) {
  // deprecated dimmer
   return (((color & 0xFF0000)/width) & 0xFF0000) + (((color & 0x00FF00)/width) & 0x00FF00) + (((color & 0x0000FF)/width) & 0x0000FF);
}

uint32_t dim_color(uint32_t color, uint32_t chunk) {
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
void wipe_color(uint32_t color, uint16_t wait, uint16_t led1 = 0, uint16_t led2 = NUM_LEDS-1) {
  int16_t increment = (led1 <= led2) ? 1 : -1;
   
  for(uint16_t led = led1; led != led2; led += increment) {
      strip.setPixelColor(led, color);
      strip.show();
      delay(wait);
  }
}

void static_commet_deprecated(uint32_t color){
  for (int led = 0; led < NUM_LEDS; led++){ 
    strip.setPixelColor(led,color);
    color = dim_color_deprecated(color,2);
  }
  strip.show();
}

void static_commet(uint32_t color, uint8_t tail_shortness){
  // for tail_shortness the shorted the value, the longer it is
  for (int led = 0; led < NUM_LEDS; led++){ 
    strip.setPixelColor(led,color);
    color = dim_color(color,tail_shortness);
  }
  strip.show();
}

void flash(uint32_t color, uint16_t wait, uint16_t first = 0, uint16_t last = NUM_LEDS){
  // Quick flash
  all_off();
  for(uint16_t led = first; led < last; led++)
    strip.setPixelColor(led, color);
  strip.show();
  delay(wait);
  all_off();
}

void flash_and_dim(uint32_t color, uint16_t wait, uint16_t wait_dim, uint32_t chunk, uint16_t first = 0, uint16_t last = NUM_LEDS){
  // Quick flash and slow dimmer
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

void fade_color_deprecated(uint32_t color, uint16_t wait) {
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
  uint16_t led = 0;
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

void theaterChaseRainbow(uint16_t wait) {
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

  // Attach interrupts
  attachInterrupt(2, increment_effect, RISING);
}

void demo_effects() {

  // Demo effects

  wipe_color(strip.Color(255, 0, 0), 5, 0, NUM_LEDS); // Red
  wipe_color(strip.Color(0, 255, 0), 5, NUM_LEDS,0); // Green
  wipe_color(strip.Color(0, 0, 255), 5, 0, NUM_LEDS); // Blue
  rainbow(20);
  // rainbowCycle(20);
  //theaterChaseRainbow(200); // takes very long to finish

  // Tested effects

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
  colors[0]=random_color(); for(int l=1;l<NUM_LEDS;l++) colors[l]=colors[l-1]-0x5; scroller(colors,NUM_LEDS,10,true);
  colors[0]=random_color(); for(int l=1;l<NUM_LEDS;l++) colors[l]=colors[l-1]-0x5; scroller(colors,NUM_LEDS,10,false);

}

void routines(){
  // Let's create routines
  uint32_t tonos[] = { 0x000100,0x000200,0x013300,0xFF8000,0x990000,0xCC0066,0xCC0066};
  cross_fade(tonos,7,100,3000);
  all_off();
  fade_to(0xCC0066,0x003400,120);
  fade_to(0x003400,0x000001,120);
  stars_individual(10,70,0x00F330,0x000001);
  
  // Slow pace, tempo 2Hz
  
  // Medium pace, temp 3Hz
}

void loop(){
   uint32_t colors[NUM_LEDS];
    flash(random_color(),250,NUM_LEDS/2+NUM_LEDS/4, NUM_LEDS);
  flash(random_color(),200,NUM_LEDS/2, NUM_LEDS/2+NUM_LEDS/4);
  flash(random_color(),300, 0, NUM_LEDS/4);
  flash(random_color(),300, 0, NUM_LEDS/4);
  flash_and_dim(random_color(),10,15,8, 0, NUM_LEDS);
  flash_and_dim(random_color(),100,15,8, 0, NUM_LEDS);
  flash_and_dim(random_color(),100,15,8, 0, NUM_LEDS);
  colors[0]=random_color(); for(int l=1;l<NUM_LEDS;l++) colors[l]=colors[l-1]-0x5; scroller(colors,NUM_LEDS,10,true);
  colors[0]=random_color(); for(int l=1;l<NUM_LEDS;l++) colors[l]=colors[l-1]-0x5; scroller(colors,NUM_LEDS,10,false);
  all_off();
  delay(1000);
  flash(0x000500,100, 0, NUM_LEDS);
  flash(0x000005,100, 0, NUM_LEDS);
  delay(1000);
}
