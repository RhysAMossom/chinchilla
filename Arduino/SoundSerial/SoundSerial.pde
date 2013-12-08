/************** Incomming commands *****************/
char inCommand;
// Vehicle Commands
const char AUTONOMOUS = 'a';
const char WIRELESS = 'w';
const char STOP = 'h';
const char BACK = 'b';
const char FRONT = 'f';
const char CALIBRATE = 'c';

const char LEFT = 'l';// for both vehicle and camera
const char RIGHT = 'r';// for both vehicle and camera
const char INSTRUCTIONS = 'i';// for both vehicle and camera

// Camera Commands
const char CAMERA = 'm';
const char UP = 'u';
const char DOWN = 'd';
const char CENTER = 'e';
const char COORDINATES = 'o';
const char SMOOTH_MOVE_TO = 's';
const char NUMBERS = 'n';
/****************************************************/
bool camControl = false;
int x,y;

#include <FatReader.h>
#include <SdReader.h>
#include <avr/pgmspace.h>
#include "WaveUtil.h"
#include "WaveHC.h"

SdReader card;    // This object holds the information for the card
FatVolume vol;    // This holds the information for the partition on the card
FatReader root;   // This holds the information for the filesystem on the card
FatReader f;      // This holds the information for the file we're play
WaveHC wave;      // This is the only wave (audio) object, since we will only play one at a time

// this handy function will return the number of bytes currently free in RAM, great for debugging!   
int freeRam(void)
{
  extern int  __bss_end; 
  extern int  *__brkval; 
  int free_memory; 
  if((int)__brkval == 0) {
    free_memory = ((int)&free_memory) - ((int)&__bss_end); 
  }
  else {
    free_memory = ((int)&free_memory) - ((int)__brkval); 
  }
  return free_memory; 
} 

void sdErrorCheck(void)
{
  if (!card.errorCode()) return;
  putstring("\n\rSD I/O error: ");
  Serial.print(card.errorCode(), HEX);
  putstring(", ");
  Serial.println(card.errorData(), HEX);
  while(1);
}

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps for debugging
  
  putstring_nl("\nWave test!");  // say we woke up!
  
  putstring("Free RAM: ");       // This can help with debugging, running out of RAM is bad
  Serial.println(FreeRam());

  //  if (!card.init(true)) { //play with 4 MHz spi if 8MHz isn't working for you
  if (!card.init()) {         //play with 8 MHz spi (default faster!)  
    putstring_nl("Card init. failed!");  // Something went wrong, lets print out why
    sdErrorCheck();
    while(1);
  }
  
  // enable optimize read - some cards may timeout. Disable if you're having problems
  card.partialBlockRead(true);
  
  // Now we will look for a FAT partition!
  uint8_t part;
  for (part = 0; part < 5; part++) {   // we have up to 5 slots to look in
    if (vol.init(card, part)) 
      break;                           // we found one, lets bail
  }
  if (part == 5) {                     // if we ended up not finding one  :(
    putstring_nl("No valid FAT partition!");
    sdErrorCheck();      // Something went wrong, lets print out why
    while(1); 
  }
  
  // Lets tell the user about what we found
  putstring("Using partition ");
  Serial.print(part, DEC);
  putstring(", type is FAT");
  Serial.println(vol.fatType(),DEC);     // FAT16 or FAT32?
  
  // Try to open the root directory
  if (!root.openRoot(vol)) {
    putstring_nl("Can't open root dir!"); // Something went wrong,
    while(1);  
  }
  
  //Speak
  playComplete("WHITE.WAV");
  playComplete("IAMAWAKE.WAV");  
  delay(1000);
  playComplete("DONSETUP.WAV");
}// end setup()



// Plays a full file from beginning to end with no pause.
void playComplete(char *name) {
  // call our helper to find and play this name
  playFile(name);
  while (wave.isplaying) {
  // do nothing while its playing
  }
  // now its done playing
}

void playNumber(int n){
  if(n <1000){
    char buffer[4];
    int curNum;
    sprintf (buffer,"%d", n);
    for(int i = 0; i<4; i++){
      curNum = buffer[i] -'0';
      switch(curNum){
      case 0:
      //playComplete("0.WAV");
        break;
      case 1:
        playComplete("1.WAV");
        break;
      case 2:
        playComplete("2.WAV");
      case 3:
        playComplete("3.WAV");
        break;
      case 4:
        playComplete("4.WAV");
        break;
      case 5:
        playComplete("5.WAV");
        break;
      case 6:    
        playComplete("6.WAV");
        break;
      case 7:    
        playComplete("7.WAV");
        break;
      case 8:
        playComplete("8.WAV");
        break;
      case 9:
        playComplete("9.WAV");
        break;
      case 10:
        playComplete("10.WAV");
        break;
      }
    }
  }
}//end playNumber()

void playFile(char *name) {
  // see if the wave object is currently doing something
  if (wave.isplaying) {// already playing something, so stop it!
    wave.stop(); // stop it
  }
  // look in the root directory and open the file
  if (!f.open(root, name)) {
    putstring("Couldn't open file "); Serial.print(name); return;
  }
  // OK read the file and turn it into a wave object
  if (!wave.create(f)) {
    putstring_nl("Not a valid WAV"); return;
  }
  
  // ok time to play! start playback
  wave.play();
}

// Parsing
int serialReadInt(){
 int i, serAva;                        // i is a counter, serAva hold number of serial available
 char inputBytes [7];                  // Array hold input bytes
 char * inputBytesPtr = &inputBytes[0];// Pointer to the first element of the array
   
 if (Serial.available()>0)             // Check to see if there are any serial input
 {
   delay(1000);                           // Delay for terminal to finish transmitted
                                       // 5mS work great for 9600 baud (increase this number for slower baud)
   serAva = Serial.available();        // Read number of input bytes
   for (i=0; i<serAva; i++)            // Load input bytes into array
     inputBytes[i] = Serial.read();
   inputBytes[i] =  '\0';              // Put NULL character at the end
   Serial.flush();
   return atoi(inputBytesPtr);         // Call atoi function and return result
 }
 else
   return -1;                          // Return -1 if there is no input
}// end SerialReadInt()

void getCoordinatesFromUser(int* X, int* Y){
  // Get X
  int& xCoor = *X;
  int& yCoor = *Y;
  
  Serial.println("Waiting for xxx coordinate");
  xCoor = serialReadInt();
  while(xCoor < 0){
    xCoor = serialReadInt();
  }
 
  // Get Y
  Serial.println("Waiting for yyy coordinate");
  yCoor = serialReadInt();
  while(yCoor < 0){
    yCoor = serialReadInt();
  }
}// end getCoordinatesFromUser()


void loop() {
  if (Serial.available()) {
    inCommand = Serial.read();
    switch((int)inCommand){
      case (int)WIRELESS:
        playComplete("WHITE.WAV");
        playComplete("WIRELESS.WAV");
        playComplete("MODE.WAV");
        playComplete("ON.WAV");
        break;
      case (int)STOP:
        playComplete("STOP.WAV");
        break;
      case (int)LEFT:
        playComplete("LEFT.WAV");
        break;
      case (int)RIGHT:
        playComplete("RIGHT.WAV");
        break;
      case (int)FRONT:
        playComplete("FOWARDS.WAV");
        break;
      case (int)BACK:
        playComplete("BACK.WAV");
        break;
      case (int)CALIBRATE:
        playComplete("CALI.WAV");
        break;
      case (int)AUTONOMOUS:
        playComplete("STOP.WAV");
        delay(500);
        playComplete("WIRELESS.WAV");
        playComplete("MODE.WAV");
        playComplete("OFF.WAV");
        delay(500);
        playComplete("AUTO.WAV");
        playComplete("MODE.WAV");
        playComplete("ON.WAV");
        break;
       case (int)NUMBERS:
       //playComplete("0.WAV");
        playComplete("1.WAV");
        playComplete("2.WAV");
        playComplete("3.WAV");
        playComplete("4.WAV");
        playComplete("5.WAV");
        playComplete("6.WAV");
        playComplete("7.WAV");
        playComplete("8.WAV");
        playComplete("9.WAV");
        playComplete("10.WAV");
        break;
      case (int)CAMERA:
      /***** Camera Mode ******/
        playComplete("CAMERA.WAV");
        playComplete("MODE.WAV");
        playComplete("ON.WAV");
        camControl = true;
        Serial.flush();
        while(camControl){
          if (Serial.available()) {
            inCommand = Serial.read();
            switch((int)inCommand){
              case (int)CAMERA:
                 playComplete("WHITE.WAV");
                 playComplete("CAMERA.WAV");
                 playComplete("MODE.WAV");
                 playComplete("ON.WAV");
                 break;
              case (int)UP:
                 playComplete("CAMERA.WAV");
                 playComplete("UP.WAV");
                 break;
               case (int)DOWN:
                 playComplete("CAMERA.WAV");
                 playComplete("DOWN.WAV");
                 break;
               case (int)CENTER:
                 playComplete("CAMERA.WAV");
                 playComplete("CENTER.WAV");
                 break;
               case (int)LEFT:
                 playComplete("CAMERA.WAV");
                 playComplete("LEFT.WAV");
                 break;
               case (int)RIGHT:
                 playComplete("CAMERA.WAV");
                 playComplete("RIGHT.WAV");
                 break;
               case (int)COORDINATES:
                 Serial.println("Move Camera To Coordinates");
                 x = 0;
                 y = 0;
                 getCoordinatesFromUser(&x,&y);
                 playComplete("MOVETO.WAV");
                 playNumber(x);
                 delay(500);
                 playNumber(y);
                 //moveTo(x,y);
                 break;
               case (int)SMOOTH_MOVE_TO:
                 Serial.println("Camera Smooth Move To Coordinates");
                 x = 0;
                 y = 0;
                 getCoordinatesFromUser(&x,&y);
                 playComplete("SMOOTH.WAV");
                 playComplete("MOVETO.WAV");
                 playNumber(x);
                 delay(500);
                 playNumber(y);
                 //smoothMoveTo(x,y);
                 break;
                case (int)WIRELESS:
                  playComplete("CAMERA.WAV");
                  playComplete("MODE.WAV");
                  playComplete("OFF.WAV");
                  delay(500);
                  playComplete("WIRELESS.WAV");
                  playComplete("MODE.WAV");
                  playComplete("ON.WAV");
                  camControl = false;
                  break;
                case (int)AUTONOMOUS:
                  playComplete("CAMERA.WAV");
                  playComplete("MODE.WAV");
                  playComplete("OFF.WAV");
                  delay(500);
                  playComplete("AUTO.WAV");
                  playComplete("MODE.WAV");
                  playComplete("ON.WAV");
                  camControl = false;
                  break;
                default:
                  playComplete("CAMERA.WAV");
                  playComplete("HUH.WAV");
            }// end switch(inCommand)
          }// end if(Serial.available)
        }// end while(camControl)
        break;
       default:
        playComplete("WIRELESS.WAV");
        playComplete("HUH.WAV");
    }//end switch(inCommand)
  }// end if(Serial.available)
}// end loop()

