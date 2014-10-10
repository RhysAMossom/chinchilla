l = 110;
w = 65;
h = 120;
screw_r = 7.05/2;
screw_r_in=2.5/2;
t = 3.2;
$fn=60;

difference(){
	cube([l,w,h]);
	translate([t,t,0])
	cube([l-2*t,w-2*t,h-t]);
}

for(x = [t+screw_r,l-t-screw_r]){
	for(y = [t+screw_r,w-t-screw_r]){
	translate([x,y,0])
	difference(){
		cylinder(h=h-t,r=screw_r);
		cylinder(h=h/2,r=screw_r_in);

		}
	}
}