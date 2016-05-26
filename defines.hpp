#ifndef GLOBALVARS_HPP
#define GLOBALVARS_HPP

//VGA
#define VGA_MEMORY 0xA000
#define VGA_LINEAR_ADDRESS ((VGA_MEMORY) << 4)
#define VGA_HEIGHT 200
#define VGA_WIDTH 320
#define VGA_SIZE (VGA_HEIGHT * VGA_WIDTH)

//Timer
#define TICKS_PER_SECOND 240
#define TICKS_PER_FRAME (TICKS_PER_SECOND / 60)

//Debug output
void debugOutput(char *str, int len){
    for(int i=0;i<len;i++){
        outp(0x3F8, str[i]);
        delay(1);
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

#endif

