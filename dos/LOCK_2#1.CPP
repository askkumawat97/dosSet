#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<dos.h>
#include<math.h>
int background=0; //color of background
int col1=15; //color of lock-outer circle
int col2=8; //color of lock-inner circle
int col_line=4; //color of lock-line

struct REGS i,o;
struct arccoordstype a1,a2,a3,a4;

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
return 0;
}

hidemouseptr()
{
i.x.ax=2;
int86(0x33,&i,&o);
return 0;
}

getmousepos(int *button,int *x,int *y)
{
i.x.ax=3;
int86(0x33,&i,&o);
*button=o.x.bx;
*x=o.x.cx;
*y=o.x.dx;
return 0;
}

movemouseptr(int x,int y)
{
i.x.ax=4;
i.x.cx=x;
i.x.dx=y;
int86(0x33,&i,&o);
return 0;
}

restrictptr(int x1,int x2,int y1,int y2)
{
i.x.ax=7;
i.x.cx=x1;
i.x.dx=x2;
int86(0x33,&i,&o);
i.x.ax=8;
i.x.cx=y1;
i.x.dx=y2;
int86(0x33,&i,&o);
return 0;
}

exit()
{
int key;
if(kbhit())
{
 key=getkey();
 if(key==1)
 {
  closegraph();
  exit(0);
 }
}
return 0;
}


lock_animation()
{
int a=320,b=-150;
int angle=-120;
int rot_time=0;
int radias1=66;
int radias2=67;
while(rot_time!=1000)
{
setcolor(15);
rectangle(0,0,getmaxx(),getmaxy());
if(b<240)
 b+=10;
if(angle<0)
 angle+=2;
if(angle==0&&radias1<100)
 radias1+=2;
if(angle==0&&radias2<141)
 radias2+=5;

if(rot_time<=750)
{
setcolor(background);
circle(a,b-10,20);
 putpixel(a,b-10,background);
circle(a1.xstart,a1.ystart,20);
circle(a1.xend,a1.yend,20);
 putpixel(a1.xstart,a1.ystart,background);
 putpixel(a1.xend,a1.yend,background);
circle(a2.xstart,a2.ystart,20);
circle(a2.xend,a2.yend,20);
 putpixel(a2.xstart,a2.ystart,background);
 putpixel(a2.xend,a2.yend,background);
circle(a3.xstart,a3.ystart,20);
circle(a3.xend,a3.yend,20);
 putpixel(a3.xstart,a3.ystart,background);
 putpixel(a3.xend,a3.yend,background);
circle(a4.xstart,a4.ystart,20);
circle(a4.xend,a4.yend,20);
 putpixel(a4.xstart,a4.ystart,background);
 putpixel(a4.xend,a4.yend,background);
}

setcolor(background);
arc(a,b,angle+0,angle+90,radias1);
getarccoords(&a1);
arc(a,b,angle+180,angle+270,radias1);
getarccoords(&a2);
arc(a,b,angle+45,angle+135,radias2);
getarccoords(&a3);
arc(a,b,angle+225,angle+315,radias2);
getarccoords(&a4);

setcolor(col1);
circle(a,b,20);
 putpixel(a,b,col1);
circle(a1.xstart,a1.ystart,20);
circle(a1.xend,a1.yend,20);
 putpixel(a1.xstart,a1.ystart,col1);
 putpixel(a1.xend,a1.yend,col1);
circle(a2.xstart,a2.ystart,20);
circle(a2.xend,a2.yend,20);
 putpixel(a2.xstart,a2.ystart,col1);
 putpixel(a2.xend,a2.yend,col1);
circle(a3.xstart,a3.ystart,20);
circle(a3.xend,a3.yend,20);
 putpixel(a3.xstart,a3.ystart,col1);
 putpixel(a3.xend,a3.yend,col1);
circle(a4.xstart,a4.ystart,20);
circle(a4.xend,a4.yend,20);
 putpixel(a4.xstart,a4.ystart,col1);
 putpixel(a4.xend,a4.yend,col1);

rot_time+=10;
delay(20);
}
setfillstyle(1,background);
bar(0,0,640,480);
return 0;
}

lock_pattern()
{
int i,j;
setcolor(15);
rectangle(0,0,getmaxx(),getmaxy());
for(i=220;i<=420;i+=100)
{
 for(j=140;j<=340;j+=100)
 {
 setcolor(col1);
 circle(i,j,20);
 setcolor(col2);
 circle(i,j,10);
 }
}
return 0;
}

draw_right_box(int x,int y) //use in layer2_password_right(int)
{
hidemouseptr(); //if not use black bar occur at mousepos
settextjustify(1,1); //centre to coordinates
setcolor(0);
for(int a=1;a<=10;a++)
{
setfillstyle(SOLID_FILL,12); //first row
bar(x,y+a*7,x+100,y+a*10);
setcolor(4);
rectangle(x,y+a*7+2,x+100,y+a*10-1);
outtextxy(x+50,y+a*8.5,"EXIT");
setfillstyle(SOLID_FILL,10); //second row
bar(x,y+a*4,x+100,y+a*7);
setcolor(2);
rectangle(x,y+a*4+2,x+100,y+a*7-1);
outtextxy(x+50,y+a*5.5,"LOCK");
setfillstyle(SOLID_FILL,9); //thirld row
bar(x,y+a,x+100,y+a*4);
setcolor(1);
rectangle(x,y+a+2,x+100,y+a*4-1);
outtextxy(x+50,y+2+a*2.5,"CHANGE");
setfillstyle(SOLID_FILL,8); //base row
bar(x,y,x+100,y+10);
setcolor(0);
rectangle(x,y+1,x+100,y+10-1);
delay(20);
}
showmouseptr(); //if not use black bar occur at mousepos
}

app_loading()
{ }/*
int a=0,b=0,c=0;
int d;
while(c<=300)
{
d=random(100);
setcolor(4);
line(0,220,300,220);
setcolor(4);
line(a,b+170,c,d+170);
a=c,b=d;
c=c+2;
delay(5);
}
}
      */
program_about()
{  }/*
hidemouseptr();
setfillstyle(SOLID_FILL,0);
bar(0,0,300-1,440-1);
bar(301,10,650,440); //for clear layer2 hint
setfillstyle(SOLID_FILL,2);
bar(60,3,240,17);
setcolor(15);
settextjustify(1,1);
outtextxy(150,10,"PRESS ANY KEY TO BACK");
setcolor(4);
int ai;
int x=0,y=0;
int a1=x+20,a2=y+40;
for(ai=0;ai<30;ai++)
 {
 line(x+10,y+140,a1,a2);
 a1+=1;
 a2+=4;
 }
int b1=x+50,b2=y+110;
int b3=x+110,b4=y+90;
for(ai=0;ai<30;ai++)
 {
 line(b1,b2,b3,b4);
 b1+=2,b2-=3;
 b3-=2,b4+=2;
 }
int c2=y+30,c4=y+150;
for(ai=0;ai<40;ai++)
 {
 line(x+115,c2,x+160,c4);
 c2+=3,c4-=3;
 }
int d1=x+220,d2=y+130;
int d3=x+170,d4=y+150;
for(ai=0;ai<14;ai++)
 {
 line(x+230,y+30,d1,d2);
 d1-=4,d2+=2;
 }
for(ai=0;ai<30;ai++)
 {
 line(x+230,y+30,d3,d4);
 d3+=1,d4-=4;
 }
int e1=x+240,e2=y+50;
int e3=x+270,e4=y+150;
for(ai=0;ai<17;ai++)
 {
 line(x+230,y+150,e1,e2);
 e1+=3,e2-=2;
 }
for(ai=0;ai<12;ai++)
 {
 line(x+260,y+90,e3,e4);
 e3+=2;
 }
 getch();
}
  */

/*layer2_hint()
{
setfillstyle(SOLID_FILL,12); //layer2 hint
bar(310,10,410,40);
setcolor(0);
rectangle(311,11,409,39);
settextjustify(1,1);
outtextxy(360,20,"RIGHT CLICK");
outtextxy(360,30,"SETTING");

setcolor(15);
rectangle(310,50,600,170);
rectangle(315,55,595,165);
settextjustify(0,2);
setcolor(4);
outtextxy(320,60,"create a file with perticuler name");
setcolor(12);
outtextxy(320,70,"eg. ashok1.c");
setcolor(4);
outtextxy(320,80,"INSIDE FILE:");
setcolor(12);
outtextxy(320,90,"name of program");
outtextxy(320,100,"make a function with similer name");
outtextxy(320,110,"eg.");
setcolor(2);
outtextxy(320,120,"  ashok1()");
outtextxy(320,130,"  {");
outtextxy(320,140,"  your program coading");
outtextxy(320,150,"  }");
}
  */

int layer2_password_right() //if password right layer activate
{  //return 10 if click on lock,return 11 if click on change
setfillstyle(1,background); //clear layer1 background
bar(0,0,getmaxx(),getmaxy());
int button1,x1,y1=0;
int yy=0,a; // draw and clear vertical cubes
int drop=0; //for right click window
int xx1=-1000,yy1=-1000; //for left click in right_box
movemouseptr(0,0);
int box_col=3;
float app_no=2; //number of applications in layer2-@@@@@@@@@@@@@@@@@@@@@@@@@
float box_no; //box number of clicked box
float ptr_range;
while(1)
{
showmouseptr();
setcolor(15);
rectangle(0,0,getmaxx(),getmaxy());
//ptr_range=(app_no*440/((app_no*app_no)+(app_no*app_no/10)) )/10;
ptr_range=40/app_no;
a=yy;
getmousepos(&button1,&x1,&y1);
if(button1==1)
 {
 if(drop==0&&x1>100&&x1<200)
  {
  for(float pt=0;pt<=440;pt+=(11*ptr_range)) //check for app_no of times
   {
   if(y1>pt&&y1<pt+(10*ptr_range)) //if inside the box
     {
     box_no=((int)pt+1)/(11*ptr_range)+1; //to find number of clicked box
     // printf("%f-",box_no);
     if((int)box_no==app_no) //last box
      {
      if(x1>100&&x1<150) //for new
      {app_no++,delay(200);}
      if(x1>150&&x1<200&&app_no>2) //for delete
      {app_no--,delay(200);}
      }
     else if((int)box_no==1) //integer value of box_no(ie. float)
      {program_about();}
     else
      {
      app_loading();
      //user define apps
      if((int)box_no==2)
      {}
      }
     setfillstyle(SOLID_FILL,background);
     bar(0,0,getmaxx(),getmaxy());
   } //end if
  } //end for
  } //end if
 //if left click on base bar of right box
 if(drop==1&&x1>xx1&&x1<xx1+100&&y1>yy1&&y1<yy1+10)
  {
  drop=0;
  hidemouseptr();
  setfillstyle(SOLID_FILL,background);
  bar(1,1,299,439);
  }
 //if left click after right click
 if(drop==1&&x1>xx1&&x1<xx1+100&&y1>yy1+10&&y1<yy1+40)
  {hidemouseptr();
  return 11;}
 if(drop==1&&x1>xx1&&x1<xx1+100&&y1>yy1+40&&y1<yy1+70)
  {hidemouseptr();
  return 10;}
 if(drop==1&&x1>xx1&&x1<xx1+100&&y1>yy1+70&&y1<yy1+100)
  {hidemouseptr(),closegraph(),exit(0);}
 //if left click on free space
 drop=0;
 hidemouseptr();
 setfillstyle(1,background);
 bar(xx1,yy1,xx1+100,yy1+100);
 } //end if(button1==1)

if(button1==2)
 {
 hidemouseptr();
 setfillstyle(1,background);
 bar(1,1,getmaxx(),getmaxy());
 }
if(button1==2|drop==0&&x1>=0&&x1<=getmaxx())
{
hidemouseptr();
if(button1!=2&&x1>=100&&x1<200)
yy=-(y1*(app_no-4)/4);
int aa=0;
for(int i1=-10;i1<110*app_no;i1+=110) //for clear app boxes
 {
 setfillstyle(SOLID_FILL,background);
 bar(aa+100,a+i1+1,aa+200,a+i1+10-1);
 }
 setfillstyle(SOLID_FILL,background);
 bar(aa+100,0+1,aa+200,a-1);
 bar(aa+100,a+110*app_no+1,aa+200,440);
for(int i=0;i<110*app_no;i+=110) //for draw app boxes
 {
 if(i==0) //for first box
  {
  setfillstyle(SOLID_FILL,box_col);
  bar(100+2,yy+i+2,200-2,yy+i+100-2);
  setcolor(4);
  settextjustify(1,1);
  outtextxy(150,yy+i+50,"ABOUT");
  }
 else if(i==110*(app_no-1)) //for devide last box into two part
  {
  setfillstyle(SOLID_FILL,box_col);
  bar(100+2,yy+i+2,200-2,yy+i+100-2);
  setcolor(background);
  line(150,yy+i+1,150,yy+i+100-1);
  setcolor(4);
  settextjustify(1,1);
  outtextxy(125,yy+i+50,"NEW");
  outtextxy(175,yy+i+50,"DELETE");
  if(app_no<=2)
   {setcolor(12);
   outtextxy(175,yy+i+50,"DELETE");}
  }
 else
  {
  setfillstyle(1,11);//box_col);
  bar(100+2,yy+i+2,200-2,yy+i+100-2);
  setcolor(4); //for file name of the user crested boxes
  char msg[7];
  sprintf(msg,"%d",i/110);
  outtextxy(125,yy+i+10,"ASHOK");
  outtextxy(155,yy+i+10,msg);
  outtextxy(170,yy+i+10,".C");
  }
 setcolor(15); //common part in all boxes
 rectangle(100,yy+i,200,yy+i+100);
 setcolor(background);
 rectangle(100+1,yy+i+1,200-1,yy+i+100-1);
 }
showmouseptr();
}
if(button1==2)
 {
 drop=1; //the above if can not be exicuted during this exicution
 if(x1<=getmaxx()-100&&y1<=getmaxy()-100)
  {
  draw_right_box(x1,y1);
  xx1=x1,yy1=y1;
  }
 if(x1>getmaxx()-100&&y1<=getmaxy()-100)
  {
  draw_right_box(x1-100,y1);
  xx1=x1-100,yy1=y1;
  }
 if(x1<=getmaxx()-100&&y1>getmaxy()-100)
  {
  draw_right_box(x1,y1-100);
  xx1=x1,yy1=y1-100;
  }
 if(x1>getmaxx()-100&&y1>getmaxy()-100)
  {
  draw_right_box(x1-100,y1-100);
  xx1=x1-100,yy1=y1-100;
  }
 }
delay(10);
} //end while
} //end of function


main()
{
int layer2=0;
//static defalt[18]={0,4,0,1,0,2,0,6,0,9,0,8,0,7,0,5,0,3}; //default password
static defalt[18]={0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int gd=DETECT,gm;
initgraph(&gd,&gm,"c:\\turboc3\\bgi");
START:
int button,x,y;
int a[10]={0,0,0,0,0,0,0,0,0,0};
int x1=0,y1=0;
int x11=0,y11=0;
int x2,y2;
int clear=0;
int redraw[10]={0,0,0,0,0,0,0,0,0,0};
int check[18]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //entered password
int m=0; //index of check for password checking
int password=0;
int count_password=0; //count wrong password
int a1=220,b1=140;
int a2=320,b2=140;
int a3=420,b3=140;
int a4=220,b4=240;
int a5=320,b5=240;
int a6=420,b6=240;
int a7=220,b7=340;
int a8=320,b8=340;
int a9=420,b9=340;
int scan=0,scanb=0;
int wtime=0; //time for clear word "WRONG PASSWORD"
int bar1=0; //time bar
int line_poly[18]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int pol=0;
layer2_password_right();//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

setfillstyle(1,background);
bar(0,0,getmaxx(),getmaxy());
initmouse();
movemouseptr(0,0);
lock_animation();
while(1)
{
exit();
restrictptr(0,getmaxx(),0,getmaxy());
if(password==0) //if password right it not exicute
lock_pattern();

if(bar1==1) //if password wrong many times
{
 for(int i=0;i<120;i++)
 {
 setfillstyle(9,4);
 bar(260,180,260+i,200);
 setcolor(6);
 rectangle(258,178,381,202);
 setcolor(12);
 settextjustify(1,1);
 outtextxy(320,190,"WAIT 12 SEC");
 delay(100);
 }
 bar1=0;
 setfillstyle(1,background);
 bar(258,178,381,202);
}
getmousepos(&button,&x,&y);
 setcolor(background);
 circle(x11,y11,10);
 setcolor(2);
 circle(x,y,10);
 x11=x,y11=y;

if(button==1&&x>=0&&x<=getmaxx()&&y>=0&&y<=getmaxy())
{
clear=1;
hidemouseptr();  //for user define ptr
restrictptr(0+10,getmaxx()-10,0+10,getmaxy()-10);
if(scan!=0)
 {
 setcolor(background);
 circle(x1,y1,10);
 setcolor(14);
 circle(x,y,10);
 }
setcolor(col_line);
if(scan==1&&redraw[scan]==0){line_poly[pol]=220,line_poly[pol+1]=140,pol+=2;}
if(scan==2&&redraw[scan]==0){line_poly[pol]=320,line_poly[pol+1]=140,pol+=2;}
if(scan==3&&redraw[scan]==0){line_poly[pol]=420,line_poly[pol+1]=140,pol+=2;}
if(scan==4&&redraw[scan]==0){line_poly[pol]=220,line_poly[pol+1]=240,pol+=2;}
if(scan==5&&redraw[scan]==0){line_poly[pol]=320,line_poly[pol+1]=240,pol+=2;}
if(scan==6&&redraw[scan]==0){line_poly[pol]=420,line_poly[pol+1]=240,pol+=2;}
if(scan==7&&redraw[scan]==0){line_poly[pol]=220,line_poly[pol+1]=340,pol+=2;}
if(scan==8&&redraw[scan]==0){line_poly[pol]=320,line_poly[pol+1]=340,pol+=2;}
if(scan==9&&redraw[scan]==0){line_poly[pol]=420,line_poly[pol+1]=340,pol+=2;}
drawpoly(pol/2,line_poly);

//initially x1=y1=0,scan=0,scanb=0,redraw[10]={0,0...,0},a[10]={0,0...,0}
//redraw[1]=0 ie below "if statment" can be exicuted
for(int n=1;n<=9;n++) //for password initialisation or password making
{
 if(redraw[n]==1) //when click on any circle
 {
 m++;
 redraw[n]=2;
 check[m]=n;
 }
}
if(redraw[1]==0&&(pow((x-a1),2)+ pow((y-b1),2)<400)) //first circle
 { //          ^-----------------------------------------------------------\
 if(scan==0) //value assigned to x2 y2 for only first click of program      |
  x2=a1,y2=b1; //                                                           |
 a[1]=1; //if click on first circle ----------------------------------\     |
 a[2]=a[3]=a[4]=a[5]=a[6]=a[7]=a[8]=a[9]=0; //other all circle are reset\   |
 scanb=scan; // below all stmt are asigned to zero                       |  |
 scan=1; //                                                              |  |
 redraw[scanb]=1; //                                                     |  |
  setcolor(background); //                                                |  |
  line(x2,y2,x1,y1); //                                                   |  |
 } //                                                                   /   |
 if(a[1]==1) //   <---------------------------------------------------/     |
  { //                                                                      |
  setcolor(background); //                                                  |
  line(a1,b1,x1,y1); //                                                     |
  x1=x,y1=y; //                                                             |
  setcolor(col_line); //                                                    |
  line(a1,b1,x,y); // above 5 line restrict the line from clicked circle    |
  x2=a1,y2=b1; // this value is send to next click--------------------\     |
  } //                                                                  \   |
if(redraw[2]==0&&(pow((x-a2),2)+ pow((y-b2),2)<400)) //second circle     |  |
 { //                                                                    |  |
 if(scan==0) //                                                          |  |
  x2=a2,y2=b2; //                                                        |  |
 a[2]=1; //                                                              |  |
 a[1]=a[3]=a[4]=a[5]=a[6]=a[7]=a[8]=a[9]=0; //                           |  |
 scanb=scan; //scanb=1                                                   |  |
 scan=2; //                                                              |  |
 redraw[scanb]=1; //first circle can not be access again-----------------|-/
  setcolor(background); //                                               /
  line(x2,y2,x1,y1); // <----------------------------------------------/
 }
 if(a[2]==1)
  {
  setcolor(background);
  line(a2,b2,x1,y1);
  x1=x,y1=y;
  setcolor(col_line);
  line(a2,b2,x,y);
  x2=a2,y2=b2;
  }
 if(redraw[3]==0&&(pow((x-a3),2)+ pow((y-b3),2)<400)) //thirld circle
 {
 if(scan==0)
  x2=a3,y2=b3;
 a[3]=1;
 a[1]=a[2]=a[4]=a[5]=a[6]=a[7]=a[8]=a[9]=0;
 scanb=scan;
 scan=3;
 redraw[scanb]=1;
  setcolor(background);
  line(x2,y2,x1,y1);
 }
 if(a[3]==1)
  {
  setcolor(background);
  line(a3,b3,x1,y1);
  x1=x,y1=y;
  setcolor(col_line);
  line(a3,b3,x,y);
  x2=a3,y2=b3;
  }
 if(redraw[4]==0&&pow((x-a4),2)+ pow((y-b4),2)<400) //forth circle
 {
 if(scan==0)
  x2=a4,y2=b4;
 a[4]=1;
 a[1]=a[2]=a[3]=a[5]=a[6]=a[7]=a[8]=a[9]=0;
 scanb=scan;
 scan=4;
 redraw[scanb]=1;
 setcolor(background);
 line(x2,y2,x1,y1);
 }
 if(a[4]==1)
  {
  setcolor(background);
  line(a4,b4,x1,y1);
  x1=x,y1=y;
  setcolor(col_line);
  line(a4,b4,x,y);
  x2=a4,y2=b4;
  }
 if(redraw[5]==0&&pow((x-a5),2)+ pow((y-b5),2)<400) //fifth circle
 {
 if(scan==0)
  x2=a5,y2=b5;
 a[5]=1;
 a[1]=a[2]=a[3]=a[4]=a[6]=a[7]=a[8]=a[9]=0;
 scanb=scan;
 scan=5;
 redraw[scanb]=1;
 setcolor(background);
 line(x2,y2,x1,y1);
 }
 if(a[5]==1)
  {
  setcolor(background);
  line(a5,b5,x1,y1);
  x1=x,y1=y;
  setcolor(col_line);
  line(a5,b5,x,y);
  x2=a5,y2=b5;
  }
 if(redraw[6]==0&&pow((x-a6),2)+ pow((y-b6),2)<400) //sixth circle
 {
 if(scan==0)
  x2=a6,y2=b6;
 a[6]=1;
 a[1]=a[2]=a[3]=a[4]=a[5]=a[7]=a[8]=a[9]=0;
 scanb=scan;
 scan=6;
 redraw[scanb]=1;
 setcolor(background);
 line(x2,y2,x1,y1);
 }
 if(a[6]==1)
  {
  setcolor(background);
  line(a6,b6,x1,y1);
  x1=x,y1=y;
  setcolor(col_line);
  line(a6,b6,x,y);
  x2=a6,y2=b6;
  }
 if(redraw[7]==0&&pow((x-a7),2)+ pow((y-b7),2)<400) //seventh circle
 {
 if(scan==0)
  x2=a7,y2=b7;
 a[7]=1;
 a[1]=a[2]=a[3]=a[4]=a[5]=a[6]=a[8]=a[9]=0;
 scanb=scan;
 scan=7;
 redraw[scanb]=1;
 setcolor(background);
 line(x2,y2,x1,y1);
 }
 if(a[7]==1)
  {
  setcolor(background);
  line(a7,b7,x1,y1);
  x1=x,y1=y;
  setcolor(col_line);
  line(a7,b7,x,y);
  x2=a7,y2=b7;
  }
 if(redraw[8]==0&&pow((x-a8),2)+ pow((y-b8),2)<400) //eight circle
 {
 if(scan==0)
  x2=a8,y2=b8;
 a[8]=1;
 a[1]=a[2]=a[3]=a[4]=a[5]=a[6]=a[7]=a[9]=0;
 scanb=scan;
 scan=8;
 redraw[scanb]=1;
 setcolor(background);
 line(x2,y2,x1,y1);
 }
 if(a[8]==1)
  {
  setcolor(background);
  line(a8,b8,x1,y1);
  x1=x,y1=y;
  setcolor(col_line);
  line(a8,b8,x,y);
  x2=a8,y2=b8;
  }
 if(redraw[9]==0&&pow((x-a9),2)+ pow((y-b9),2)<400) //ninth circle
 {
 if(scan==0)
  x2=a9,y2=b9;
 a[9]=1;
 a[1]=a[2]=a[3]=a[4]=a[5]=a[6]=a[7]=a[8]=0;
 scanb=scan;
 scan=9;
 redraw[scanb]=1;
 setcolor(background);
 line(x2,y2,x1,y1);
 }
 if(a[9]==1)
  {
  setcolor(background);
  line(a9,b9,x1,y1);
  x1=x,y1=y;
  setcolor(col_line);
  line(a9,b9,x,y);
  x2=a9,y2=b9;
  }
}
else
{
 a[1]=a[2]=a[3]=a[4]=a[5]=a[6]=a[7]=a[8]=a[9]=0;
 x1=y1=0;
 int wrong=scan; //for cheking password is wrong
 scanb=scan=0;
 for(int i=0;i<10;i++)
  {redraw[i]=0;}
 for(int i1=0;i1<18;i1++)
  {line_poly[i1]=0,pol=0;} //above all lines for re enter password
 if(clear==1) //if release mouse clear graphic
  {
  setfillstyle(1,background); //change color value to hide abstraction
  bar(0,0,getmaxx(),getmaxy());
  clear=0;
  }
for(int i2=1;i2<18;i2+=2) //matching password
{
 if(check[i2]==defalt[i2])
 password=10;
 else
 {
 password=0;
  if(wrong!=0&&layer2==0)
  {
  wtime=0; //restart wtime
  count_password++;
  setcolor(4);
  settextjustify(1,1);
  outtextxy(320,190,"WRONG PATTERN");
  }
 goto ASD;
 }
} //if all entities(i1) are match then password=10

ASD: //if any one (out of 18) mismatch thenn password=0
if(password==10) //if all entities matched
 {
 a1=a2=a3=a4=a5=a6=a7=a8=a9=-1000;
 b1=b2=b3=b4=b5=b6=b7=b8=b9=-1000; //circles coordinates are -1000
 setfillstyle(1,background);
 bar(0,0,getmaxx(),getmaxy());
 LAYER2:
 layer2=layer2_password_right();
 if(layer2==10) //if click on lock in layer2
 {
 layer2=0;
 goto START;
 }
 if(layer2==11) //if click on change in layer2
 {goto START;}
 }
if(layer2==11&&wrong!=0)   //for change password
 {
 layer2=0;
 count_password=0;
 for(int a=1;a<18;a+=2)
 defalt[a]=check[a];
 goto LAYER2;
 }
if(count_password==3) //if password wrong three times
 {
 bar1=1;
 count_password=0;
 wtime=300;
 }
for(int ii=0;ii<=18;ii++) //for reset password
 {check[ii]=0;}
 m=0;
} //end else

if(wtime==300) //clear word"WRONG PASSWORD"
 {
 setcolor(background);
 settextjustify(1,1);
 outtextxy(320,190,"WRONG PATTERN");
 }
wtime++;
delay(1);
} //end while loop
} //end main