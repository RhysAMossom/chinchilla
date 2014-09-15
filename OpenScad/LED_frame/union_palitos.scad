module union_dos_palitos(){
	r = 7/2;
	h = 60;
	t = 2;
	$fn=70;
	difference(){
		cylinder(h=h,r=t+r);
		cylinder(h=h,r=r);
	}
}

module colgador_palo(){
	r = 8.2/2;
	h = 20;
	t = 2;
	$fn=70;
	difference(){
		cylinder(h=h+t,r=t+r);
		cylinder(h=h,r=r);
	}
	translate([-t,0,h+t+r])
	rotate(a=[0,90,0])
	difference(){
		cylinder(h=2*t,r=t+r);
		cylinder(h=2*t,r=r);
	}
}

module strip_hook(){
	r = 7/2;
	h = 5;
	t = 2;
	w = 5;
	l = 15;
	$fn=70;
	difference(){
		cylinder(h=h,r=t+r);
		cylinder(h=h,r=r);
		translate([-t,0,0])
		cube([r+2*t,r+t,h]);
	}
	translate([r+t,-l/2,0])
	difference(){
		translate([-t,0,0])
		cube([w+2*t,l+t,h]);
		cube([w,l,h]);
	}

}

module cross(){
	r = 7/2;
	h = 10;
	t = 2;
	$fn=70;
	difference(){
		cylinder(h=h,r=t+r);
		cylinder(h=h,r=r);
		translate([-t,0,0])
		cube([r+2*t,r+t,h]);
	}
	r = 8.2/2;
	h = 20;
	t = 2;
	rotate(a=[90,0,50])
	translate([-2*r-t,h/2,-h/2])
	difference(){
		cylinder(h=h,r=t+r);
		cylinder(h=h,r=r);
		rotate(a=[0,0,45])
		translate([-t-r,0,0])
		cube([r+2*t,r+t,h]);
	}

}
//union_dos_palitos();
//colgador_palo();
strip_hook();
//cross();