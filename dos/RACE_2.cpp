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

restrict_mouse(int x1,int x2)
{
i.x.ax=7;
i.x.cx=x1;
i.x.dx=x2;
int86(0x33,&i,&o);
}

exit()
{
int key;
if(kbhit())
{
key=getkey();
if(key==1)
exit(0);
}
}

draw_boost_bar()
{
setcolor(8);
rectangle(418,168-50,512,202-50);
rectangle(419,169-50,511,201-50);
setfillstyle(SOLID_FILL,6);
bar(421,171-50,509,199-50);
setcolor(4);
outtextxy(425,175-50,"ENTER TO");
outtextxy(460,190-50,"BOOST");
}

game_over()
{
}

main()
{
int gd=DETECT,gm;
initgraph(&gd,&gm,"c:\\turboc3\\bgi");
int button,x,y,key;
int count=1;
int time=100;
int life=0;
int boost=0;
int car_col_1=4,car_col_2=12;
showmouseptr();
  rectangle(9,0,341,500);  /*to draw road*/
  setfillstyle(SOLID_FILL,8);
  bar(10,0,340,500);
    setcolor(5);  /*to draw exit bar*/
    rectangle(360,20,580,50);
    setfillstyle(SOLID_FILL,13);
    bar(362,22,578,48);
    setcolor(14);
    outtextxy(370,30,"CLICK ESCAPE TO EXIT GAME");
  setcolor(5);  /*draw color bar*/
  rectangle(360,60,580,90);
  setfillstyle(SOLID_FILL,13);
  bar(362,62,578,88);
  setcolor(14);
  outtextxy(380,70,"CLICK C TO CHANGE COLOR");
while(1)
{
if(kbhit())
{
key=getkey();
if(key==1)
  {
  nosound();
  exit(0);
  }
if(key==28&&boost==1)
  time=40;
if(key==46)  /*for change car color*/
  {
  car_col_1+=1;
  car_col_2+=1;
  }
}

sound(40);

setfillstyle(SOLID_FILL,0); /*for life of car*/
if(life==1)
{
   int i;
   for(i=100;i<800;i+=100)
   {
   sound(i);
   delay(100);
   }
game_over();
printf("score is %d",count);
nosound();
delay(1000);
exit(0);
}

int check;
if(count%50==0) /*for boost*/
{
   int i;
   for(i=300;i<400;i+=10)
   {
   sound(i);
   delay(2);
   }
draw_boost_bar();
boost=1;
check=count;
}
if(count==check+20)
{
setfillstyle(SOLID_FILL,10);
bar(418,118,512,152);
boost=0;
time=100;
}

hidemouseptr();
    setcolor(7); /*to draw road divider*/
    rectangle(120,-1,230,500);
restrict_mouse(10,310); /*control player car*/
    static x=10;
    setfillstyle(SOLID_FILL,8);
    bar(x,400,x+30,450);
getmousepos(&button,&x,&y);
  setfillstyle(SOLID_FILL,car_col_1);  /*draw player car*/
    bar(x,400,x+30,450);
  setfillstyle(SOLID_FILL,car_col_2);
    bar(x+5,400,x+30-5,450);
  setfillstyle(SOLID_FILL,0);
    bar(x,400+10,x+30-29,450-35);
    bar(x,400+40,x+30-29,450-5);
    bar(x+29,400+10,x+30,450-35);
    bar(x+29,400+40,x+30,450-5);
  setcolor(car_col_2);
    rectangle(x+2,400+2,x+30-2,450-2);
  setfillstyle(SOLID_FILL,car_col_1);
    bar(x+20,400+20,x+30-20,450-10);


static car1=10,car1x=100;  /*charecteristics of green car 1*/
setfillstyle(SOLID_FILL,2);
bar(car1x,car1,car1x+30,car1+50);
  setfillstyle(SOLID_FILL,10);
  bar(car1x+5,car1+8,car1x+30-5,car1+50-15);
setfillstyle(SOLID_FILL,8);
bar(car1x,car1-20,car1x+30,car1);
car1+=20;
if(car1>500)
{
count++;
int car1xx;
car1=10;
car1xx=random(310);
car1x=car1xx+10;
}
if(x>car1x-30&&x<car1x+30 && car1>350&&car1<450)
{
rectangle(x,400,x+30,450);
life=1;
}


static car2=20,car2x=200;   /*charecteristics of blue car 2*/
setfillstyle(SOLID_FILL,1);
bar(car2x,car2,car2x+30,car2+50);
  setfillstyle(SOLID_FILL,9);
  bar(car2x+5,car2+8,car2x+30-5,car2+50-15);
setfillstyle(SOLID_FILL,8);
bar(car2x,car2-30,car2x+30,car2);
car2+=30;
if(car2>500)
{
count++;
int car2xx;
car2=20;
car2xx=random(310);
car2x=car2xx+10;
}
if(x>car2x-30&&x<car2x+30 && car2>350&&car2<450)
{
rectangle(x,400,x+30,450);
life=1;
}


static car3=30,car3x=300;   /*charecteristics of cyan car 3*/
setfillstyle(SOLID_FILL,3);
bar(car3x,car3,car3x+30,car3+50);
  setfillstyle(SOLID_FILL,11);
  bar(car3x+5,car3+8,car3x+30-5,car3+50-15);
setfillstyle(SOLID_FILL,8);
bar(car3x,car3-40,car3x+30,car3);
car3+=40;
if(car3>520)
{
count++;
int car3xx;
car3=30;
car3xx=random(310);
car3x=car3xx+10;
}
if(x>car3x-30&&x<car3x+30 && car3>350&&car3<450)
{
rectangle(x,400,x+30,450);
life=1;
}


delay(time);
}
nosound();
getch();
}