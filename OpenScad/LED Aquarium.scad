w = 71;
l = 40;
into = 10;
t = 5;

difference(){
	cube([w+2*t,l,l]);
	translate([0,t+into,t+into])
	cube([w+2*t,l,l]);
	translate([t,t,t])
	cube([w,l,l]);

}