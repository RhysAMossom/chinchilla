$fn = 100;
r_in = 25.6*(2.5-0.25)/2;
l = 20;
t = 1;

difference(){
	cylinder(h=l,r=r_in);
	cylinder(h=l,r=r_in-t);
}