h = 100;
w = 200;
t = 10;
pants_h = 50;

leg_h = 100;
leg_t = 30;
shoe_l = 50;

difference(){
	cube([w+2*t,pants_h,h+2*t]);
	translate([t,-t,t])
	cube([w,pants_h,h]);
}
translate([(w+2*t)/4,pants_h,0])
cube([leg_t,leg_h,h+2*t]);
translate([t,leg_h+2*t,0])
cube([shoe_l,leg_t,h+2*t]);

translate([3*(w+2*t)/4-leg_t,pants_h,0])
cube([leg_t,leg_h,h+2*t]);
translate([3*(w+2*t)/4-t,leg_h+2*t,0])
cube([shoe_l,leg_t,h+2*t]);