#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<stdlib.h>
struct REGS i,o;
getkey()
{
i.h.ah=0;
int86(22,&i,&o);
return(o.h.ah);
}

initmouse()
{
i.x.ax=0;
int86(0x33,&i,&o);
return(o.x.ax);
}

showmouseptr()
{
i.x.ax=1;
int86(0x33,&i,&o);
}

hidemouseptr()
{
i.x.ax=2;
int86(0x33,&i,&o);
}

getmousepos(int *button,int *x,int *y)
{
i.x.ax=3;
int86(0x33,&i,&o);
*button=o.x.bx;
*x=o.x.cx;
*y=o.x.dx;
}

main()
{
int gd=DETECT,gm;
initgraph(&gd,&gm,"c:\\turboc3\\bgi");
int button,x,y,key;
while(1)
{
   if(kbhit())
   {
   key=getkey();
   if(key==1)
   {
   closegraph();
   exit(0);
   }
   }
showmouseptr();
  setcolor(15);
  line(0,400,600,400);

static xb1=50,yb1=50; /*initial value of red bar*/
static xb2=200,yb2=50;
getmousepos(&button,&x,&y);

/* data for red bar */
  setfillstyle(SOLID_FILL,0);   /*hide backwors red bar*/
  bar(xb1-50,yb1-50-3,xb1+50,yb1+50);
if(button==1&&x>xb1-50&&x<xb1+50&&y>yb1-50&&y<yb1+50) /*if click in red bar*/
{
  if(xb1<xb2-100|xb1>xb2+100|yb1<yb2-100|yb1>yb2+100) /*if red bar is outside of green bar*/
  xb1=x,yb1=y;  /*red bar track to mouse pos*/
  if(xb1>=xb2-100&&xb1<xb2&&  yb1>yb2-100&&yb1<yb2+100) /*if red bar go in green bar from left*/
  {
  xb1=xb2-101; /*then red bar throw from green bar to backward or right*/
  setfillstyle(SOLID_FILL,0);
  bar(xb2-50,yb2-50,xb2+50,yb2+50);
  xb2+=1;
  }
  if(xb1<=xb2+100&&xb1>xb2&&  yb1>yb2-100&&yb1<yb2+100) /*if red bar go in green bar from fight*/
  {
  xb1=xb2+101; /*then red bar throw from green bar to backward or left*/
  setfillstyle(SOLID_FILL,0);
  bar(xb2-50,yb2-50,xb2+50,yb2+50);
  xb2-=1;
  }

  if(yb1>=yb2-100&&yb1<yb2&&  xb1>xb2-100&&xb1<xb2+100) /*if red bar go in green bar from top*/
  yb1=yb2-101; /*then red bar throw from green bar to backward or to top*/
}
  setfillstyle(SOLID_FILL,4);  /*draw red bar on mouse pos*/
  bar(xb1-50,yb1-50,xb1+50,yb1+50);
/* if(yb1<350) */
if((xb1<xb2-100|xb1>xb2+100|yb1<yb2-105|yb1>yb2+100)&&yb1<350)
yb1+=3;    /*if red bar is outside to green bar then it is fall*/


  setfillstyle(SOLID_FILL,0);
  bar(xb2-50,yb2-50-3,xb2+50,yb2+50);
if(button==1&&x>xb2-50&&x<xb2+50&&y>yb2-50&&y<yb2+50)
{
  if(xb2<xb1-100|xb2>xb1+100|yb2<yb1-100|yb2>yb1+100)
  xb2=x,yb2=y;
  if(xb2>=xb1-100&&xb2<xb1&&  yb2>yb1-100&&yb2<yb1+100)
  {
  xb2=xb1-101;
  setfillstyle(SOLID_FILL,0);
  bar(xb1-50,yb1-50,xb1+50,yb1+50);
  xb1+=1;
  }
  if(xb2<=xb1+100&&xb2>xb1&&  yb2>yb1-100&&yb2<yb1+100)
  {
  xb2=xb1+101;
  setfillstyle(SOLID_FILL,0);
  bar(xb1-50,yb1-50,xb1+50,yb1+50);
  xb1-=1;
  }

  if(yb2>=yb1-100&&yb2<yb1&&  xb2>xb1-100&&xb2<xb1+100)
  yb2=yb1-101;
}
  setfillstyle(SOLID_FILL,2);
  bar(xb2-50,yb2-50,xb2+50,yb2+50);
/* if(yb2<350) */
if((xb2<xb1-100|xb2>xb1+100|yb2<yb1-105|yb2>yb1+100)&&yb2<350)
yb2+=3;


delay(10);
}
getch();
}