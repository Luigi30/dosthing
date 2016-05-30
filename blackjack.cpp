#include "blackjack.hpp"

W_Button buttons[16];
int widgetCount = 0;
int lmbDown = false;

Deck deck;

int keyInBuffer(){
    union REGS regs;
    regs.h.ah = 0x01;
    int386(0x16, &regs, &regs);
    
    if(regs.w.ax > 0x0000){
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

void dealHand(){
    g_screen.layer_text.putString("Deal!", strlen("Deal!"), TEXTCELL(0, 3), COLOR_WHITE, FONT_6x8);
    Card card = deck.getRandomCard();
    char strCard[32];
    sprintf(strCard, "Drew %c%c", card.getRank(), card.getSuit());
    g_screen.layer_text.putString(strCard, strlen(strCard), TEXTCELL(0, 4), COLOR_WHITE, FONT_6x8);
}

void blackjack(){
    //Entry point for blackjack game.
    deck = Deck();
    
    //reset the framebuffers
    g_screen.init_framebuffers();

    char str[32] = "Now we need buttons!";
    g_screen.layer_text.putString(str, strlen(str), TEXTCELL(0, 0), COLOR_WHITE, FONT_6x8);

    g_screen.widgetsList.push_back(new W_Button("buttonDeal", Point(20, 160), BUTTON_SHAPE_RECT, 40, 20, "Deal"));
    g_screen.widgetsList.push_back(new W_Button("buttonExit", Point(260, 160), BUTTON_SHAPE_RECT, 40, 20, "Exit"));

    cursorEnable();

    g_screen.redraw();

    while(true){
        while(!timer24Hz){
            //wait for 24Hz timer to fire
        }

        MouseData mouseData = getMouseData();

        if(!lmbDown && mouseData.lmb_click){
            lmbDown = true;
            char clicked[32];
            std::string clickedWidgetName = g_screen.getClickedWidget(Point(mouseData.x, mouseData.y));

                 if(clickedWidgetName == "buttonExit") exit_program("Returning to DOS...");
            else if(clickedWidgetName == "buttonDeal") dealHand();

            g_screen.redraw();
        }

        if(lmbDown && !mouseData.lmb_click) lmbDown = 0;

        /*
        int key = keyInBuffer();
        if(key == 0x1B) {
            exit_program("Returning to DOS...");
        }
        */
    }
}
