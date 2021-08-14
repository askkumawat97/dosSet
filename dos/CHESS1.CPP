#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<stdlib.h>

struct REGS i, o;

int i1, i2;
int boundstart = 50;
int boundsize = 400;
int blocksize;
int selectedbox;
int pcordx, pcx, pcordy, pcy, pnum, pxpart, pypart;
int blackpiece[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
int whitepiece[16] = {57,58,59,60,61,62,63,64,49,50,51,52,53,54,55,56};
/*
int brookl=1, bhorsel=2, bbishopl=3, bqueen=4, bking=5;
int brookr=8, bhorser=7, bbishopr=6;
int bpawn1=9, bpawn2=10 , bpawn3=11, bpawn4=12;
int bpawn5=13, bpawn6=14, bpawn7=15, bpawn8=16;
int wrookl=57, whorsel=58, wbishopl=59, wqueen=60, wking=61;
int wrookr=64, whorser=63, wbishopr=62;
int wpawn1=49, wpawn2=50, wpawn3=51, wpawn4=52;
int wpawn5=53, wpawn6=54, wpawn7=55, wpawn8=56;
*/

getkey() {
i.h.ah = 0;
int86(22, &i, &o);
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

getmousepos(int *button,int *bx,int *by)
{
i.x.ax=3;
int86(0x33,&i,&o);
*button=o.x.bx;
*bx=o.x.cx;
*by=o.x.dx;
}


drawpieces() {
//value of piece is 0 means it is out
blocksize = boundsize / 8;
pxpart = blocksize / 4;
pypart = blocksize / 8;
for(i2 = 0; i2 < 2; i2++) //i2 works for color
for(i1 = 0; i1 < 16; i1++) { //i1 works for pieces
  if(i2 == 0) pnum = blackpiece[i1];
  if(i2 == 1) pnum = whitepiece[i1];
  pcx = boundstart + blocksize * ((pnum-1)%8);
  pcy = boundstart + blocksize * ((pnum-1)/8);
  rectangle(pcx+pxpart*1, pcy+pypart*6.3, pcx+pxpart*3, pcy+pypart*7.3);
  if(i1 == 4 || i1 == 60) { //king
    circle(pcx+pxpart*2, pcy+pypart*3, pypart);
    line(pcx+pxpart*1.7, pcy+pypart*4.0, pcx+pxpart*1.4, pcy+pypart*6.3);
    line(pcx+pxpart*2.4, pcy+pypart*4.0, pcx+pxpart*2.6, pcy+pypart*6.3);
    line(pcx+pxpart*2.0, pcy+pypart*1.0, pcx+pxpart*2.0, pcy+pypart*2.0);
    line(pcx+pxpart*1.7, pcy+pypart*1.5, pcx+pxpart*2.4, pcy+pypart*1.5);
  }
  if(i1 == 3 || i1 == 59) { //queen

  }
  if(i1 == 0 || i1 == 7 || i1 == 56 || i1 == 63) { //rook

  }
  if(i1 == 1 || i1 == 6 || i1 == 57 || i1 == 62) { //horse

  }
  if(i1 == 2 || i1 == 5 || i1 == 58 || i1 == 61) { //bishop

  }
  if((i1 > 7 && i1 < 16) || (i1 > 47 && i1 < 56)) { //pawn

  }
}
}

void main() {
int gd = DETECT, gm;
initgraph(&gd, &gm, "c:\\turboc3\\bgi");
i.h.ah = 0;
int button, buttonx, buttony, key;



showmouseptr();

while(1) {
if(kbhit()) {
  int86(22, &i, &o);
  key = o.h.ah;
  if(key == 1) {
    closegraph();
    exit(0);
  }
}


blocksize = boundsize / 8;

for(i1 = 0; i1 < 9; i1++) {
  line(boundstart, boundstart+blocksize*i1, boundstart+boundsize, boundstart+blocksize*i1);
  line(boundstart+blocksize*i1, boundstart, boundstart+blocksize*i1, boundstart+boundsize);
}

drawpieces();

/*
rectangle(boundstart, boundstart, boundstart+boundsize, boundstart+boundsize);
for(i1 = 0, i2 = 0; i2 < 8; i1 += 2) {
  setfillstyle(SOLID_FILL, 15);
  bar(boundstart+i1*blocksize, boundstart+i2*blocksize, \
  boundstart+(i1+1)*blocksize-1, boundstart+(i2+1)*blocksize-1);
  if(i1 > 5) {
    i1 = 5 - i1;
    i2++;
  }
}
*/





delay(100);
}
}