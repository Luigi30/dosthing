#include "mouse.hpp"

int isMouseAttached(){
    //INT 33h, AH=00h - reset mouse if attached.
    //out AX = 0x0000 if no mouse, 0xFFFF if mouse
    //out BX = number of buttons detected
    
    union REGS regs;
    regs.w.ax = 0x0000;
    int386(0x33, &regs, &regs);

    return (regs.w.ax == 0xFFFF);
}

void cursorEnable(){
    //INT 33h, AH=01h - enable cursor
    union REGS regs;
    regs.w.ax = 0x0001;
    int386(0x33, &regs, &regs);
}

void cursorDisable(){
    //INT 33h, AH=02h - disable
    union REGS regs;
    regs.w.ax = 0x0002;
    int386(0x33, &regs, &regs);
}