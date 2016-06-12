/* A big mess of defines that need to be reorganized. */

#ifndef GLOBALVARS_HPP
#define GLOBALVARS_HPP

#include <conio.h>
#include <i86.h>

#include "colors.hpp"

double PI = 3.14159265;

//VGA
#define VGA_MEMORY 0xA000
#define VGA_LINEAR_ADDRESS ((VGA_MEMORY) << 4)
#define VGA_HEIGHT 200
#define VGA_WIDTH 320
#define VGA_SIZE (VGA_HEIGHT * VGA_WIDTH)
int VGA_Y_OFFSETS[VGA_HEIGHT];

//Timer
#define TICKS_PER_SECOND 240
#define TICKS_PER_FRAME (TICKS_PER_SECOND / 60)

//Debug output
void debugOutput(char *str, int len){
    for(int i=0;i<len;i++){
        outp(0x3F8, str[i]); //COM1
    }
}

#define DEBUG(X) debugOutput(X, strlen(X));
#define TEXTCELL(X,Y) Point(X, Y*8)

//char *framebuffers[2];
char *VGA_PTR;

//Timers
void __interrupt __far timerHandler();
void (__interrupt __far *biosTimerHandler)();
volatile unsigned long biosClockTicks;
unsigned long timerReload;
volatile unsigned long myTimerTicks;
volatile unsigned int timer60Hz;
volatile unsigned int timer24Hz;

//Button shape
enum ButtonShape { BUTTON_SHAPE_RECT, BUTTON_SHAPE_ROUNDRECT };

/******** Common Type Definitons ********/
// unsigned types
typedef unsigned char         Byte;
typedef unsigned short        UInt16;
typedef unsigned long         UInt32;
typedef unsigned long long    UInt64;
// signed types
typedef signed char           SByte;
typedef signed short          Int16;
typedef signed long           Int32;
typedef signed long long      Int64;
#endif

