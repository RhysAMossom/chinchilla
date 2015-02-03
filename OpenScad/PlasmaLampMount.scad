t = 2;
r = 100/2;
h = 21;
screw_r = 2;
$fn = 80;

difference(){
	cylinder(h=h+2*t,r=r+t);
	translate([0,0,t])
	cylinder(h=h,r=r);
	cylinder(h=h+2*t,r=r-3*screw_r);
	for(y = [r+t-2*screw_r,-(r+t-2*screw_r)]) {
		translate([0,y,0])
		cylinder(h=h+2*t,r=screw_r);
	}
	translate([-(r+t),0,t])
	cube([2*(r+t),r+t,h+2*t]);
	translate([-5*t,-(r+t),t])
	cube([10*t,r+t,h+2*t]);
}