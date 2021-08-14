#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<stdlib.h>
#include<math.h>

struct REGS i,o;
struct arccoordstype arc1,arc2;

getkey() {
i.h.ah=0;
int86(22,&i,&o);
return(o.h.ah);
}

void main() {
int gd=DETECT,gm;
initgraph(&gd,&gm,"c:\\turboc3\\bgi");
int key;
//int crcl1x=320,crcl1y=240,crcl2x=520,crcl2y=240;
int crcl1x=320,crcl1y=240,crcl2x=490,crcl2y=240;
int crcl1rad=100,crcl2rad=50;
int arc1end=90,arc2end=90;
int breakpointx=100,breakpointy=100;
int breakdist=crcl1rad+crcl2rad;



while(1) {
if(kbhit()) {
  clearviewport();
  key=getkey();
  if(key==1) {
    closegraph();
    exit(0);
  }
  if(key==75) {
    crcl2x-=5;
  }
  if(key==77) {
    crcl2x+=5;
  }
  if(key==72) {
    crcl2y-=5;
  }
  if(key==80) {
    crcl2y+=5;
  }
}



long int tempr=(long int)(crcl2y-crcl1y)*(long int)(crcl2y-crcl1y)+(long int)(crcl2x-crcl1x)*(long int)(crcl2x-crcl1x);
long int templ1=sqrt(tempr);
int templ=(int) templ1;
int tempx=((crcl2x-crcl1x)*(templ+crcl1rad-crcl2rad))/(2*templ);
int tempy=((crcl2y-crcl1y)*(templ-crcl1rad-crcl2rad))/(2*templ);
breakpointx=crcl1x+tempx;
breakpointy=tempy;
line(breakpointx,0,breakpointx,480);
line(0,breakpointy,640,breakpointy);


line(crcl1x,crcl1y,crcl2x,crcl2y);

circle(crcl1x,crcl1y,crcl1rad);
arc(crcl1x,crcl1y,0,arc1end,crcl1rad);
getarccoords(&arc1);

circle(crcl2x,crcl2y,crcl2rad);
arc(crcl2x,crcl2y,0,arc2end,crcl2rad);
getarccoords(&arc2);



delay(20);
}
}