#define MOUSE_INTERRUPT 0x33

#include <i86.h>

struct MouseData {
    int lmb_click;
    int rmb_click;
    int x;
    int y;    
};

int isMouseAttached();
void cursorEnable();
void cursorDisable();
MouseData getMouseData();
