$fn=50;
r_out = 35.8/2;
r_in = 9/2;
h = 30;

difference(){
	cylinder(r=r_out,h=h);	
	cylinder(r=r_in,h=h);
	cube([r_out,r_out,h]);
}