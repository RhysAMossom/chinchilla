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
wheel_screw_h = 10;
wheels_sep = 35;

wheel_base_w = 5 + wheel_screw_r;

endstop_sep = 10;
endstop_screw_r = 2.3/2+th;
endstop_h = 20;
endstop_d = t;
endstop_l = 21;
endstop_t = 6.5;

cover_enclosure = true;
cart_l = 130;
cart_w = 60;
cart_h = wheel_screw_h + wheels_sep + 2*wheel_screw_r + 2*t;

arduino_cover_h = 25;
arduino_screw_r = 1;
lcd_l = 72;
lcd_w = 26;
lcd_x = 13;
lcd_y = 7.5;
lcd_screw_r = 2.5;
lcd_screw_d = t;
buttons_x = [-5,-2,-8,-5,-7,-2];
buttons_y = [2,10,10,19,29,73];
num_buttons = 6;
button_r = 2.5;
button_h = 10;
usb_s = 13;
usb_x = 11.5;
usb_h = 4;
pwr_conn_s = 11;
pwr_conn_x = 43;
pwr_conn_h = 3;

pulley_h = 17;
pulley_screw_r = 4/2 + th;
pulley_screw_h = cart_h/2+2;
pulley_sep = 20;
pulley_positions_y = [10,35,cart_l-35,cart_l-10];

motor_r = 28/2;
motor_screw_r = 4/2+th;
motor_screw_sep = 35;
motor_screw_h = pulley_screw_h - 5;
motor_h = 20;
motor_spacing = 4;

nut_w = 11+th;
nut_h = 6+th;

camera_mount_r = 10/2+th;
camera_mount_h = cart_h+25;
camera_in_x = cart_w/2 + 3*camera_mount_r;
camera_in_y = 2*wheel_base_w + 2*t;

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
difference() {
cube([cart_w,cart_l,cart_h]);


if (cover_enclosure) {
translate([t,t,t])
cube([cart_w - 2*t,cart_l - 2*t,cart_h ]);


for (y = [0,cart_l-t]){
// enstop oppening
translate([cart_w/2-endstop_screw_r-2*t,y,endstop_h+t])
cube([endstop_l,2*t,endstop_t]);
// belt openning
translate([t,y,t+5])
cube([pulley_h,t,cart_h-10-t]);

}

} else {
translate([t,t+2*wheel_base_w,t])
cube([cart_w-t,cart_l - 2*t-4*wheel_base_w,cart_h - t]);
translate([t,0,t])
cube([cart_w - 2*t,cart_l,cart_h - t]);
}

// Wheel holders
for( z = [0,wheels_sep]){
for( y = [wheel_base_w ,cart_l-wheel_base_w]) {
translate([0,y, z + t+ wheel_screw_h])
rotate(a=[0,90,0])
cylinder(h=cart_w, r=wheel_screw_r);
}
}

// pulley holders;
for(y = pulley_positions_y){
translate([0,y, pulley_screw_h])
rotate(a=[0,90,0])
cylinder(h=pulley_h+2*t, r=pulley_screw_r);
}
}

// Internal wall pulley holders
difference() {
translate([pulley_h+t,0,0])
cube([t,cart_l,pulley_screw_h + 2*pulley_screw_r]);
for(y = pulley_positions_y){
translate([0,y, pulley_screw_h])
rotate(a=[0,90,0])
cylinder(h=pulley_h+2*t, r=pulley_screw_r);
}
for(y = [0,motor_screw_sep]){
translate([0,t+(cart_l-motor_screw_sep)/2 +y, motor_screw_h])
rotate(a=[0,90,0])
cylinder(h=pulley_h+2*t, r=pulley_screw_r);
}
// Motor Mount holes
translate([t,(cart_l-motor_screw_sep)/2+3*t + motor_screw_r, motor_screw_h/2])
cube([pulley_h+2*t, 2*(motor_r-t), 2*motor_r]);



}

// Motor Mount cube
translate([pulley_h+motor_h/2+t,(cart_l-motor_screw_sep)/2+3*t + motor_screw_r, t])
cube([motor_h, 2*(motor_r-t), motor_spacing]);

// enstop mounts
for( x = [cart_w/2,cart_w/2+endstop_sep]){
for( y = [t+endstop_d,cart_l-t -endstop_d]) {
translate([x,y,t])
difference() {
cylinder(r=endstop_screw_r+t,h=endstop_h);
cylinder(r=endstop_screw_r,h=endstop_h);
}
}
}

// Camera mount
translate([camera_in_x,camera_in_y,t])
difference(){
cylinder(h=camera_mount_h,r=camera_mount_r+2*t);
cylinder(h=camera_mount_h,r=camera_mount_r);
}

}

module arduino_cover() {
difference() {
cube([cart_w,cart_l+2*t,arduino_cover_h+t]);
translate([t,t,0])
cube([cart_w - 2*t,cart_l - t,arduino_cover_h]);

// LCD screen
translate([lcd_x,lcd_y,arduino_cover_h])
cube([lcd_w,lcd_l,t]);

// board holder
for(x = [lcd_x-lcd_screw_d,lcd_x+lcd_w+lcd_screw_d]){
translate([x,lcd_y-lcd_screw_d,arduino_cover_h])
cylinder(h=t,r=lcd_screw_r);
}

// buttons
for (i= [0:num_buttons-1]){
translate([cart_w -2*t + buttons_x[i],2*t+button_r/2+buttons_y[i],arduino_cover_h])
cylinder(h=t,r=button_r);
}

// Camera holder
translate([ cart_w - camera_in_x,2*t + cart_l-camera_in_y,arduino_cover_h])
cylinder(h=t,r=camera_mount_r+2*t+th);

// Power and USB connectors
translate([usb_x,0,usb_h])
cube([usb_s,t,usb_s]);
translate([pwr_conn_x,0,pwr_conn_h])
cube([pwr_conn_s,t,pwr_conn_s]);
}

// arduino screw
arduino_screw_y = t + 98;
arduino_screw_x = cart_w - 2*t - lcd_screw_r;
translate([arduino_screw_x,arduino_screw_y,t])
difference() {
cylinder(h=arduino_cover_h-t,r=arduino_screw_r+t);
cylinder(h=arduino_cover_h-t,r=arduino_screw_r);
}

// tabs
/*for(x=[t-th,cart_w-2*t+th]){
translate([x,cart_l/2-2*t,-3*t])
cube([t,4*t,4*t]);
}*/
}

module buttons() {
cylinder(h=t,r=button_r+2*th);
cylinder(h=button_h,r=button_r-th);
}

//arduino_cover();

buttons();

//cart();

//wheel();

//main_mount();

//translate([w/2,t+screw_mount_l,screw_mount_h*2.1])
//screw_mount();

//translate([0,0,-5*t])
//belt_gripper();
