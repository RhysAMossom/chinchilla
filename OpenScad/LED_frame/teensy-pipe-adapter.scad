$fn = 100;
r = 20;
t = 2;
l = 15;
b = 46;
w = 26;

difference(){
cylinder(r=r+t,h=l+t);
cylinder(r=r,h=l);
}

translate([-(b+2*t)/2,-(w+2*t)/2,l+t])
difference(){
cube([b+2*t,w+2*t,2*l+t]);
translate([t,t,t])
cube([b,w,2*l]);
}