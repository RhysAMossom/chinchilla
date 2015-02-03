mirror_t = 12;
mirror_s = 30;
cube_s = 14.5;

t = 4;

difference(){
	cube([cube_s+2*t,cube_s+2*t,cube_s+t]);
	translate([t,t,0])
	cube([cube_s,cube_s,cube_s]);
}

translate([cube_s+t,cube_s+t,0])
difference(){
	cube([mirror_s+2*t,mirror_s+2*t,cube_s+t]);
	translate([t,t,cube_s-mirror_t])
	cube([mirror_s+t,mirror_s+t,mirror_t]);
	translate([4*t,4*t,0])
	cube([mirror_s-t,mirror_s-t,cube_s+t]);
}