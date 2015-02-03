led_h = 13;
led_w = 20;
led_l = 96;

frame_w = 72;
frame_l = 401;
frame_h = 289;
frame_into = 10;
frame_gap = 38;
cushion = 5;
base_h = led_h + 2*cushion + frame_into;

module led(){
	cube([led_w,led_l,led_h]);
}

module bottom_frame(){
	difference(){
		cube([frame_w+2*cushion,cushion+frame_l/2,base_h]);
		translate([cushion,cushion,base_h-frame_into])
		cube([frame_w,frame_l/2,frame_into]);

		translate([(frame_w+2*cushion)/2+0.5*led_w,
			cushion+60,
			base_h-frame_into-led_h])
		led();
		translate([(frame_w+2*cushion)/2-1.5*led_w,
			cushion+60,
			base_h-frame_into-led_h])
		led();
	}
}

module side_frame(){
	difference(){
		cube([frame_w+2*cushion,frame_h-2*frame_into,base_h]);
		translate([cushion,0,base_h-frame_into])
		cube([frame_w,frame_h-2*frame_into,frame_into]);

		translate([(frame_w+2*cushion)/2+0.5*led_w,
			cushion+20,
			base_h-frame_into-led_h])
		led();
		translate([(frame_w+2*cushion)/2-1.5*led_w,
			cushion+20,
			base_h-frame_into-led_h])
		led();
		translate([(frame_w+2*cushion)/2+0.5*led_w,
			cushion+40 + led_l,
			base_h-frame_into-led_h])
		led();
		translate([(frame_w+2*cushion)/2-1.5*led_w,
			cushion+40 + led_l,
			base_h-frame_into-led_h])
		led();

	}
}

module top_frame(){
	difference(){
		cube([frame_w+2*cushion,cushion+frame_l/2,base_h]);
		translate([cushion,cushion,base_h-frame_into])
		cube([frame_w,frame_l/2,frame_into]);

		translate([(frame_w+2*cushion)/2+0.5*led_w,
			cushion+frame_l/2 - led_l,
			base_h-frame_into-led_h])
		led();
		translate([(frame_w+2*cushion)/2-1.5*led_w,
			cushion+frame_l/2 - led_l,
			base_h-frame_into-led_h])
		led();
	}
}

module gap(){
	difference(){
		cube([frame_w+2*cushion,frame_gap,base_h]);
		translate([cushion,0,base_h-frame_into])
		cube([frame_w,frame_gap,frame_into]);

		translate([(frame_w+2*cushion)/2+0.5*led_w,
			0,
			base_h-frame_into-led_h])
		led();
		translate([(frame_w+2*cushion)/2-1.5*led_w,
			0,
			base_h-frame_into-led_h])
		led();

	}
}


//bottom_frame();
//side_frame();
//top_frame();
gap();
