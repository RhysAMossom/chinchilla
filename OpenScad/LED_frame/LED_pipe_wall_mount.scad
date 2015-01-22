$fn = 100;

r_pipe = 36/2;

mount_base = 4* r_pipe;
mount_height = 2* r_pipe;
mount_width = 25;
mount_t = 5;

height_pipe = r_pipe+mount_t+mount_height/3;

screw_head_r = 3;
screw_r = 2;
screw_t = 3;
screw_in = 5+screw_head_r;

module triangle_sq(b,w,h){
polyhedron(
  points=[ [b,w,0],[b,0,0],[0,0,0],[0,w,0], // the four points at base
           [b/2,0,h],[b/2,w,h]  ], // the two apex points
  triangles=[ [0,1,4],[0,4,5], // two triangles for square side
				[4,3,5],[2,3,4], // two triangles for square side
             [1,0,3],[2,1,3], // two triangles for square base
				[4,1,2],[3,0,5]
	]
 );
}

difference(){
	// base and ring
	union(){
		triangle_sq(mount_base,mount_width,mount_height);
		translate([mount_base/2,-0.1,height_pipe])
		rotate(a=[-90,0,0])
		cylinder(h=mount_width+0.2,r=r_pipe+mount_t);
	}
	
	// extrusion pipe
	translate([mount_base/2,-0.1,height_pipe])
	rotate(a=[-90,0,0])	
	cylinder(h=mount_width+0.2,r=r_pipe);

	//Screw holes
	for (x = [screw_in,mount_base-screw_in]){
		translate([x,mount_width/2,screw_t])
		cylinder(h=mount_height,r=screw_head_r);
		translate([x,mount_width/2,0])
		cylinder(h=mount_height,r=screw_r);
	}	

}

