use </home/chinchillabot/chinchilla/OpenScad/cc_library.scad>
use </home/test_engineer/chinchilla/OpenScad/cc_library.scad>
use </Users/Carlitos/chinchilla/OpenScad/cc_library.scad>

$fn = 50;

// base
w = 20;
h = 50;
t = 3;

// strip
strip_t = 5;
strip_w = 13;

// holder
holder_l = w;
holder_t = 2*strip_t + t;
holder_w = 2/3*strip_w;
holder_r = 1;

// base
round_corner_square(w,h,t,2);

// holder shift
shift = 3/4*w;

// mounting holes
nail_r = 1;
screw_r = 2;

// holder-clip
difference(){
	translate([0,shift,holder_t])
		rotate(a=[0,90,0]) 
			round_corner_square(holder_t,holder_l,holder_l,2);
	//strip extrusion
	translate([-0.5,shift,t])
	cube(size=[holder_l+1,strip_w + 2*holder_r,strip_t]);
}
// clip
translate([0,shift+holder_r,t+strip_t])
	rotate(a=[0,90,0])
		cylinder(r=holder_r, h=w);
