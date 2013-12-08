import processing.video.*;
Capture myCapture;

void setup()
{
  size(800,600);
  smooth();
  println(Capture.list());
  myCapture = new Capture(this,640,480,Capture.list()[1],30);
}

void captureEvent(Capture myCapture)
{
  myCapture.read();
}

void draw() {
  image(myCapture,0,0);
  fill(200);
  ellipse(mouseX,mouseY,80,80);
  fill(200,100,30);
  noStroke();
  rect(100,100,50,50);

}
