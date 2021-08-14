#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<stdlib.h>

struct REGS i,o;
struct arccoordstype a1,a2;

getkey() {
i.h.ah=0;
int86(22,&i,&o);
return(o.h.ah);
}

void main() {
int gd=DETECT,gm;
initgraph(&gd,&gm,"c:\\turboc3\\bgi");
int key,i;
int midx=320,midy=240;
int crcl1rad=100,crcl2rad=100;
int crcl1x=crcl1rad,crcl2x=crcl2rad;
//int breakpoint=midy-(2*crcl1rad*crcl2rad/(crcl1rad+crcl2rad));
int baseangle1=90;
int arcangle=0;
int line1x[5],line1y[5],line2x[5],line2y[5];
int lines=4;


while(1) {
if(kbhit()) {
  clearviewport();
  key=getkey();
  if(key==1) {
    closegraph();
    exit(0);
  }
  if(key==2) {
    crcl1x-=5;
    crcl2x-=5;
    arcangle-=2;
  }
  if(key==3) {
    crcl1x+=5;
    crcl2x+=5;
    arcangle+=2;
  }
}

setcolor(15);
line(0,240,640,240);
line(320,0,320,480);

circle(midx-crcl1x,240,crcl1rad);
arc(midx-crcl1x,midy,0,baseangle1-arcangle,crcl1rad);
getarccoords(&a1);
line(midx,midy-100-100+crcl1x,a1.xend,a1.yend);
line(midx,2*midy-(midy-100-100+crcl1x),a1.xend,2*midy-a1.yend);
for(i=0;i<lines;i++) {
  line1x[i]=(midx)+(i+1)*(a1.xend-midx)/(lines+1);
  line1y[i]=(midy-200+crcl1x)+(i+1)*(a1.yend-(midy-200+crcl1x))/(lines+1);
}

circle(midx+crcl2x,240,crcl2rad);
arc(midx+crcl2x,midy,baseangle1+arcangle,180,crcl2rad);
getarccoords(&a2);
line(midx,midy-100-100+crcl2x,a2.xstart,a2.ystart);
line(midx,2*midy-(midy-100-100+crcl2x),a2.xstart,2*midy-a2.ystart);
for(i=0;i<lines;i++) {
  line2x[i]=(midx)+(i+1)*(a2.xstart-midx)/(lines+1);
  line2y[i]=(midy-200+crcl2x)+(i+1)*(a2.ystart-(midy-200+crcl2x))/(lines+1);
}
//line(midx,midy-100-100+cirx,a2.xend,a2.yend);
//for(i=0;i<lines;i++) {
//  line2x[i]=(midx)+(i+1)*(a2.xend-midx)/(lines+1);
//  line2y[i]=(midy-200+cirx)+(i+1)*(a2.yend-(midy-200+cirx))/(lines+1);
//}


for(i=0;i<lines;i++) {
  line(line1x[i],line1y[i],line2x[lines-i-1],line2y[lines-i-1]);
  line(line1x[i],2*midy-line1y[i],line2x[lines-i-1],2*midy-line2y[lines-i-1]);
}


delay(20);
}
}