module frame() {
t = 2;
h = 40;
l = 250;
w = 20;

difference() {
cube(size=[w,l,h]);
translate([0,0,t]) cube(size=[w-1.5*t,l,h-2*t]);
}
}

module strip_holder() {
	t = 0.7;
	h = 13;
	l = 280;
	w = 20;
	tab_l = 15;
	screw_holder_r = 2.5;
	screw_holder_l = 3*screw_holder_r;
	screw_holder_t = 5;

	difference() {
		cube(size=[w,l,h]);
		translate([t,0,t]) cube(size=[w-2*t,l,h-2*t]);
		// outer tabs that hold wires
		for(y = [0:2*tab_l:l]){
			translate([0,y,t]) cube(size=[t,tab_l,h-2*t]);
		}
	}
	// Inner tabs that hold strip
	for(y = [10:2*tab_l:l-tab_l]){
		translate([w-t-5,y,t]) cube(size=[t,tab_l,h-2*t]);
	}
	
	// Screw holes
	for(y = [15:l/3:l-screw_holder_l]){
		translate([0,y,h])
			difference(){
				cube(size=[screw_holder_t,screw_holder_l,screw_holder_l]);
				translate([0,screw_holder_l/2,screw_holder_l/2])
					rotate(a=[0,90,0])	cylinder(r=screw_holder_l/3, h=screw_holder_t);
			}
		translate([0,y+l/6,-screw_holder_l])
			difference(){
				cube(size=[screw_holder_t,screw_holder_l,screw_holder_l]);
				translate([0,screw_holder_l/2,screw_holder_l/2])
					rotate(a=[0,90,0])	cylinder(r=screw_holder_l/3, h=screw_holder_t);
			}
		
	}
}

strip_holder();

