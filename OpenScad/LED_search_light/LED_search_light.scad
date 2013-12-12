use </home/chinchillabot/chinchilla/OpenScad/cc_library.scad>

l = 40;
w = 40;
h = 15;

difference(){
	// main cube

	translate([0,0,1]) round_corner_square(l,w,h,2);
	
	for (x = [2.5:5:l]){
			translate([x,2.5,0])
				led_3mm();
	}		
	for (x = [2.5:5:35]){
			translate([x,7.5,0])
				led_3mm();
	}	


}