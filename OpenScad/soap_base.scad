h = 120;
w = 80;
l = 80;
t = 3;
leg_b = 10;
stomp_h = 50;
stomp_b = leg_b;

// Top Base
translate([0,0,h])
cube([w,l,t]);

// Legs
cube([leg_b,leg_b,h]);
translate([w-leg_b,0,0])
cube([leg_b,leg_b,h]);
translate([0,l-leg_b,0])
cube([leg_b,leg_b,h]);

// Stomp
translate([0,0,h+t])
cube([stomp_b,stomp_b,stomp_h]);