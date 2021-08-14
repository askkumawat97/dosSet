#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<stdlib.h>
int hr_box=60,vr_box=20;//resolution
int col[20][60];
main()
{
int gd=DETECT,gm;
initgraph(&gd,&gm,"c:\\turboc3\\bgi");
START:
int key;
struct REGS i,o;
i.h.ah=0;
i.x.ax=0;
int x=0,y=0,r=1;
int button,x1,y1;
int xd,yd;
int rx,ry;
int hr,vr;
int background=9;
int fillstyle=7;
int color=0;
int exit1=0;
int find_box_x,find_box_y;
while(1)
{
COLOR_WINDOW:
if(kbhit())
 {
 int86(22,&i,&o);
 key=o.h.ah;
 }
if(key==1)
 {closegraph(),exit(0);}
if(key==28)
 {clearviewport(),x=0,y=0,r=1,key=0;}
i.x.ax=3;
rx=x1;
ry=y1;
int86(0x33,&i,&o);
button=o.x.bx;
x1=o.x.cx;
y1=o.x.dx;

if(button==1)
 {
 if(x1>590&&x1<640&&y1<20){exit1=1;}
 if(x1>535&&x1<590&&y1<20)
  {
  }
 if(x1>480&&x1<535&&y1<20)
  {
  fillstyle++;
  if(fillstyle==12)fillstyle=0;
  }
 }
if(x1>30)
 {
 i.x.ax=2;
 int86(0x33,&i,&o);
 setcolor(background+1);
 line(x1-5,y1,x1+5,y1);
 line(x1,y1-5,x1,y1+5);
 putpixel(x1,y1,background);
 }
if(x1<30)
 {
 i.x.ax=1;
 int86(0x33,&i,&o);
 if(button==1)
  {color=y1/30;}
 if(button==2)
  {background=y1/30;}
 for(int k=0;k<16;k++)
  {
  setfillstyle(1,k);
  bar(5,k*30+5,25,k*30+25);
  setcolor(15);
  rectangle(4,k*30+5-1,26,k*30+25+1);
  }
 goto COLOR_WINDOW;
 }
if(x1>480&&y1<20)
 {
 setfillstyle(1,12);
 bar(590,0,640,20);
 setcolor(4);
 outtextxy(600,7,"EXIT");
 if(x1>590)
  {
  rectangle(590+1,0+1,640-1,20-1);
  rectangle(590+2,0+2,640-2,20-2);
  rectangle(590+3,0+3,640-3,20-3);
  }
 setfillstyle(1,13);
 bar(535,0,590-1,20);
 setcolor(5);
 outtextxy(543,7,"CLEAR");
 if(x1<590&&x1>535)
  {
  rectangle(535+1,0+1,590-2,20-1);
  rectangle(535+2,0+2,590-3,20-2);
  rectangle(535+3,0+3,590-4,20-3);
  }
 setfillstyle(1,10);
 bar(480,0,535-1,20);
 setcolor(2);
 outtextxy(490,7,"BG_PT");
 if(x1<535)
  {
  rectangle(480+1,0+1,535-2,20-1);
  rectangle(480+2,0+2,535-3,20-2);
  rectangle(480+3,0+3,535-4,20-3);
  }
 delay(10);
 goto COLOR_WINDOW;
 }

if(button==1)
 {
 if(x1>x&&x1<x+r*hr*10&&y1>y&&y1<y+r*vr*10)
  {
  find_box_x=(x1-x)/(r*10);
  find_box_y=(y1-y)/(r*10);
  col[find_box_y][find_box_x]=color;
  }
 }
if(button==2&&key==30)
 {
 if(x1!=rx);//clearviewport();
 if(x1-rx<0&&r>1) r--;
 if(x1-rx>0&&r<47) r++;
 }
if(button==2&&key==31)
 {
 if(x1!=rx);//clearviewport();
 if(y1!=ry);//clearviewport();
 x=x1+xd;
 y=y1+yd;
 }
xd=x-x1;
yd=y-y1;

for(hr=0;hr<hr_box;hr++)
{
int xa=x+hr*r*10;
for(vr=0;vr<vr_box;vr++)
{
int ya=y+vr*r*10;
setfillstyle(1,7);
bar(xa,ya,xa+r-1,ya+r-1);
setfillstyle(1,8);
bar(xa+r,ya,xa+r*10-1,ya+r-1);
setfillstyle(1,8);
bar(xa,ya+r,xa+r-1,ya+r*10-1);
setfillstyle(1,col[vr][hr]);
bar(xa+r,ya+r,xa+r*10-1,ya+r*10-1);
}
}
setfillstyle(fillstyle,background);
bar(-1,-1,641,y-1);
bar(-1,-1,x-1,481);
bar(-1,y+r*vr*10,641,481);
bar(x+r*hr*10,-1,641,481);

}
}