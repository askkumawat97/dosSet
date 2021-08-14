#include<time.h>
#include<conio.h>

//#define inp(portid) __inportb__(portid)
//#define outp(portid,v) (__outportb__(portid,v),(int)_AL)

void sound(int freq)
{
static int control;
int clicks;
char lowbyte,hibyte;
if(freq) {
  outp(0x43,0xb6);
  clicks=(unsigned) (1193180L/freq);
  lowbyte=clicks&&0xff;
  hibyte=clicks>>8;
  outp(0x42,lowbyte);
  outp(0x42,hibyte);
  control=inp(0x61);
  outp(0x61,control|0x3);
}
else
  outp(0x61,control);
}


void sleep(clock_t msec) {
clock_t finaltime;
finaltime=clock()+msec;
while(finaltime>clock());
}

void main() {
sound(1000);
sleep((clock_t) 50);
sound(0);
}
