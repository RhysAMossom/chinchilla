use </home/chinchillabot/chinchilla/OpenScad/cc_library.scad>
use </home/test_engineer/chinchilla/OpenScad/cc_library.scad>
use </Users/Carlitos/chinchilla/OpenScad/cc_library.scad>

l = 40;
w = 40;
h = 15;

difference(){
	// main cube

	//translate([0,0,1])
	 round_corner_square(l,w,h,2);

	for (x = [2.5:5:l]){
		for (y = [2.5:5:w]){
			translate([x,y,0])
				//cylinder(r=1.6, h = 10);
				led_3mm();
		}
	}

}