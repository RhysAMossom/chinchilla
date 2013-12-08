// Visuals
import processing.video.*;
Capture videoIN;
MovieMaker videoOUT;
int hVideoIN = 480,wVideoIN = 640,spacer = 15,x,y,photoCounter = 0,videoCounter = 0;
PImage rightA,leftA,upA,downA,camButton,recButON,recButOFF,saveArea;
boolean recording = false, firstRec = false;

//To control Arduino
import processing.serial.*;
Serial arduino;
String portName;
String outString = "";   // the string being sent out the serial port
String inString = "";    // the string coming in from the serial port
int receivedLines = 0;   // how many lines have been received
int bufferedLines = 10;  // number of incoming lines to keep

// Define Message Commands
String AUTONOMOUS = 'a';
String WIRELESS = 'w';
String LEFT = 'l';
String RIGHT = 'r';
String STOP = 's';
String BACK = 'b';
String FRONT = 'f';
String CALIBRATE = 'c';

void setup()
{
  size(wVideoIN + 2*spacer,hVideoIN + 7*spacer);
  smooth();
  background(255, 204, 0);
  
  //Load Arrows and other images
  rightA = loadImage("rightA.png");
  leftA = loadImage("leftA.png");
  upA = loadImage("upA.png");
  downA = loadImage("downA.png");
  camButton = loadImage("cameraButton.png");
  recButON = loadImage("recON.png");
  recButOFF = loadImage("recOFF.png");
   
  // println(Capture.list());
  videoIN = new Capture(this,wVideoIN,hVideoIN,Capture.list()[2],64);
  saveArea = createImage(wVideoIN,hVideoIN,RGB);
  
  //println(Serial.list());
  portName = Serial.list()[2];
  arduino = new Serial(this,portName,9600);
}// end setup()

boolean inButton(int x,int y, int originX,int originY,int widthX,int heightY)
{
  if(x> originX && x <(originX + widthX) && y> originY && y<(originY + heightY)) return true;
  return false;
}// end inButton()

// Events
void captureEvent(Capture videoIN)
{
  videoIN.read();
}// end captureEvent()

void serialEvent(Serial arduino) {
  // read the next byte from the serial port:
  int inByte = arduino.read();
  // add it to  inString:
  inString += char(inByte);
  if (inByte == '\r') {
    // if the byte is a carriage return, print
    // a newline and carriage return:
    inString += '\n';
    // count the number of newlines:
    receivedLines++;
    // if there are more than 10 lines, delete the first one:
    if (receivedLines >  bufferedLines) {
      deleteFirstLine();
    }
  }
}// end SerialEvent

void deleteFirstLine() {// deletes the top line of inString so that it all fits on the screen:
  // find the first newline:
  int firstChar = inString.indexOf('\n');
  // delete it:
  inString= inString.substring(firstChar+1);
}


// Keys and Mouse listeners

void keyPressed() {
  switch (key) {
  case '\n':
    arduino.write(outString + "\r");
    outString = "";
    break;
  case 8:    // backspace
    // delete the last character in the string:
    outString = outString.substring(0, outString.length() -1);
    break;
  case '+':  // we have to send the + signs even without a return:
    arduino.write(key);
    // add the key to the end of the string:
    outString += key;
    break;
  case 65535:  // If the user types the shift key, don't type anything:
    break;
    // any other key typed, add it to outString:
  default:
    // add the key to the end of the string:
    outString += key;
    break;
  }
}// end keyPressed()

void mousePressed()
{
    x = mouseX;
    y = mouseY;
    if(inButton(x,y,videoIN.width-3*spacer,5*spacer,4*spacer, videoIN.height - 8*spacer))
    { println("Move Right");
      arduino.write(RIGHT);}
    else if(inButton(x,y,spacer,5*spacer,4*spacer, videoIN.height - 8*spacer)){
      println("camLeft");
      arduino.write(LEFT);}
    else if(inButton(x,y,5*spacer,spacer,videoIN.width - 8*spacer, 4*spacer)){
      println("camUp");
      arduino.write(FRONT);}
    else if(inButton(x,y,5*spacer,videoIN.height-3*spacer,videoIN.width - 8*spacer, 4*spacer)){
      println("camDown");
      arduino.write(BACK);}
    else if(inButton(x,y,2*spacer,height - 3*spacer-recButOFF.height/2,recButOFF.width,recButOFF.height)){
      recording = !recording;
      if(recording){
        println("Recording...");
        arduino.write(STOP);
        videoOUT = new MovieMaker(this,width,height,"video "+ nf(videoCounter++,3)+".mov",8,MovieMaker.H263, MovieMaker.BEST);
        firstRec = true;
      }}
     
    else if(inButton(x,y,10*spacer,height - 3*spacer-camButton.height/2,camButton.width,camButton.height)){
      image(videoIN,spacer,spacer);
      saveArea.set(0,0,get(spacer,spacer,videoIN.width,videoIN.height));
      saveArea.save("snapshot "+ nf(photoCounter++,3)+".jpg");
      println("Snapshot saved in sketchbook folder as 'snapshot "+ nf(photoCounter-1,3)+".jpg'");  }
   else arduino.write(STOP);
}// end mousePressed()

void draw()
{
  //Arrows
  image(videoIN,spacer,spacer);
  image(rightA,width-4*spacer,spacer + hVideoIN/2- rightA.height/2);
  image(leftA,4*spacer - leftA.width,spacer+hVideoIN/2 - rightA.height/2);
  image(upA, width/2 -upA.width/2,3*spacer);
  image(downA,width/2 - downA.width/2, hVideoIN -4*spacer + downA.height);
  
  //Rectangles
  noFill();
  rect(videoIN.width-3*spacer,5*spacer,4*spacer, videoIN.height - 8*spacer);//Right
  rect(spacer,5*spacer,4*spacer, videoIN.height - 8*spacer);//Left
  rect(5*spacer,spacer,videoIN.width - 8*spacer, 4*spacer);//Up
  rect(5*spacer,videoIN.height-3*spacer,videoIN.width - 8*spacer, 4*spacer);//Down
  
  //Buttons and Recording Code
  if(recording) {
    image(recButON,2*spacer, height - 3*spacer-recButON.height/2);
    videoOUT.addFrame();
  }
  else{
    image(recButOFF,2*spacer, height - 3*spacer-recButOFF.height/2);
    if(firstRec){
     videoOUT.finish();
     firstRec = false;
     println("Done recording.\n\t Video saved in sketchbook folder as: 'video "+nf(videoCounter-1,3)+".mov'");
    }   
  }
  image(camButton,10*spacer,height - 3*spacer-camButton.height/2); 
  
  // Serial Terminal
  text("Serial port: " + portName, spacer + wVideoIN, hVideoIN + 1*spacer);
  text("typed: " + outString, spacer + wVideoIN, hVideoIN + 2*spacer);
  text("received:\n" + inString, spacer + wVideoIN, hVideoIN + 3*spacer);   
}// end draw()
