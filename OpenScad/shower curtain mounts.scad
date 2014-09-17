$fn=70;

screw_r = 5.3/2;
screw_d = 38/2; // Distance from center
mount_t = 4;
mount_r = 26;
hanger_r = mount_r/2;
hanger_h = 110;

translate([0,0,mount_t])
cylinder(r=hanger_r,h=hanger_h);
difference(){
	cylinder(r=mount_r,h=mount_t);
	for(x=[-screw_d,screw_d]){
		translate([x,0,0])
		cylinder(r=screw_r,h=mount_t);
	}
}
