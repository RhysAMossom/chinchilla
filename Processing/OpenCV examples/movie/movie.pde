import hypermedia.video.*;

OpenCV opencv;

boolean remember = false;

void setup() {

  size( 640, 480 );

  opencv = new OpenCV( this );
  opencv.movie( "bunny.avi", width, height );

  println( "Click inside sketch window to change movie timecode" );
  println( "Press space bar to record background image" );
  
}

void draw() {

  opencv.read();
  if ( remember ) opencv.absDiff();
  //sopencv.threshold( 200 );

  image( opencv.image(), 0, 0 );
}

void keyPressed() {
  opencv.remember();
  remember = true;
}

void mousePressed() {
  float time = mouseX/float(width);
  opencv.jump( time );
}
