/*
 * LED & Sound with PS2 control strip program
 * Author: Carlos Chinchilla
 * 2013-2015
 * 
*/
/********************** Sound Functions **************************/
void soundISR()
{
//  if(digitalRead(GATE_PIN)){
    backup();
    all_on(random_color());
//  }
 // else
 //   restore();
}

/********************** Arduino Functions **************************/
void setup() {
  delay(1000); // power-up safety delay
  Serial.begin(57600);
  pinMode(HEART_BEAT_PIN, OUTPUT);
  digitalWrite(HEART_BEAT_PIN, HIGH);
  
  // Initialize temp colors
  color0 = CRGB::Red;
  color1 = CRGB::Green;
  color2 = CRGB::Blue;
  
  // Sound detection
  pinMode(GATE_PIN, INPUT);
  attachInterrupt(IRQ_GATE_IN, soundISR, HIGH);
  
#ifdef USE_PS2_CONTROLLER
  // Initialize PS2 Controller
  int error = 0;
  byte type = 0;
  byte vibrate = 0;
  //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  
  if(error == 0){
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
  if (pressures)
    Serial.println("true ");
  else
    Serial.println("false");
  Serial.print("rumble = ");
  if (rumble)
    Serial.println("true");
  else
    Serial.println("false");  }  
  else if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
  else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  type = ps2x.readType(); 
  switch(type) {
    case 0:
      Serial.println("Unknown Controller type found");
      break;
    case 1:
      Serial.println("DualShock Controller found");
      break;
    case 2:
      Serial.println("GuitarHero Controller found ");
      break;
    case 3:
      Serial.println("Wireless Sony DualShock Controller found");
      break;
    default:
      Serial.print("Received unhandled controller type ");
      Serial.println(type);
   }
  
  // Show demo if no controller found or Guitar Hero Controller
  if(error == 1 || type == 2){
    Serial.println("Starting demo effects");
    continuous_flow = true;
  }
#endif

  // Initialize strips
   FastLED.addLeds<LED_TYPE, STRIP_PIN, COLOR_ORDER>(strip, NUM_LEDS);
   FastLED.setBrightness(brightness);

  // Give initial value to theme colors
  THEME_COLORS[0] = random_color();
  THEME_COLORS[1] = random_color();
  THEME_COLORS[2] = random_color();
  THEME_COLORS[3] = random_color();
  THEME_COLORS[4] = random_color();
  
  // Initialize Sound
  pinMode(GATE_PIN,INPUT);
  
  // Initialize Random Seed
  randomSeed(analogRead(0));
}
