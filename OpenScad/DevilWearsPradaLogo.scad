use </home/chinchillabot/chinchilla/OpenScad/Libs.scad>
use </home/test_engineer/chinchilla/OpenScad/Libs.scad>
use </Users/Carlitos/chinchilla/OpenScad/Libs.scad>

s = 35;
t = 5;
difference() {
	equilateralTriangle(s,t, true);
	equilateralTriangle(s-t,t, true);
}

translate([t,-s/4,0]) cube(size=[s/20,s/4,t], center=true);
translate([0,-s/4,0]) cube(size=[s/20,s/2,t], center=true);
translate([-t,-s/4,0]) cube(size=[s/20,s/4,t], center=true);