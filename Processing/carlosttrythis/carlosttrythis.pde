import processing.serial.*;
Serial arduino;

int [] x;
int [] y;

void setup()
{
    size(600,600);
    rectMode(CENTER);
    frameRate(30);
    x= new int[600];
    y= new int[600];

    background(0); 
    for (int i = 0; i < 600; i++)
    {
        for(int j = 0; j < 600;j++)
        {
            stroke(floor(random(256)), floor(random(256)), floor(random(256)));
            point(i,j);
        }
    }
}

/*void draw()
{ 
    background(0); 
    for (int i = 0; i < 600; i++)
    {
        for(int j = 0; j < 600;j++)
        {
            stroke(floor(random(256)));
            point(i,j);
        }
    }
  
}*/
