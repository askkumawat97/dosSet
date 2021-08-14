#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<stdlib.h>
struct arccoordstype h1,h2,h3,b1,b2,b3,a1,a2,a3;
struct arccoordstype c1,c2,c3,c4;
struct arccoordstype word;
main()
{
int gd=DETECT,gm;
initgraph(&gd,&gm,"c:\\turboc3\\bgi");
struct REGS i,o;
int x=350,y=200,r=100;
int key;
int ds,de;
int time=0;
int base=250,base1=0,base2=0;
int hour=0,hourc=0,hourc1=0;
int contx=150,conty=350,contc=180;
int bc1=0,bc2=90;
int button,x1=0,y1=0;
int xd,yd;
int rx,ry;
int askx=0,asky=0;

setfillstyle(1,12);
bar(0,0,640,480);
for(int q=0;q<10000;q++)
{
askx=random(640);
asky=random(480);
setcolor(0);//interchange bar and line color
line(300,200,askx,asky);
}

while(1)
{
if(kbhit())
 {
 i.h.ah=0;
 int86(22,&i,&o);
 key=o.h.ah;
 }
if(key==1)
 {
 closegraph();
 exit(0);
 }
if(key==28)
 {clearviewport(),x=300,y=200,r=100;}
i.x.ax=1;
int86(0x33,&i,&o);
i.x.ax=3;
rx=x1;
ry=y1;
int86(0x33,&i,&o);
button=o.x.bx;
x1=o.x.cx;
y1=o.x.dx;
if(button==1)
 {
 if(x1!=rx)clearviewport();
 if(x1-rx<0&&r>0) r--;
 if(x1-rx>0) r++;
 }
if(button==2)
 {
 if(x1!=rx)clearviewport();
 if(y1!=ry)clearviewport();
 x=x1+xd;
 y=y1+yd;
 }
xd=x-x1;
yd=y-y1;

if(key==2&&time>1)time-=10;
if(key==3&&time<100)time+=10;
key=0;

setcolor(0);
 line(x,y,b1.xstart,b1.ystart);//base line
 circle(b1.xstart,b1.ystart,8);
 line(b2.xstart,b2.ystart,b2.xend,b2.yend);//base center
 line(b3.xstart,b3.ystart,b3.xend,b3.yend);
 line(b2.xend,b2.yend,b3.xstart,b3.ystart);
line(x,y,h1.xstart,h1.ystart);//hour tip
circle(h2.xstart,h2.ystart,10);//hour center
line(h3.xstart,h3.ystart,h3.xend,h3.yend);
 line(contx,conty,b1.xstart,b1.ystart);//base control rod
 line(80,350,c1.xstart,c1.ystart);//base control circle arm
 line(c1.xstart,c1.ystart,contx,conty);
 circle(c1.xstart,c1.ystart,5);
 circle(contx,conty,5);
 line(c2.xstart,c2.ystart,c2.xend,c2.yend);//star circle
 line(c2.xend,c2.yend,c3.xend,c3.yend);
 line(c3.xend,c3.yend,c3.xstart,c3.ystart);
 line(c3.xstart,c3.ystart,c4.xstart,c4.ystart);
 line(c4.xstart,c4.ystart,c4.xend,c4.yend);

setcolor(0);//base handle
 arc(x,y,base,base+30,150);
 getarccoords(&b1);
setcolor(4);
 line(x,y,b1.xstart,b1.ystart);
 circle(b1.xstart,b1.ystart,8);
setcolor(15);//base center
 arc(x,y,base2,base2+240,20);
 getarccoords(&b2);
 arc(x,y,base2+120,base2+360,20);
 getarccoords(&b3);
 line(b2.xstart,b2.ystart,b2.xend,b2.yend);
 line(b3.xstart,b3.ystart,b3.xend,b3.yend);
 line(b2.xend,b2.yend,b3.xstart,b3.ystart);
setcolor(0);//hour tip
 arc(x,y,hour,hour+50,70);
 getarccoords(&h1);
 arc(x,y,hourc,hourc+50,30);
 getarccoords(&h2);
setcolor(3);//hour tip middle
 circle(h2.xstart,h2.ystart,10);
 arc(h2.xstart,h2.ystart,hourc1,hourc1+180,10);
 getarccoords(&h3);
 line(h3.xstart,h3.ystart,h3.xend,h3.yend);
setcolor(4);//hour tip line
 line(x,y,h1.xstart,h1.ystart);
setcolor(14);//base control rod
 if(base1==0)contx+=5;
 if(base1==1)contx-=5;
 line(contx,conty,b1.xstart,b1.ystart);
setcolor(15);//base circle
 arc(80,350,contc,contc+30,30);
 getarccoords(&c1);
 line(80,350,c1.xstart,c1.ystart);
 line(c1.xstart,c1.ystart,contx,conty);
 circle(c1.xstart,c1.ystart,5);
 circle(contx,conty,5);
setcolor(6);//star circle
 arc(80,350,bc1,bc1+144,30);
 getarccoords(&c2);
 arc(80,350,bc1+72,bc1+280,30);
 getarccoords(&c3);
 arc(80,350,bc1+216,bc1+360,30);
 getarccoords(&c4);
 line(c2.xstart,c2.ystart,c2.xend,c2.yend);
 line(c2.xend,c2.yend,c3.xend,c3.yend);
 line(c3.xend,c3.yend,c3.xstart,c3.ystart);
 line(c3.xstart,c3.ystart,c4.xstart,c4.ystart);
 line(c4.xstart,c4.ystart,c4.xend,c4.yend);

rectangle(155,345,250,355);
setcolor(15);
circle(x,y,75);
circle(x,y,r);
for(int j=0;j<350;j+=20)
 {
 if(j%40==0){ds=j+2,de=ds+11;}
 if(j%40==20){ds=j-2,de=ds+19;}
 arc(x,y,ds,de,r);
 getarccoords(&a1);
 arc(x,y,j,j+15,r+6);
 getarccoords(&a2);
 arc(x,y,j,j+15,r+10);
 getarccoords(&a3);
 line(a1.xstart,a1.ystart,a2.xstart,a2.ystart);
 line(a1.xend,a1.yend,a2.xend,a2.yend);
 line(a2.xstart,a2.ystart,a3.xstart,a3.ystart);
 line(a2.xend,a2.yend,a3.xend,a3.yend);
 }
char msg[10];
int wordc=60;
for(int k=1;k<=12;k++)
 {
 setcolor(0);
 arc(x,y,wordc,wordc+10,87);
 getarccoords(&word);
 setcolor(4);
 settextjustify(1,1);
 sprintf(msg,"%d",k);
 outtextxy(word.xstart,word.ystart,msg);
 wordc-=30;
 }

if(base==250)base1=0;
if(base==290)base1=1;
if(base1==0){base+=2,base2+=1,hourc1-=2;}
if(base1==1){base-=2;}
if(base1==0&&base==290){hour-=6,hourc-=6;}
contc+=9;
bc1+=9;

delay(time);
}//end while(1)
getch();
}