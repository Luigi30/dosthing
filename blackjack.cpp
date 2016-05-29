#include "blackjack.hpp"

W_Button buttons[16];
int widgetCount = 0;

int keyInBuffer(){
    union REGS regs;
    regs.h.ah = 0x01;
    int386(0x16, &regs, &regs);

    if(regs.h.al){
        regs.h.ah = 0x00;
        int386(0x16, &regs, &regs);
        return regs.h.al;
    }

    return 0x00;
}

void exit_program(std::string msg) {
    _setvideomode(_DEFAULTMODE);
    printf(msg.c_str());
    exit(0);
}

void blackjack(){
    //Entry point for blackjack game.
    
    //reset the framebuffers
    g_screen.init_framebuffers();

    char str[32] = "Now we need buttons!";
    g_screen.layer_text.putString(str, strlen(str), TEXTCELL(0, 0), COLOR_WHITE, FONT_6x8);

    Button btn = Button(Point(40, 160), 40, 20, "Deal");
    g_screen.addButton(btn);

    cursorEnable();

    while(true){
        while(!timer24Hz){
            //wait for 24Hz timer to fire
        }
        
        int key = keyInBuffer();
        if(key) {
            if(key == 0x1B) {
                exit_program("Returning to DOS...");
            }
        }

        g_screen.redraw();
    }
}
