// Fan adapter for tube

$fn = 50;


module square_adapter(){
	t = 1;

	// Side vent
	d = 3;
	l = 15;
	h = 12.5;
	w = 17.55;

	// Tube holders
	r = 2.6;
	strain_relief_h = 8;
	difference(){
		union(){
		translate([w/2,l/2+r,-strain_relief_h+t+1])
			cylinder(h=strain_relief_h, r=r+2*t);
			cube([w,l,h]);
		}
		translate([w/2,l/2+r,-strain_relief_h+t+1])
		cylinder(h=strain_relief_h, r=r);

		translate([t,0,t])
			cube([w-2*t,l-t,h-2*t]);
	}
}

module triangular_adapter(){
	t = 1;
	in = 5;
	s1 = 12.5;
	s2 = 17.55;
	piramid_h = 25;
	r_out = 5.0/2;
	r_in = r_out -t;
	hose_h = piramid_h + 10;

	difference(){
		cube([s1,s2,in]);
		translate([t,t,0,])
		cube([s1 - 2*t,s2 - 2*t,in]);
	}
	translate([s1/2,s2/2,in])
	difference(){
		union(){
		polyhedron(
			points=[[s1/2,s2/2,0],[s1/2,-s2/2,0],[-s1/2,-s2/2,0],
					[-s1/2,s2/2,0],[0,0,piramid_h]],
			triangles=[[0,1,4],[1,2,4],[2,3,4],[3,0,4],[1,0,3],[2,1,3]]
		);
		cylinder(r=r_out,h=hose_h);
		}
		translate([0,0,-t])
		polyhedron(
			points=[[s1/2,s2/2,0],[s1/2,-s2/2,0],[-s1/2,-s2/2,0],
					[-s1/2,s2/2,0],[0,0,piramid_h]],
			triangles=[[0,1,4],[1,2,4],[2,3,4],[3,0,4],[1,0,3],[2,1,3]]
		);

		cylinder(r=r_in,h=hose_h);
	}

}

triangular_adapter();