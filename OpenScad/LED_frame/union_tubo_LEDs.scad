$fn = 100;
r_in = 25.6*(2.5-0.25)/2;
r_out = 38/2;
l = 20;
t = 1;

module union_pipe() {
difference(){
	cylinder(h=l,r=r_in);
	cylinder(h=l,r=r_in-t);
}
}

module tapadera(led_holes=false) {
in = 4;
r_in = 31/2;
r_led= 5.5/2;
x = 16;
y = x*sin(60);
height = 40;
difference(){
  union() {
	translate([0,0,in])
	if (!led_holes){
		cylinder(h=2*t,r=r_out);
	} else {
		cylinder(h=40,r=r_out);
	}
	cylinder(h=in,r=r_in);
  }

  if (led_holes) {
	cylinder(h=in+2*t,r=r_led);
	translate([0,0,2*t+in])
	cylinder(h=height-(2*t),r=r_out-2*t);

	translate([0,y/2+t,0])
	cylinder(h=in+2*t,r=r_led);
	translate([-x/2+t,-y/2+2*t,0])
	cylinder(h=in+2*t,r=r_led);
	translate([x/2-t,-y/2+2*t,0])
	cylinder(h=in+2*t,r=r_led);

  } else {
  cylinder(h=in,r=r_in-t);
  }
}
}

tapadera(true);

