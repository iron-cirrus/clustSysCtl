#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>
#include <wiringPi.h>


#define DRIVE_UNSET -1
#define DRIVE_LOW    0
#define DRIVE_HIGH   1

#define PULL_UNSET  -1
#define PULL_NONE    0
#define PULL_DOWN    1
#define PULL_UP      2

#define FUNC_UNSET  -1
#define FUNC_IP      0
#define FUNC_OP      1
#define FUNC_A0      4
#define FUNC_A1      5
#define FUNC_A2      6
#define FUNC_A3      7
#define FUNC_A4      3
#define FUNC_A5      2

#define GPIO_MIN     0
#define GPIO_MAX     53

static const int gpio_Pods[4] =
{
	22,25,3,7
};

void print_help()
{
    char *name = "PodCtl"; /* in case we want to rename */
    printf("\n");
    printf("WARNING! %s set writes directly to the GPIO control registers\n", name);
    printf("ignoring whatever else may be using them (such as Linux drivers) -\n");
    printf("it is designed as a debug tool, only use it if you know what you\n");
    printf("are doing and at your own risk!\n");
    printf("\n");
}

int _PodCtl(char *Etat)
{
    int n; 
    for (n = 0; n < 4 ; n++)  {
        if(Etat[n]=='1') {
            digitalWrite(gpio_Pods[n],HIGH) ;
            //printf("ON %d GPIO:%d\n",n,gpio_Pods[n]);
        } else {
            //printf("OFF %d GPIO:%d\n",n,gpio_Pods[n]);
            digitalWrite(gpio_Pods[n],LOW) ;
        }
    }

    return 1;
}

int main(int argc, char *argv[])
{
    int mSec=0;
    char choixPod[4]="    ";


    wiringPiSetup();
    pinMode(7,OUTPUT);
    pinMode(3,OUTPUT);
    pinMode(22,OUTPUT);
    pinMode(25,OUTPUT);

    if (argc < 2)  {
        printf("No arguments given - try \"PodCtl help\"\n");
        return 0;
    }

    if (strcmp(argv[1], "help") == 0)  {
        print_help();
        return 0;
    } else if (strcmp(argv[1], "on") == 0) {
	for(int a=1; a<argc;a++) digitalWrite(gpio_Pods[atoi(argv[a])-1],HIGH) ;
    } else if (strcmp(argv[1], "off") == 0) {
        for(int a=1; a<argc;a++) digitalWrite(gpio_Pods[atoi(argv[a])-1],LOW) ;
    } else if (strcmp(argv[1], "ipl") == 0)  {
        if(argc>2) mSec=atoi(argv[2]);
        if(mSec<2500) mSec=2500;
        _PodCtl("1000");
        delay(mSec);
        _PodCtl("1100");
        delay(mSec);
        _PodCtl("1110");
        delay(mSec);
        _PodCtl("1111");
        return 0;
    } else  if (argc == 2 && strlen(argv[1])>1) { // cas 0101
        strncpy(choixPod,argv[1],4);
        _PodCtl(choixPod);
    }

    return 0;
}
