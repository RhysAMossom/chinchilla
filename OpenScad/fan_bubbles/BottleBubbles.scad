$fn = 80;

strip_t = 4;
strip_w = 12;
strip_l = 62;

in = 10;
t = 5;
h = in + strip_t + t;

module dual_bottle(bottle){

	bottle_r = 37;
	d = 56;
	strip_holder_h = 250;
	strip_holder_w = 35;
	
	motor_r = 26.5/2; 
	motor_h = 35;
	motor_z = 180;
	if (bottle) {
		difference(){
			union(){
				translate([d,0,0])
				cylinder(h=h,r=bottle_r+t);
				cylinder(h=h,r=bottle_r+t);
				translate([0,bottle_r/2,0])
				cube([d,bottle_r,h-in]);
			}
			translate([0,0,h-in]){
				translate([d,0,0])
				cylinder(h=in,r=bottle_r);
				cylinder(h=in,r=bottle_r);
			}
			translate([d/2-(1/2)*strip_w,-bottle_r/2,h-in-strip_t])
			cube([strip_w,strip_l,strip_t+in]);

			translate([(d-strip_holder_w)/2,(3/2)*bottle_r-2*t,0])
			cube([strip_holder_w,t,h-in]);

			translate([0,-bottle_r,h-in])
			cube([d,2*bottle_r,in]);
		}
	}
	else { //strip holder
		cube([strip_holder_w,strip_holder_h,t]);
		translate([-t,h-in,0])
		cube([strip_holder_w+2*t,t,2*t]);
		
		translate([motor_r+t,motor_z,motor_r+1.5*t])
		rotate(a=[-90,0,0])
		difference(){
			cylinder(r=motor_r+t, h=motor_h);
			cylinder(r=motor_r, h=motor_h);
			translate([-t,-(motor_r+t),0])
			cube([2*t,2*t,motor_h]);
		}
	}
}

module square_bottle(base){
	w = 122;
	l = 111;//back to front
	out = 80;
	tapon_r = 24/2;
	tapon_h = 25 + 2*t;
	hose_r = 3.3;

	if (base){
		difference(){
			translate([0,-out,0])
			cube([w+2*t,l+2*t+out,h]);
			translate([t,t,h-in])
			cube([w,l,in]);
		
			translate([0,-out,h-in])
			cube([w+2*t,out,in]);
		
			for (x = [l/3-strip_w/2:2.5*strip_w:l+t-strip_w]){
				translate([x,0,h-in-strip_t])
				cube([strip_w,l+t,strip_t+in]);
			}
		}
	}
	else { // tapon
		difference(){
			union(){
				cylinder(r=tapon_r+t,h=2*t);
				cylinder(r=tapon_r,h=tapon_h);
			}
			cylinder(r=hose_r,h=tapon_h);
		}
	}
}

//square_bottle(false);
//dual_bottle(false);

cube([strip_w,260,10]);