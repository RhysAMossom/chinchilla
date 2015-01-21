$fn = 80;
w = 25;
h = 100;
t = 15;
l = 20;
screw_r = 6/2;
candle_r = 25;
hook_r = 30;


module candle_holder(){
	difference(){
		cylinder(r= candle_r + t/2, h = 2*t);
		translate([0,0,t])
		cylinder(r= candle_r, h =t);
	}
}

module hook(){
	difference(){
		cube([t,w,h]);
		translate([0,w/2,h/2+2*screw_r])
		rotate(a=[0,90,0])
		cylinder(r=screw_r,h=t);
	}
	translate([hook_r,0,hook_r])
	rotate(a=[-90,0,0])
	difference(){
		cylinder(r=hook_r,h=w);
		cylinder(r=hook_r-t,h=w);
		translate([-hook_r,-hook_r,0])
		cube([2*hook_r,hook_r,w]);
	}
}

cube([hook_r,w,t]);
hook();
translate([0,0,h])
cube([l,w,2*t]);
translate([candle_r+l,candle_r/2,h])
candle_holder();