$fn=70;

screw_r = 5.3/2;
screw_d = 38/2; // Distance from center
mount_t = 4;
mount_r = 26;
hanger_r = mount_r/2;
hanger_h = 200;

hole_t = 15;

module mounts(){
	//translate([0,hanger_r,hanger_r])
	//rotate(a=[90,0,0])
	difference(){
		translate([0,0,mount_t])
		cylinder(r=hanger_r,h=hanger_h);
		translate([-mount_r,0,hanger_h-2*hole_t])
		cube([2*mount_r,mount_r,hole_t]);
	}
	difference(){
		cylinder(r=mount_r,h=mount_t);
		for(x=[-screw_d,screw_d]){
			translate([x,0,0])
			cylinder(r=screw_r,h=mount_t);
		}
	}
}

//mounts();

// accessories
a_h = 50;
a_e_h = 20;
a_r_t = hanger_r;
threshold = 1;
difference(){
	cylinder(r=mount_t+hanger_r,h=a_h);
	cylinder(r=hanger_r+threshold,h=a_e_h);
}

translate([0,-a_r_t,a_h + hanger_r])
rotate(a=[-90,0,0])
difference(){
	cylinder(r=mount_t+hanger_r,h=2*a_r_t);
	cylinder(r=hanger_r+threshold,h=2*a_r_t);
	translate([hanger_r/2,-hanger_r,0])
	cube([hanger_r,hanger_r,2*a_r_t]);
}