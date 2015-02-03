
$fn=60;
h = 35;
r_s = 16/2;
r_b = 23/2;
r_m = 30/2;
t = 5;

cylinder(h=t,r=r_b);
translate([0,0,t])
cylinder(h=h,r1=r_s,r2=r_b);

translate([0,h/2,t+h+r_m])
rotate(a=[90,0,0])
difference(){
	cylinder(h=h,r=r_m+t);
	cylinder(h=h,r=r_m);
	translate([-2*t,r_m-t,0])
	cube([4*t,r_m,h]);
}