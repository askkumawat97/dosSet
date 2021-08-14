#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<stdlib.h>
#include<math.h>
/*working of this program*/
     /*if we click on the any block then the colour of clicked block is
     change by black and the black coloured block get to the colour of
     clicked block*/
     /*position of block is constant only colours of block is change*/
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

exit()
{
if(kbhit())
{
int key;
key=getkey();
if(key==1)
exit(0);
}
}

draw() /*draw out lines of main game blocks*/
{
int i,j;
int a=100,b=300;
setcolor(10);
for(i=0;i<4;i++)
{
line(300,a,600,a);
a+=100;
}
for(j=0;j<4;j++)
{
line(b,100,b,400);
b+=100;
}
}

value() /*value of rectangle blocks*/
{
static a1=300,b1=100;
static a2=400,b2=100;
static a3=500,b3=100;
static a4=300,b4=200;
static a5=400,b5=200;
static a6=500,b6=200;
static a7=300,b7=300;
static a8=400,b8=300;
static a9=500,b9=300;
}

view() /*to draw game help on top right*/
{
int i,j;
int a=50,b=50;
int col=0;
for(i=0;i<3;i++)
 {
 a=50;
 for(j=0;j<3;j++)
 {
 setfillstyle(SOLID_FILL,col);
 bar(a,b,a+50,b+50);
 a=a+50;
 col++;
 }
 b=b+50;
 }
}

win() /*output to win game*/
{
int i;
int a=50;
int col=0;
for(i=0;i<20;i++)
{
setcolor(col);
circle(310,220,a);
a+=5;
col++;
}
outtextxy(280,220,"YOU WIN");
}

lose()/*if time out or game over*/
{
int i;
int a=50;
int col=0;
for(i=0;i<20;i++)
{
setcolor(col);
circle(310,220,a);
a+=5;
col++;
}
outtextxy(280,220,"YOU LOSE");
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

health() /*draw health bar*/
{
int i;
int a=302;
setcolor(12);
rectangle(300,35,600,65);
setfillstyle(SOLID_FILL,12);
bar(303,38,597,62);
}

draw_pause() /*draw pause window if click on pause button*/
{
setcolor(13);
rectangle(204,174,436,236);
rectangle(207,177,433,233);
setfillstyle(SOLID_FILL,13);
bar(210,180,430,230);
}

clear_pause() /*clear pause window if press enter to back*/
{
setcolor(0);
rectangle(204,174,436,236);
rectangle(207,177,433,233);
setfillstyle(SOLID_FILL,0);
bar(210,180,430,230);
}

ask_to_repeat()  /*if we win or loss then this ask to play again the game*/
{
int key;
setfillstyle(SOLID_FILL,9);
bar(200,370,430,415);
setcolor(14);
outtextxy(215,380,"CLICK ENTER TO PLAY AGAIN");
outtextxy(215,400,"CLICK ESCAPE TO EXIT GAME");
if(kbhit()) /*get input for destination*/
{
key=getkey();
if(key==1) /*if press escape key game exit*/
  {
  closegraph();
  exit(0);
  }
if(key==28) /*if press enter key then return value 5 to perticuler variable*/
return 5;
}
}

main()
{
int gd=DETECT,gm;
initgraph(&gd,&gm,"c:\\turboc3\\bgi");
int button,x,y,key;
ASHOK: /*if mouse click on restart then game load from here*/
  static a1=300,b1=100;
  static a2=400,b2=100;
  static a3=500,b3=100;
  static a4=300,b4=200;
  static a5=400,b5=200;
  static a6=500,b6=200;
  static a7=300,b7=300;
  static a8=400,b8=300;
  static a9=500,b9=300;

int j,al;
int col; /*it is use to change the color of block*/
int click=0; /*count click to complete game*/
int time=0;  /*counting of game time*/
int aa=302;  /*x2 position of black bar in health bar*/

int get;  /*use for getkey() in pause mose*/
int c[9]={8,5,7,2,3,0,6,1,4}; /*get color to blocks*/
showmouseptr();
for(j=0;j<9;j++)/*to check the element where value is zero*/
{
if(c[j]==0)
al=j;
}

while(1)
{
exit(); /*if press esc key then exit to game*/
static high=302;
setfillstyle(SOLID_FILL,14);
bar(302,25,high,30);
  if(time==30000) /*game over if time is lost*/
  {
  int ask;
  clearviewport();
  ask=ask_to_repeat(); /*if loss game ask play to repeat*/
  ASK2: /*the loop is use for get input for play again or exit*/
    lose(); /*display loss window*/
    ask=ask_to_repeat(); /*if we press enter then value of ask is 5*/
    if(ask==5)
    {
    clearviewport();
    goto ASHOK;  /*for restart the game*/
    }
  goto ASK2; /*if no any input then repeat above loop simultanuously*/
  }
health();  /*draw health bar*/
setfillstyle(SOLID_FILL,0); /*for increase black bar*/
bar(302,38,aa,62);              /*but we see to decrease health bar*/
aa+=1;

restart(); /*draw restart button*/
pause(); /*draw pause button*/
draw(); /*draw outlines of main game blocks*/
view(); /*draw game help panel*/
draw_exit(); /*draw exit button*/
setcolor(3);
outtextxy(50,250,"clicks =");
  if(c[0]==0&&c[1]==1&&c[2]==2&&c[3]==3&&c[4]==4&&c[5]==5
  &&c[6]==6&&c[7]==7&&c[8]==8)    /*output if complete game*/
  {
  int ask;
  clearviewport();
  high=aa;  /*for get minimum time to complete game*/
  ASK1: /*the loop is use for get input for play again or exit*/
    win();  /*display win window*/
    ask=ask_to_repeat(); /*if we press enter then value of ask is 5*/
    if(ask==5)
    {
    clearviewport();
    goto ASHOK;  /*for restart the game*/
    }
  goto ASK1; /*if no any input then repeat above loop simultanuously*/
  }
STAT:
getmousepos(&button,&x,&y);
  if(button==1&&x>100&&x<200&&y>330&&y<360) /*if mouse clicked on pause button*/
  {
  hidemouseptr();
  draw_pause(); /*draw pause window*/
  setcolor(15);
  outtextxy(230,200,"PRESS ENTER TO CONTINUE");
  LOOP: /*program repeat into the below loop*/
    {
    get=getkey();
    if(get==28)
    {
    showmouseptr();
    clear_pause();
    goto STAT;  /*if press enter program goto initial position*/
    }
    }
  goto LOOP;  /*if no press to enter then program run into loop*/
  }
	 if(button==1&&x>50&&x<125&&y>370&&y<400) /*for exit to game*/
	 {
	 closegraph();
	 }
	 if(button==1&&x>125&&x<200&&y>370&&y<400) /*for restart the game*/
	 {
	 clearviewport();
	 goto ASHOK; /*start game from ASHOK or restart game*/
	 }
  /*check mouse click then swap value of clicked block and black colour block*/
  if(button==1&&x>300&&x<400&&y>100&&y<200)
  {
  col=c[0],c[0]=0,c[al]=col,al=0;
  click++;
  }
  if(button==1&&x>400&&x<500&&y>100&&y<200)
  {
  col=c[1],c[1]=0,c[al]=col,al=1;
  click++;
  }
  if(button==1&&x>500&&x<600&&y>100&&y<200)
  {
  col=c[2],c[2]=0,c[al]=col,al=2;
  click++;
  }
  if(button==1&&x>300&&x<400&&y>200&&y<300)
  {
  col=c[3],c[3]=0,c[al]=col,al=3;
  click++;
  }
  if(button==1&&x>400&&x<500&&y>200&&y<300)
  {
  col=c[4],c[4]=0,c[al]=col,al=4;
  click++;
  }
  if(button==1&&x>500&&x<600&&y>200&&y<300)
  {
  col=c[5],c[5]=0,c[al]=col,al=5;
  click++;
  }
  if(button==1&&x>300&&x<400&&y>300&&y<400)
  {
  col=c[6],c[6]=0,c[al]=col,al=6;
  click++;
  }
  if(button==1&&x>400&&x<500&&y>300&&y<400)
  {
  col=c[7],c[7]=0,c[al]=col,al=7;
  click++;
  }
  if(button==1&&x>500&&x<600&&y>300&&y<400)
  {
  col=c[8],c[8]=0,c[al]=col,al=8;
  click++;
  }
 /*change block colour after get mouse click and draw blocks*/
setfillstyle(SOLID_FILL,c[0]);
bar(a1,b1,a1+100,b1+100);
setfillstyle(SOLID_FILL,c[1]);
bar(a2,b2,a2+100,b2+100);
setfillstyle(SOLID_FILL,c[2]);
bar(a3,b3,a3+100,b3+100);
setfillstyle(SOLID_FILL,c[3]);
bar(a4,b4,a4+100,b4+100);
setfillstyle(SOLID_FILL,c[4]);
bar(a5,b5,a5+100,b5+100);
setfillstyle(SOLID_FILL,c[5]);
bar(a6,b6,a6+100,b6+100);
setfillstyle(SOLID_FILL,c[6]);
bar(a7,b7,a7+100,b7+100);
setfillstyle(SOLID_FILL,c[7]);
bar(a8,b8,a8+100,b8+100);
setfillstyle(SOLID_FILL,c[8]);
bar(a9,b9,a9+100,b9+100);
delay(100); /*stop loop for 100 milisecond*/
time=time+100; /*count time of game*/
}
getch();
}