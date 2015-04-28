h = 120;
w = 80;
l = 110;
t = 3;
leg_b = 10;
stomp_h = 20;
stomp_b = leg_b;
hook_h = 15;
hook_in = 10;

// Top Base
translate([0,0,h])
difference(){
	cube([w,l,t]);
	translate([leg_b,leg_b,0])
	cube([w-2*leg_b,l-2*leg_b,t]);
}

// Legs
cube([leg_b,leg_b,h]);
translate([w-leg_b,0,0])
cube([leg_b,leg_b,h]);
translate([0,l-leg_b,0])
cube([leg_b,leg_b,h]);

// Stomp
translate([w-leg_b,0,h+t])
cube([stomp_b,stomp_b,stomp_h]);

// Hook
module hook() {
	cube([leg_b, leg_b, hook_h + t]);
	translate([0,0,hook_h])
	cube([leg_b, leg_b + hook_in, t]);
	translate([0,leg_b + hook_in -t, hook_h - t])                 
	cube([leg_b, t, t]);
}
translate([w-leg_b,0,h+t])
hook();
translate([(w-leg_b)/2,0,h+t])
hook();
translate([0,l,h+t])
rotate(a=[0,0,-90])
hook();
