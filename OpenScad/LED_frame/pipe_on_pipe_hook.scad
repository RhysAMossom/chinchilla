
led_r = 41/2;
pipe_r = 55/2;
t = 4;
w = 10;
h = 120;

difference(){
	cylinder(h=w,r=led_r+t);
	cylinder(h=w,r=led_r);
}

translate([led_r+t/2,-w/2,0])
cube([h,w,w]);

translate([2*led_r+t/2+h,0,0])
difference(){
	cylinder(h=w,r=led_r+t);
	cylinder(h=w,r=led_r);
	translate([-(led_r+t),w/2,0])
	cube([led_r+t,led_r+t,w]);
}