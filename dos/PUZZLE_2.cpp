#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>
#include<stdlib.h>
struct REGS i,o;
initmouse()
{
i.x.ax=0;
int86(0x33,&i,&o);
return(o.x.ax);
}

getkey()
{
i.h.ah=0;
int86(22,&i,&o);
return(o.h.ah);
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
*y=
o.x.dx;
}

restrictmouseptr(int x1,int x2,int y1,int y2)
{
i.x.ax=7;
i.x.cx=x1;
i.x.dx=x2;
int86(0x33,&i,&o);
i.x.ax=8;
i.x.cx=y1;
i.x.dx=y2;
int86(0x33,&i,&o);
}

draw_click()
{
int i,hor=310,ver=110;
setfillstyle(SOLID_FILL,7);
for(i=0;i<3;i++)
{
  bar(hor,70,hor+80,90);
  hor+=100;
}
for(i=0;i<3;i++)
{
  bar(270,ver,290,ver+80);
  ver+=100;
}
}

draw_hint()
{
int i,j,col=1;
for(i=50;i<=150;i+=50)
{
  for(j=50;j<=150;j+=50)
  {
  setfillstyle(SOLID_FILL,col);
  bar(j,i,j+50,i+50);
  col+=1;
  if(col==7)
  col=12;
  }
}
}

swap(int &x1,int &y1,int &x2,int &y2,int &x3,int &y3)
{
x1=x1+y1,y1=x1-y1,x1=x1-y1;
x2=x2+y2,y2=x2-y2,x2=x2-y2;
x3=x3+y3,y3=x3-y3,x3=x3-y3;
}

clear() //for colomn rectangle
{
setcolor(0);
rectangle(308,68,392,92);
rectangle(408,68,492,92);
rectangle(508,68,592,92);
}
clear1() //for row rectangle
{
setcolor(0);
rectangle(268,108,292,192);
rectangle(268,208,292,292);
rectangle(268,308,292,392);
}

draw_exit() /*draw exit button*/
{
setcolor(4);
rectangle(50,370,125,400);
setfillstyle(SOLID_FILL,4);
bar(53,373,122,397);
setcolor(0);
outtextxy(73,380,"EXIT");
}
restart() /*draw restart button*/
{
setcolor(2);
rectangle(125,370,200,400);
setfillstyle(SOLID_FILL,2);
bar(128,373,197,397);
setcolor(0);
outtextxy(135,380,"RESTART");
}
pause()  /*draw pause button*/
{
setcolor(14);
rectangle(50,330,200,360);
setfillstyle(SOLID_FILL,14);
bar(53,333,197,357);
setcolor(0);
outtextxy(105,340,"PAUSE");
}
draw_pause() //draw pause window if click on pause button
{
setcolor(13);
rectangle(204,174,436,236);
rectangle(207,177,433,233);
setfillstyle(SOLID_FILL,13);
bar(210,180,430,230);
}
clear_pause() //clear pause window if press enter to back
{
setcolor(0);
rectangle(204,174,436,236);
rectangle(207,177,433,233);
setfillstyle(SOLID_FILL,0);
bar(210,180,430,230);
setfillstyle(SOLID_FILL,7);
  bar(270,110,290,190);
  bar(270,210,290,290);
}

main()
{
int gd=DETECT,gm;
initgraph(&gd,&gm,"c:\\turboc3\\bgi");
int button,x,y,key;
ASHOK:
int a1,a2,a3,a4,a5,a6,a7,a8,a9; //colour for bars
a1=5;
a2=4;
a3=6;
a4=2;
a5=1;
a6=3;
a7=13;
a8=12;
a9=14;
int a,b,c; //check click
int d,e,f;
a=b=c=0; //initialize clicks
d=e=f=0;
int cl=15;
showmouseptr();
draw_click();
draw_hint();
draw_exit();
restart();
pause();
while(1)
{
  if(kbhit())
  {
  key=getkey();
  if(key==1)
  exit(0);
  }

if(a1==1&&a2==2&&a3==3&&a4==4&&a5==5&&a6==6&&a7==12&&a8==13&&a9==14)
{
  while(!kbhit())
  {
setfillstyle(SOLID_FILL,15);
bar(260,230,400,250);
outtextxy(280,235,"TOU WIN ENTER");
  key=getkey();
  if(key==28)
  exit(0);
  }
}
STAT:
getmousepos(&button,&x,&y);
if(button==1)
{
  if(button==1&&x>50&&x<125&&y>370&&y<400) //for exit to game
  {
    closegraph();
  }
  if(button==1&&x>125&&x<200&&y>370&&y<400) //for restart the game
  {
    clearviewport();
    goto ASHOK; //start game from ASHOK or restart game
  }
  if(button==1&&x>100&&x<200&&y>330&&y<360) //for pause the game
  {
  hidemouseptr();
  draw_pause(); //draw pause window
  setcolor(15);
  outtextxy(230,200,"PRESS ENTER TO CONTINUE");
  LOOP: //program repeat into the below loop
    key=getkey();
    if(key==28)
    {
    showmouseptr();
    clear_pause();
    goto STAT;  //if press enter program goto initial position
    }
  goto LOOP;  //if no press to enter then program run into loop
  }


  if(x>310&&x<390&&y>70&&y<90) //first colomn
  {
    a=1; //initialize colomn data
    d=e=f=0; //clear row data
    clear1(); //clear row rectangle
    setcolor(cl); //draw colomn rectangle
    rectangle(308,68,392,92);
    if(a==b)
    {
    swap(a1,a2,a4,a5,a7,a8);
    a=b=c=d=e=f=0;
    clear();
    }
    else if(a==c)
    {
    swap(a1,a3,a4,a6,a7,a9);
    a=b=c=d=e=f=0;
    clear();
    }
  }
  if(x>410&&x<490&&y>70&&y<90) //second colomn
  {
    b=1;
    d=e=f=0;
    clear1();
    setcolor(cl);
    rectangle(408,68,492,92);
    if(b==a)
    {
    swap(a1,a2,a4,a5,a7,a8);
    a=b=c=d=e=f=0;
    clear();
    }
    else if(b==c)
    {
    swap(a2,a3,a5,a6,a8,a9);
    a=b=c=d=e=f=0;
    clear();
    }
  }
  if(x>510&&x<590&&y>70&&y<90) //thirld colomn
  {
    c=1;
    d=e=f=0;
    clear1();
    setcolor(cl);
    rectangle(508,68,592,92);
    if(c==a)
    {
    swap(a1,a3,a4,a6,a7,a9);
    a=b=c=d=e=f=0;
    clear();
    }
    else if(c==b)
    {
    swap(a2,a3,a5,a6,a8,a9);
    a=b=c=d=e=f=0;
    clear();
    }
  }
  if(x>270&&x<290&&y>110&&y<190) //first row
  {
    d=1;
    a=b=c=0;
    clear();
    setcolor(cl);
    rectangle(268,108,292,192);
    if(d==e)
    {
    swap(a1,a4,a2,a5,a3,a6);
    a=b=c=d=e=f=0;
    clear1();
    }
    else if(d==f)
    {
    swap(a1,a7,a2,a8,a3,a9);
    a=b=c=d=e=f=0;
    clear1();
    }
  }
  if(x>270&&x<290&&y>210&&y<290) //second row
  {
    e=1;
    a=b=c=0;
    clear();
    setcolor(cl);
    rectangle(268,208,292,292);
    if(e==d)
    {
    swap(a1,a4,a2,a5,a3,a6);
    a=b=c=d=e=f=0;
    clear1();
    }
    else if(e==f)
    {
    swap(a4,a7,a5,a8,a6,a9);
    a=b=c=d=e=f=0;
    clear1();
    }
  }
  if(x>270&&x<290&&y>310&&y<390) //thirld row
  {
    f=1;
    a=b=c=0;
    clear();
    setcolor(cl);
    rectangle(268,308,292,392);
    if(f==d)
    {
    swap(a1,a7,a2,a8,a3,a9);
    a=b=c=d=e=f=0;
    clear1();
    }
    else if(f==e)
    {
    swap(a4,a7,a5,a8,a6,a9);
    a=b=c=d=e=f=0;
    clear1();
    }
  }
}

setfillstyle(SOLID_FILL,a1);
bar(300,100,400,200);
setfillstyle(SOLID_FILL,a2);
bar(400,100,500,200);
setfillstyle(SOLID_FILL,a3);
bar(500,100,600,200);
setfillstyle(SOLID_FILL,a4);
bar(300,200,400,300);
setfillstyle(SOLID_FILL,a5);
bar(400,200,500,300);
setfillstyle(SOLID_FILL,a6);
bar(500,200,600,300);
setfillstyle(SOLID_FILL,a7);
bar(300,300,400,400);
setfillstyle(SOLID_FILL,a8);
bar(400,300,500,400);
setfillstyle(SOLID_FILL,a9);
bar(500,300,600,400);

delay(100);
}
getch();
}