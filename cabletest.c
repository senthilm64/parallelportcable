#include<stdio.h>
#include<sys/io.h>
#include<signal.h>
#define BASE 0x378

int running=1;

void signalhandler(int sig)
{
running=0;
}

int main(void)
{
printf("pp_interface test 0x%x\n",BASE);
signal(SIGINT,signalhandler);
int ret=ioperm(BASE,4,1);
if(ret!=0)
{
printf("Error:could not set permission on ports\n");
return ret;
}
while(running)
{
outb(0xFF,BASE);
outb(0x00,BASE);
}
ret=ioperm(BASE,4,0);
if(ret!=0)
{
printf("Error:could not clear permission on ports\n");
return ret;
}
return 0;
}