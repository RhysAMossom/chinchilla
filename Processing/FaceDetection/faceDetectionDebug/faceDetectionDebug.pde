import hypermedia.video.*;
import java.awt.Rectangle;

OpenCV opencv;

void setup() {
    size( 640, 480 );

    opencv = new OpenCV( this );
    opencv.capture( width, height );                   // open video stream
    opencv.cascade( OpenCV.CASCADE_FRONTALFACE_ALT );  // load detection description, here-> front face detection : "haarcascade_frontalface_alt.xml"
}

public void stop() {
    opencv.stop();
    super.stop();
}

void draw() {
    opencv.read(); // grab frame
    
//    opencv.convert( GRAY );

    // proceed detection
    Rectangle[] faces = opencv.detect( 1.2, 2, OpenCV.HAAR_DO_CANNY_PRUNING, 40, 40 );

    // display the image
    image( opencv.image(), 0, 0 );
    
    // display boundaries
    noFill();
    stroke(100,250,0);
    rect(width/4, height/3, 2*width/4, height/3);

    // draw face area(s)
    noFill();
    stroke(0,0,255);
    for( int i=0; i<faces.length; i++ ) {
        rect( faces[i].x, faces[i].y, faces[i].width, faces[i].height );
        
        // center of face
        noFill();
        stroke(10,10,0);
        ellipse(faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2, 2, 2);

        
        
        // Print Coordinates and Location of faces
        //println("x = " + faces[i].x + "\ty = " + faces[i].y);
        
        // Find Location of Faces
        // Horizontally
        if (faces[i].x + faces[i].width/2 < width/4) { 
          println("right");
        }
        else if (faces[i].x + faces[i].width/2 > 3*width/4){
          println("left");
        }
        else { 
          println("Centered Horizontally");
        }
        delay(100);
        
        // Vertically
        if (faces[i].y + faces[i].height/2 < height/3){
          println("up");
        }
        else if(faces[i].y + faces[i].height/2 > 2*height/3){
        println("down");
        }
        else {
          println("Centered Vertically");
        }
        delay(100);
    }
}
