use </home/chinchillabot/chinchilla/OpenScad/Libs.scad>
use </home/test_engineer/chinchilla/OpenScad/Libs.scad>
use </Users/Carlitos/chinchilla/OpenScad/Libs.scad>

use </home/chinchillabot/chinchilla/OpenScad/cc_library.scad>
use </home/test_engineer/chinchilla/OpenScad/cc_library.scad>
use </Users/Carlitos/chinchilla/OpenScad/cc_library.scad>

s = 35;
t = 5;
difference() {
	equilateralTriangle(s,t, true);
	equilateralTriangle(s-t,t, true);
}

translate([t,-s/4,0]) cube(size=[s/20,s/4,t], center=true);
translate([0,-s/4,0]) cube(size=[s/20,s/2,t], center=true);
translate([-t,-s/4,0]) cube(size=[s/20,s/4,t], center=true);

translate([-(5/8)*s,-(5/8)*s,-t/2]) round_corner_square((5/4)*s,(5/4)*s,t/2, t/2);