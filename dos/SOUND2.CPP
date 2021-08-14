#include<stdio.h>
#include<time.h>
#include<conio.h>

void main()
{
int freq=1000;
static int control;
int clicks;
char lowbyte,hibyte;
clrscr();

  outp(67,182);
  clicks=(unsigned) (1193180L/freq);
  lowbyte=clicks&&0xff;
  hibyte=clicks>>8;
  outp(66,lowbyte);
  outp(66,hibyte);
  control=inp(97);
  outp(97,control|3);
  printf("%d",control);

clock_t finaltime;
finaltime=clock()+10;
while(finaltime>clock());
`printf("%f",finaltime);

//outp(97,control);
outp(97,0);
}
