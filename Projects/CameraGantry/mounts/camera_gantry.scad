th = 0.2;
r_sm = 10/2+th;
r_lg = 15/2+th;
t = 2;
hole_sep = 60;

screw_r = 5/2 + th;
screw_mount_l = 10;
screw_mount_h = 15;

nut_w = 11+th;
nut_h = 4+th;

l = 100;
h = 2*(r_lg+t);
w = 2*(screw_r+2*t);

$fn = 60;

module main_mount() {
difference() {
union() {
cube([w, l, h]);
translate([0,l-screw_mount_l,h]){
cube([w,screw_mount_l,screw_mount_h]);
translate([w/2,0,screw_mount_h])
rotate(a=[-90,0,0])
cylinder(r=w/2,h=screw_mount_l);
}

translate([0,0,h]) {
cube([w,screw_mount_l,screw_mount_h]);
translate([w/2,0,screw_mount_h])
rotate(a=[-90,0,0])
cylinder(r=w/2,h=screw_mount_l);
}
}

translate([w/2,l-screw_mount_l,h+screw_mount_h-t])
rotate(a=[-90,0,0])
cylinder(r=screw_r,h=screw_mount_l);

translate([w/2,0,h+screw_mount_h-t])
rotate(a=[-90,0,0])
cylinder(r=screw_r,h=screw_mount_l);

// Hole for small end of stick
translate([0,(l-hole_sep)/2,r_sm + (h-(2*r_sm))/2])
rotate(a=[0,90,0])
cylinder(r=r_sm, h=w-t);

// Hole for large end of stick
translate([0,(l-hole_sep)/2+hole_sep,r_lg + (h-(2*r_lg))/2])
rotate(a=[0,90,0])
cylinder(r=r_lg, h=w-t);

// Holes for screws
translate([w/2-t,(l-hole_sep)/2,0])
cylinder(r=screw_r,h=h);
translate([w/2-t,(l-hole_sep)/2+hole_sep,0])
cylinder(r=screw_r,h=h);
}
}

module screw_mount() {
difference() {
union() {
translate([-nut_w/2-t,(l-2*(t+screw_mount_l)-nut_w-2*t)/2,0])
cube([nut_w+2*t,nut_w+2*t,nut_h+w/4+t]);
rotate(a=[-90,0,0])
cylinder(h=l-2*(t+screw_mount_l),r=w/2);
}
translate([-nut_w/2-t,(l-2*(t+screw_mount_l)-nut_w)/2,w/2-t]){
cube([nut_w,nut_w,nut_h]);
translate([w/4+t,t+w/4,t])
cylinder(h=nut_h,r=screw_r);
}
rotate(a=[-90,0,0])
cylinder(h=l-2*(t+screw_mount_l),r=screw_r);
}
}

module belt_gripper() {
difference() {
translate([0,screw_mount_l,0])
cube([w-2*t,l-2*screw_mount_l,2*t]);
// Holes for screws
translate([w/2-t,(l-hole_sep)/2,0])
cylinder(r=screw_r,h=h);
translate([w/2-t,(l-hole_sep)/2+hole_sep,0])
cylinder(r=screw_r,h=h);
}
}

//main_mount();

//translate([w/2,t+screw_mount_l,screw_mount_h*2.1])
//screw_mount();

//translate([0,0,-5*t])
belt_gripper();
