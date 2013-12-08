  PGraphics savearea;
  void setup() {
     size(500,500);
   savearea = createGraphics(width/2,height/2,JAVA2D);
 }

void draw() {
  background(255);
  fill(0);
 noStroke();
   rect(0,0,width/2,height/2);
   rect(width/2,height/2,width/2,height/2);
   noFill();
    stroke(255,0,0);
   rect(mouseX,mouseY,width/2,height/2);
 }


 void mousePressed() {
 savearea.set(0,0,get(mouseX,mouseY,width/2,height/2));
   savearea.save("SavedArea-" + nf(frameCount,4) + ".png");
 }
