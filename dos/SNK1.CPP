#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<dos.h>

struct REGS i, o;

getkey() {
  i.h.ah = 0;
  int86(22, &i, &o);
  return(o.h.ah);
}

void main()
{
int gd = DETECT, gm;
initgraph(&gd, &gm, "c:\\turboc3\\bgi");
int key, i, a1, a2;
int speed = 500;
int dir = 2;
int dirc=0;
int blocksize = 20;
int boundx = 0, boundy = 20;
int boundxs = 600, boundys = 400;

int snksize = 4;
int totalbox = (boundxs / blocksize) * (boundys / blocksize);
int snkbox[600];
for(i = 0; i < totalbox; i++) {
  snkbox[i] = i;
}
snkbox[0] = 4;
snkbox[1] = 3;
snkbox[2] = 2;
snkbox[3] = 1;

int point;
int pointstat = 0;
int pointx, pointy;
//int pointbox[600];


while(1) {
if(kbhit()) {
  key = getkey();
  if(key == 1) {
    closegraph();
    exit(0);
  }
  if(key == 75 && dirc == 1) {dir = 1, dirc = 0;}
  if(key == 77 && dirc == 1) {dir = 2, dirc = 0;}
  if(key == 72 && dirc == 0) {dir = 3, dirc = 1;}
  if(key == 80 && dirc == 0) {dir = 4, dirc = 1;}
}

clearviewport();

for(i = 0; i < snksize-1; i++) {
  snkbox[snksize-i-1] = snkbox[snksize-i-2];
}
if(dir == 1) {
  snkbox[0] = snkbox[0] - 1;
}
if(dir == 2) snkbox[0] = snkbox[0] + 1;
if(dir == 3) snkbox[0] = snkbox[0] - (boundxs / blocksize);
if(dir == 4) snkbox[0] = snkbox[0] + (boundxs / blocksize);
for(i = 0; i < snksize; i++) {
  a1 = boundx + blocksize * (snkbox[i] % (boundxs / blocksize));
  a2 = boundy + blocksize * (snkbox[i] / (boundxs / blocksize));
  rectangle(a1, a2, a1 + blocksize, a2 + blocksize);
 printf("%d-",snkbox[i]);
}

for(i = 0; i < snksize; i++) {
  if(snkbox[0] == snkbox[i+1]) {
  delay(3000);
    closegraph();
    exit(0);
  }
}

if(point == snkbox[0]) {
  pointstat = 0;
  snksize++;
}
if(pointstat == 0) {
  point = snkbox[snksize + random(totalbox - snksize)];
  pointx = boundx + blocksize * (point % (boundxs / blocksize));
  pointy = boundy + blocksize * (point / (boundxs / blocksize));
}
pointstat = 1;
rectangle(pointx, pointy, pointx + blocksize, pointy + blocksize);



delay(speed);
}
}