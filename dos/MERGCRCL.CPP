#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>
#include<stdlib.h>

struct REGS i,o;
struct arccoordstype a1,a2,a3,a4;

getkey() {
i.h.ah=0;
int86(22,&i,&o);
return(o.h.ah);
}

exit() {
int key;
if(kbhit()) {
  key=getkey();
  if(key==1) {
    closegraph();
    exit(0);
  }
}
return(0);
}

void main() {
int gd=DETECT,gm;
initgraph(&gd,&gm,"c:\\turboc3\\bgi");
int key;
int a1start=0,a1end=180;
int startx[20],starty[20],endx[20],endy[20];
int i;
int lines=4;


while(1) {
//exit();
if(kbhit()) {
  clearviewport();
  key=getkey();
  if(key==1) {
    closegraph();
    exit(0);
  }
  if(key==2&&a1start<80) {
  a1start++;
  a1end--;
  }
  if(key==3&&a1start>30) {
  a1start--;
  a1end++;
  }
  if(key==4) lines--;
  if(key==5) lines++;
}

line(0,240,640,240);
circle((320+50)+(80-a1start)*2,240,50);

for(i=0;i<lines;i++) {
  setcolor(0);
  arc(320,240,a1start,a1end,(i+1)*(200/lines));
  getarccoords(&a1);
  startx[i]=a1.xstart;
  starty[i]=a1.ystart;
  endx[i]=a1.xend;
  endy[i]=a1.yend;
}
for(i=0;i<lines;i++) {
  setcolor(15);
  line(endx[i],endy[i],startx[lines-i-1],starty[lines-i-1]);
  line(320,240,startx[lines-1],starty[lines-1]);
  line(320,240,endx[lines-1],endy[lines-1]);
}


delay(20);
}
}