// Fan adapter for tube

$fn = 50;
t = 1;

// Side vent
d = 3;
l = 15;
h = 12.5;
w = 17.55;

// Tube holders
r = 2.6;
strain_relief_h = 8;

difference(){
	union(){
	translate([w/2,l/2+r,-strain_relief_h+t+1])
		cylinder(h=strain_relief_h, r=r+2*t);
		cube([w,l,h]);
	}
	translate([w/2,l/2+r,-strain_relief_h+t+1])
	cylinder(h=strain_relief_h, r=r);

	translate([t,0,t])
		cube([w-2*t,l-t,h-2*t]);
		
}