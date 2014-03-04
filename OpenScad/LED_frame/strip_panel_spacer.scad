use </home/chinchillabot/chinchilla/OpenScad/cc_library.scad>
use </home/test_engineer/chinchilla/OpenScad/cc_library.scad>
use </Users/Carlitos/chinchilla/OpenScad/cc_library.scad>

$fn = 50;

// base
w = 10;
t = 1.5;

// strip
strip_t = 5;
strip_w = 15;

// holder
holder_l = 15;
holder_t = 2*strip_t;
holder_w = 10;
holder_h = 22;
holder_r = 1;

// holder-clip
difference(){
	round_corner_square(holder_w,holder_l,holder_h,t);

	//strip extrusion
	translate([0,t,t])
	cube(size=[holder_l+1,strip_w + 2*holder_r,strip_t]);
}
// clip
translate([holder_t/4,holder_l-holder_r,strip_t+t])
	rotate(a=[0,90,0])
		cylinder(r=holder_r, h=holder_t/2);
