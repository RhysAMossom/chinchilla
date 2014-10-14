$fn = 80;
r1 = 4.5/2;
r2 = 5.5/2;
t = 1;
h = 10;

difference(){
union(){
	cylinder(r1=r1,r2=r2,h=h);
	translate([0,0,h]){
	cylinder(r2=r1,r1=r2,h=h);
	rotate(a=[0,90,0])
	cylinder(r2=r1,r1=r2,h=h);
	}
}
	translate([0,0,h]){
	cylinder(r2=r1-t,r1=r2-t,h=h);
	rotate(a=[0,90,0])
	cylinder(r2=r1-t,r1=r2-t,h=h);
	}
	cylinder(r1=r1-t,r2=r2-t,h=h);
}
