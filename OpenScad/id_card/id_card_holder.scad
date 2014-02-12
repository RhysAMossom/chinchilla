RESOLUTION = 200;
$fn=RESOLUTION;


id_h = 86;
id_l = 56.5;
id_t = 1.5;

frame_w = 5;
corner_r = frame_w/3;

holder_h = id_h+4;
holder_l = id_l+4;
holder_t = id_t + 3;

clip_h = 10;
clip_l = 20;
clip_t = (holder_t-id_t)/2;

clip_hole_h = clip_h/3+1;
clip_hole_l = clip_l-6;
clip_hole_t = id_t;

slide_h = id_h/2;
slide_l = clip_l;

pin_h = 3;
pin_r = id_t/3;


module rectangle_round_corners(h,l,t,corner_r) {


	module fillet(r, h) {
	    translate([r / 2, r / 2, 0])

	        difference() {
   	         cube([r + 0.01, r + 0.01, h], center = true);
	
   	         translate([r/2, r/2, 0])
   	             cylinder(r = r, h = h + 1, center = true);
	
   	     }
	}



difference() {
	cube(size=[t,l,h]);


	rotate(a=[-t/2,-90,0]) fillet(corner_r,2*t);

	translate([t/2,l,0]) rotate(a=[90,0,-90]) fillet(corner_r,2*t);
	translate([t/2,0,h]) rotate(a=[90,90,90])	fillet(corner_r,2*t);
	translate([t/2,l,h]) rotate(a=[90,180,90]) fillet(corner_r,2*t);
}
}

difference() {
//holder
rectangle_round_corners(h=holder_h,l=holder_l,t=holder_t,corner_r=corner_r);

//id frame
translate([holder_t/2,(holder_l-id_l+(2*frame_w))/2,(holder_h-id_h+(2*frame_w))/2]) 
rectangle_round_corners(h=id_h-(2*frame_w),l=id_l-(2*frame_w),t=holder_t,corner_r=corner_r);

//thumb slide hole
translate([0,(holder_l-slide_l)/2,(holder_h-slide_h)/2]) 
rectangle_round_corners(h=slide_h,l=slide_l,t=holder_t,corner_r=corner_r);

//id frame
translate([holder_t/2,(holder_l-id_l+(2*frame_w))/2,(holder_h-id_h+(2*frame_w))/2]) 
rectangle_round_corners(h=id_h-(2*frame_w),l=id_l-(2*frame_w),t=holder_t,corner_r=corner_r);

//id
translate([(holder_t-id_t)/2,(holder_l-id_l)/2,(holder_h-id_h)/2]) 
rectangle_round_corners(h=holder_h,l=id_l,t=id_t,corner_r=corner_r);

}

// Clip Holder
translate([0,(holder_l-clip_l)/2,holder_h-corner_r])
difference() {
	rectangle_round_corners(h=clip_h,l=clip_l,t=clip_t,corner_r=corner_r);
	translate([0,(clip_l-clip_hole_l)/2,(clip_h-clip_hole_h)/2 -1])
	rectangle_round_corners(h=clip_hole_h,l=clip_hole_l,t=clip_t+2,corner_r=corner_r);
}


// pins
translate([holder_t-id_t,pin_h+2*(holder_l-id_l),holder_h-pin_r]) rotate(a=[90,0,0]) cylinder(h=pin_h, r=pin_r);

translate([holder_t-id_t,id_l+pin_h-2*(holder_l-id_l),holder_h-pin_r]) rotate(a=[90,0,0]) cylinder(h=pin_h, r=pin_r);