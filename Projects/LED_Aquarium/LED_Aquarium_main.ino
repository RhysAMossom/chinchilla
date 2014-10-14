/*
 * LED & Sound with PS2 control strip program
 * Author: Carlos Chinchilla
 * 2013-2014
 * 
*/

/********************** Arduino Functions **************************/
void setup() {
  delay(1000); // power-up safety delay
  Serial.begin(57600);
  pinMode(HEART_BEAT_PIN, OUTPUT);
  digitalWrite(HEART_BEAT_PIN, HIGH);
   
  // Initialize strips
   FastLED.addLeds<LED_TYPE, STRIP_PIN, COLOR_ORDER>(strip, NUM_LEDS);
   FastLED.setBrightness(brightness);

  // Give initial value to theme colors
  THEME_COLORS[0] = random_color();
  THEME_COLORS[1] = random_color();
  THEME_COLORS[2] = random_color();
  THEME_COLORS[3] = random_color();
  THEME_COLORS[4] = random_color();
  
  // Initialize Servo
  servo.attach(SERVO_PIN);
  servo.write(SERVO_MIN);
  
  // Initialize Random Seed
  randomSeed(analogRead(0));
}
