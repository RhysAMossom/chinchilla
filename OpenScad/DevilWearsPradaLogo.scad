use </home/chinchillabot/chinchilla/OpenScad/Libs.scad>
use </home/test_engineer/chinchilla/OpenScad/Libs.scad>
use </Users/Carlitos/chinchilla/OpenScad/Libs.scad>

use </home/chinchillabot/chinchilla/OpenScad/cc_library.scad>
use </home/test_engineer/chinchilla/OpenScad/cc_library.scad>
use </Users/Carlitos/chinchilla/OpenScad/cc_library.scad>

s = 35;
t = 5;
$fn = 50;
module DevilWearsPreadaLogo(s,t){
difference() {
	equilateralTriangle(s,t, true);
	equilateralTriangle(s-t,t, true);
}

translate([t,-s/4,0]) cube(size=[s/20,s/4,t], center=true);
translate([0,-s/4,0]) cube(size=[s/20,s/2,t], center=true);
translate([-t,-s/4,0]) cube(size=[s/20,s/4,t], center=true);
}

// On square
//translate([-(5/8)*s,-(5/8)*s,-t/2]) round_corner_square((5/4)*s,(5/4)*s,t/2, t/2);
//DevilWearsPreadaLogo(s,t);

// Necklace
difference(){
	DevilWearsPreadaLogo(s,t);
	translate([0,-s/2+s/15,0])
	rotate(a=[0,90,0])
	cylinder(h=s/20,r=2, center=true);
}