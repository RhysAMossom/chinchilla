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
