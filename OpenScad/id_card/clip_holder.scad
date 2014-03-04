wall_thickness = 1.5;
height_watch = 11;
height_cover = wall_thickness + height_watch;
radius_watch_glass = 36/2;
radius_cover_inner = radius_watch_glass + 5;
radius_cover_outer = radius_cover_inner + wall_thickness;

clasp_length = 12;
holder_height = 1;
holder_t = 2;
holders_cover_height = 6;
holders = 8; // holder pair thickness
holder_thickness = 5.2;

buttons_angle = 60;
buttons_height = wall_thickness + 6;
buttons_radius = 6/2;



RESOLUTION = 200;
$fn=RESOLUTION;


module frame(){
// Main Frame
difference() {
	union() {
// clip
		translate([0,-(radius_cover_outer/2-3),-height_watch/2-wall_thickness/2-1]) cube(size=[1.5*holders, radius_cover_outer, holder_t], center=true);
translate([0,-(radius_cover_outer-4),-height_watch/2-wall_thickness/2]) rotate(a=[0,90,0])	cylinder(h=1.5*holders, r = holder_t+1, center=true);

	// Cover face
	cylinder(h = height_watch, r1 = radius_cover_outer, r2 = radius_cover_outer, center = true);
}
	// Glass hole
	cylinder(h = height_watch+1, r1 = radius_watch_glass, r2 = radius_watch_glass, center = true);

	// Watch frame hole
 	cylinder(h = height_watch - 2*wall_thickness, r1 = radius_cover_inner, r2 = radius_cover_inner, center = true);

	// Main Frame clasp
	cylinder(h = height_watch+1, r1 = radius_cover_outer - clasp_length, r2 = radius_cover_outer-wall_thickness, center = true);

	// Main Frame slant
	translate([0,0,-(height_watch/2 - wall_thickness) -0.5]) cylinder(h = 1.2, r1 = radius_cover_outer - clasp_length, r2 = radius_cover_inner-1, center = true);

	// Wristband holder
		translate([0,radius_cover_outer+1,wall_thickness]) cube(size=[holders, radius_cover_outer+1, height_watch], center=true);

}
translate([0,2,-height_watch/2-wall_thickness/2-1]) rotate(a=[0,90,0])	cylinder(h=1.5*holders, r = holder_t/1.2, center=true);
}

frame();

