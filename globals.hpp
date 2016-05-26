// GLOBALS.H
//
// Global Include file

//#if !defined( GLOBALS_H )
//#define GLOBALS_H

#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <vector>

#include "mouse.hpp"
#include "colors.hpp"
#include "fonts\font.hpp"
#include "shapes\point.hpp"
#include "shapes\shapes.hpp"
#include "scorched.hpp"

double PI = 3.14159265;

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

//VGA
#define VGA_MEMORY 0xA000
#define VGA_LINEAR_ADDRESS ((VGA_MEMORY) << 4)
#define VGA_HEIGHT 200
#define VGA_WIDTH 320
#define VGA_SIZE (VGA_HEIGHT * VGA_WIDTH)

#define TICKS_PER_SECOND 240
#define TICKS_PER_FRAME (TICKS_PER_SECOND / 60)

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

//Global data
char messages[64][4];
std::vector<Shape> shapesList;

//Debug output
void debugOutput(char *str, int len){
    for(int i=0;i<len;i++){
        outp(0x3F8, str[i]);
        delay(1);
    }
}

#define DEBUG(X) debugOutput(X, strlen(X));

#endif
