import processing.video.*;
Capture videoIN;
MovieMaker videoOUT;
int hVideoIN = 480,wVideoIN = 640,spacer = 15,x,y,photoCounter = 0,videoCounter = 0;
PImage rightA,leftA,upA,downA,camButton,recButON,recButOFF,saveArea;
boolean recording = false, firstRec = false;


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
   
  println(Capture.list());
  videoIN = new Capture(this,wVideoIN,hVideoIN,Capture.list()[4],64);
  saveArea = createImage(wVideoIN,hVideoIN,RGB);
  
}

boolean inButton(int x,int y, int originX,int originY,int widthX,int heightY)
{
  if(x> originX && x <(originX + widthX) && y> originY && y<(originY + heightY)) return true;
  return false;
}

void captureEvent(Capture videoIN)
{
  videoIN.read();
}
void mousePressed()
{
    x = mouseX;
    y = mouseY;
    if(inButton(x,y,videoIN.width-3*spacer,5*spacer,4*spacer, videoIN.height - 8*spacer))
    { println("Move Right");}
    else if(inButton(x,y,spacer,5*spacer,4*spacer, videoIN.height - 8*spacer)){
      println("camLeft");}
    else if(inButton(x,y,5*spacer,spacer,videoIN.width - 8*spacer, 4*spacer)){
      println("camUp");}
    else if(inButton(x,y,5*spacer,videoIN.height-3*spacer,videoIN.width - 8*spacer, 4*spacer)){
      println("camDown");}
    else if(inButton(x,y,2*spacer,height - 3*spacer-recButOFF.height/2,recButOFF.width,recButOFF.height)){
      recording = !recording;
      if(recording){
        println("Recording...");
        videoOUT = new MovieMaker(this,width,height,"video "+ nf(videoCounter++,3)+".mov",8,MovieMaker.H263, MovieMaker.BEST);
        firstRec = true;
      }}
     
    else if(inButton(x,y,10*spacer,height - 3*spacer-camButton.height/2,camButton.width,camButton.height)){
      image(videoIN,spacer,spacer);
      saveArea.set(0,0,get(spacer,spacer,videoIN.width,videoIN.height));
      saveArea.save("snapshot "+ nf(photoCounter++,3)+".jpg");
      println("Snapshot saved in sketchbook folder as 'snapshot "+ nf(photoCounter-1,3)+".jpg'");  }
}

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
}
