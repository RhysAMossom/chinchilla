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

int error = 0;
byte type = 0;
byte vibrate = 0;

void setup(){
  Serial.begin(57600);
  delay(300);  // Give wireless ps2 module some time to startup, before configuring it

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
      Serial.print("Unknown Controller type found");
      break;
    case 1:
      Serial.print("DualShock Controller found");
      break;
    case 2:
      Serial.print("GuitarHero Controller found ");
      break;
    case 3:
      Serial.print("Wireless Sony DualShock Controller found");
      break;
    default:
      Serial.print("Received unhandled controller type ");
      Serial.println(type);
   }
}

void loop() {
  // Show demo if no controller found or Guitar Hero Controller
  if(error == 1 || type == 2){
    demo_effects();
  }
  else { //DualShock Controller
    ps2_cases();
}

void ps2_cases(){
    ps2x.read_gamepad(); //read controller
    if(ps2x.ButtonReleased(PSB_SQUARE))//will be TRUE if button was JUST released
      Serial.println("Square just released");     

    else if(ps2x.ButtonReleased(PSB_SELECT)) {
      // Select RBG colors from joystic values
      Serial.println("Ly\tLx\tRy\tRx");
      delay(50);
      ps2x.read_gamepad();
      while(ps2x.ButtonReleased(PSB_SELECT)){
        Serial.print(ps2x.Analog(PSS_LY), DEC);
        Serial.print("\t");
        Serial.print(ps2x.Analog(PSS_LX), DEC); 
        Serial.print("\t");
        Serial.print(ps2x.Analog(PSS_RY), DEC); 
        Serial.print("\t");
        Serial.println(ps2x.Analog(PSS_RX), DEC);
        ps2x.read_gamepad();
        delay(50);
      }
    }     
  }
  delay(50);  
}
