$fn = 60;

h = 15;
t = 2;
d = 0.3;
th = 0.2;
nail_r = t;
nail_h = 2*d + t;
camera_mount_r = 5;
r1 = camera_mount_r+t;
r2 = r1+d+t;
r3 = r2+d+t;
r4 = r3+d+t;

weight_mount_w = 30;
weight_mount_l = 60;

screw_r = 3;

module axis(r,h,nail_r=nail_r,nail_h=nail_h,nail_head =true){
 translate([0,-(r+nail_h),h])
 rotate(a=[-90,0,0]){
  cylinder(h=2*(r+nail_h),r=nail_r);
  if (nail_head){
   for(z=[-t,2*(r+nail_h)]){
    translate([0,0,z])
    cylinder(h=t,r=nail_r+t);
   }
  }
 }
}

// Camera Mount holder
difference(){
 union(){
 translate([0,0,-t-th])
  cylinder(h=t,r=r1+t);
  cylinder(h=h+t+th,r=r1);
  translate([-weight_mount_w/2,-screw_r-2*t,h+th])
  cube([weight_mount_w,weight_mount_l,t]);
 }
 cylinder(h=h+t+th,r=camera_mount_r);
 for(x=[-weight_mount_w/4+screw_r,weight_mount_w/4-screw_r]){
  translate([x,weight_mount_l/2])
  cylinder(h=r4+nail_h+4*t,r=screw_r); 
 }
}

// Rotation around Z-axis
difference() {
 union() {
  cylinder(h=h,r=r2);
  axis(r2,h/2);
 }
 cylinder(h=h,r=r1+d);
}

// Rotation around x-axis
difference() {
 union() {
  cylinder(h=h,r=r3);
  rotate(a=[0,0,90])
  axis(r3,h/2);
 }
 axis(r2,h/2,nail_r+th);
 cylinder(h=h,r=r2+d);
}

// Rotation around Y-axis
translate([-r4,-nail_r-t,0]){
 difference() {
  cube([2*r4,r4+nail_h+4*t,h]);

  translate([t,0,0])
  cube([2*(r4-t),r4+nail_h+2*t,h]);

  translate([r4,+nail_r+t,0])
  rotate(a=[0,0,90])
  axis(r3,h/2,nail_r+th);

  for(x=[-(r4-t)+screw_r,(r4-t)-screw_r]){
   translate([r4+x,+nail_r+t,h/2])
   rotate(a=[-90,0,0])
   cylinder(h=r4+nail_h+4*t,r=screw_r); 
  }
 }
}
