/*
 * LED strip program controlled with a PS2 controller
 * Author: Carlos Chinchilla
 * 2013-2014
 * 
*/
/********************** Arduino Functions **************************/
void setup() {
  Serial.begin(57600);
  delay(1000);  // Give wireless ps2 module some time to startup, before configuring it
  
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
  
  // Initialize strip
  strip.begin();
  strip.show();
}
