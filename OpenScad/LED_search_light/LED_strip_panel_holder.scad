use </home/chinchillabot/chinchilla/OpenScad/cc_library.scad>
use </home/test_engineer/chinchilla/OpenScad/cc_library.scad>
use </Users/Carlitos/chinchilla/OpenScad/cc_library.scad>

d=20;
w=40;
h=75;

panel_d = 15;
panel_h = 50;

screw_r = 2.5;
screw_head_r = screw_r + 1;

// Gargola
difference(){
	translate([0,13,20]) import("/home/chinchillabot/chinchilla/OpenScad/Gargola/dragon.stl");
	cube(size=[50,w,h]);
}

// Back pannel
difference(){
//main board
	cube(size=[d,w,h]);

	// panel extrusion
	translate([0,0,(h-panel_h)/2]) cube(size=[panel_d,w,panel_h]);

	//screw holes
	// head	
	translate([0,w/2,(h-(h-panel_h)/4)]) rotate(a=[0,90,0]) cylinder(h=d/2, r=screw_head_r);
	translate([0,w/2,(h-(h-panel_h)/4)]) rotate(a=[0,90,0]) cylinder(h=d, r=screw_r);
}


