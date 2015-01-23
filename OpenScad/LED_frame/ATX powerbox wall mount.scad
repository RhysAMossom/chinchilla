$fn = 100;
b = 150;
h = 85;
w = 25;
t = 4;
l = 30;
r = 2;


module screw_attachment(){
difference(){
	cube([l,t,w]);
	translate([l/2,-0.1,w/2])
	rotate(a=[-90,0,0])
	cylinder(h=t+0.2,r=r);
}
}

difference(){
cube([b+t,h+t,w]);
translate([0,t,0])
cube([b,h,w]);
}

translate([b+t,h,0])
screw_attachment();
rotate(a=[0,0,-90])
screw_attachment();