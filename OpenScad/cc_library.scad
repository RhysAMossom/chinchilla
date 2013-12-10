// Carlos Chinchilla - Openscan object library

$fn = 50;

module round_corner_square(b, w, h,r){
	z = h;
	x = b;
	y = w;
	union(){
		// rectangles
		translate([0,r,0])	cube(size=[x,y-2*r,z]);
		translate([r,0,0])	cube(size=[x-2*r,y,z]);

		// corners
		translate([x-r,y-r,0])	cylinder(r=r, h=z);
		translate([x-r,r,0])	cylinder(r=r, h=z);
		translate([r,y-r,0])	cylinder(r=r, h=z);
		translate([r,r,0])	cylinder(r=r, h=z);
	}
}

module round_corner_cube(x, y, z,r){

	union(){
		// rectangles
		translate([0,r,r])	cube(size=[x,y-2*r,z-2*r]);
		translate([r,0,r])	cube(size=[x-2*r,y,z-2*r]);
		translate([r,r,0])	cube(size=[x-2*r,y-2*r,z]);

		// corners
		translate([x-r,y-r,r])	sphere(r=r);
		translate([x-r,r,r])	sphere(r=r);
		translate([r,y-r,r])	sphere(r=r, h=z);
		translate([r,r,r])	sphere(r=r);
		translate([x-r,y-r,z-r])	sphere(r=r);
		translate([x-r,r,z-r])	sphere(r=r);
		translate([r,y-r,z-r])	sphere(r=r, h=z);
		translate([r,r,z-r])	sphere(r=r);
		
		// edges
		translate([x-r,y-r,r])	cylinder(r=r,h=z-2*r);
		translate([x-r,r,r])	cylinder(r=r,h=z-2*r);
		translate([r,y-r,r])	cylinder(r=r,h=z-2*r);
		translate([r,r,r])	cylinder(r=r,h=z-2*r);
		translate([r,y-r,r])	rotate(a=[0,90,0]) cylinder(r=r,h=x-2*r);
		translate([r,r,r])	rotate(a=[0,90,0]) cylinder(r=r,h=x-2*r);
		translate([r,y-r,z-r])	rotate(a=[0,90,0]) cylinder(r=r,h=x-2*r);
		translate([r,r,z-r])	rotate(a=[0,90,0]) cylinder(r=r,h=x-2*r);
		translate([r,r,z-r])	rotate(a=[-90,0,0]) cylinder(r=r,h=y-2*r);
		translate([x-r,r,z-r])	rotate(a=[-90,0,0]) cylinder(r=r,h=y-2*r);
		translate([r,r,r])	rotate(a=[-90,0,0]) cylinder(r=r,h=y-2*r);
		translate([x-r,r,r])	rotate(a=[-90,0,0]) cylinder(r=r,h=y-2*r);
	}
}

module led(r,h){
	h = h -r;
	translate([0,0,h])
	rotate(a=[180,0,0])
	difference(){
		union(){
			sphere(r=r);
			cylinder(r=r,h=h);
			translate([0,0,h-1]) cylinder(r=r+0.5,h=1);
		}
		translate([r,-r,-r]) cube(size=[0.5,2*r,h+r]);
	}
}

module led_5mm(){
	led(5/2,8.6);
}

module led_3mm(){
	led(3/2,4.5+0.8);
}
