l = 145;
w = 90;
t = 2;
pants_h = 10;
leg_h = 150;
leg_t = 30;

difference(){
	cube([w + 2*t, l + 2*t, 2*pants_h]);
	translate([t,t,pants_h])
	cube([w, l, pants_h]);
}

for(y = [10+(1/3)*(l + 2*t)-leg_t,-10+(2/3)*(l + 2*t)]){
	translate([0,y,-leg_h])
	cube([w + 2*t,leg_t,leg_h]);
}

for(y = [10,-10+(2/3)*(l + 2*t) + (2/3)*leg_t]){
	translate([0,y,-leg_h])
	cube([w + 2*t,leg_t,leg_t]);
}