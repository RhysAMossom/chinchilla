import processing.video.*;

MovieMaker mm;  // Declare MovieMaker object

void setup() {
  size(320, 240);
  // Create MovieMaker object with size, filename,
  // compression codec and quality, framerate
  mm = new MovieMaker(this, width, height, "drawing.mov",
                       30, MovieMaker.H263, MovieMaker.HIGH);
  background(204);
}

void draw() {
  ellipse(mouseX, mouseY, 20, 20);
  mm.addFrame();  // Add window's pixels to movie
}

void keyPressed() {
  if (key == ' ') {
    mm.finish();  // Finish the movie if space bar is pressed!
  }
}
