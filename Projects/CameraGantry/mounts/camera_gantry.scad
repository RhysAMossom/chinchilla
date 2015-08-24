th = 0.2;
r_sm = 10/2+th;
r_lg = 16.2/2+th;
t = 2;
hole_sep = 100;

screw_r = 6.5/2 + th;
screw_mount_l = 10;
screw_mount_h = 15;

wheel_r = 10;
wheel_screw_r = 6/2+ th;
wheel_screw_h = 20;
wheels_sep = 35;
wheel_base_w = 5;
wheel_base_l = 4*t + 2*wheel_screw_r;
wheel_base_h = wheels_sep + wheel_screw_h + 2*t;

motor_s = 43;
motor_h = 39;
motor_screw_r = 3/2+th;
motor_screw_sep = 31;
motor_screw_h = 3.5;
motor_holder_h = motor_screw_h + 2*motor_screw_r+t;

endstop_w = 10;
endstop_l = 20;
endstop_h = wheel_base_h/2;

cart_l = 120;
cart_w = 65;//hole_sep - 2*(r_sm +r_lg) -2*t;

nut_w = 11+th;
nut_h = 6+th;

l = 120;
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
cylinder(h=hole_sep-2*t,r=(w+t)/2);
}
translate([-nut_w/2-t,(l-2*(t+screw_mount_l)-nut_w)/2,w/2-1.5*t]){
cube([nut_w,nut_w,nut_h]);
translate([w/4+t,t+w/4,2*t])
cylinder(h=nut_h,r=screw_r);
}
rotate(a=[-90,0,0])
cylinder(h=hole_sep-2*t,r=screw_r);
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

module wheel() {
difference() {
union() {
cylinder(h=2*t,r1=wheel_r+2*t,r2= wheel_r);
translate([0,0,2*t])
cylinder(h=r_lg,r=wheel_r);
translate([0,0,r_lg+2*t])
cylinder(h=2*t,r2=wheel_r+2*t,r1= wheel_r);
}
cylinder(h=4*t+r_lg,r=wheel_screw_r);
}
}

module cart() {
// cart base
cube([cart_w,cart_l,2*t]);
translate([0,0,2*t+wheel_base_h])
difference() {
cube([cart_w,cart_l,2*t]);
translate([10,10,0])
cube([cart_w-2*wheel_base_h,cart_l-2*wheel_base_l,2*t]);
}

// motor holder
translate([0,(cart_l-motor_s-2*t)/2,2*t]){
cube([motor_h,t,motor_holder_h]);
translate([0,motor_s+t,0])
cube([motor_h,t,motor_holder_h]);
translate([motor_h,0,0])
difference() {
cube([t,motor_s+2*t,motor_holder_h]);
for (y = [t,t+motor_screw_sep]){
translate([0,t+motor_screw_h+y,motor_screw_h])
rotate(a=[0,90,0])
cylinder(h=t, r=motor_screw_r);
}
}
}

// enstop mounts
for ( y = [0,cart_l-endstop_w]){
translate([motor_h-t-endstop_l,y,2*t])
difference() {
cube([endstop_l,endstop_w,endstop_h]);
translate([t,0,0])
cube([endstop_l-2*t,endstop_w,endstop_h-t]);
}
}

// Wheel holders
for (Y = [0,cart_l-wheel_base_l]) {
for (X = [0,cart_w-wheel_base_w]) {
translate([X,Y,2*t])
difference() {
cube([wheel_base_w, wheel_base_l, wheel_base_h]);
for ( y = [0,wheels_sep]) {
translate([0,wheel_base_w/2+wheel_screw_r+t/2,wheel_screw_h-wheel_screw_r+y])
rotate(a=[0,90,0])
cylinder(h=wheel_base_w, r=wheel_screw_r);
}
}
}
}
}

cart();

//wheel();

//main_mount();

//translate([w/2,t+screw_mount_l,screw_mount_h*2.1])
//screw_mount();

//translate([0,0,-5*t])
//belt_gripper();
