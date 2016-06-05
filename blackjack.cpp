#include "blackjack.hpp"

W_Button buttons[16];
int widgetCount = 0;
int lmbDown = false;
Widget *clickedWidget;
std::string clickingOnWidgetName;

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
    //reset deck between hands
    deck = Deck();
    
    g_screen.layer_text.putString("Deal!", strlen("Deal!"), TEXTCELL(0, 3), COLOR_WHITE, FONT_6x8);
    Card card1 = deck.getRandomCard();  
    char strCard[32];
    sprintf(strCard, "Drew %c%c", card1.getRank(), card1.getSuit());
    g_screen.layer_text.putString(strCard, strlen(strCard), TEXTCELL(0, 4), COLOR_WHITE, FONT_6x8);

    Card card2 = deck.getRandomCard();  
    sprintf(strCard, "Drew %c%c", card2.getRank(), card2.getSuit());
    g_screen.layer_text.putString(strCard, strlen(strCard), TEXTCELL(0, 5), COLOR_WHITE, FONT_6x8);

    g_screen.widgetsList.push_back(new W_Card_Graphic("card1", Point(40, 60), card1.getRank(), card1.getSuit()));
    g_screen.widgetsList.push_back(new W_Card_Graphic("card2", Point(95, 60), card2.getRank(), card2.getSuit()));
}

void blackjack(){
    //Entry point for blackjack game.
     
    //reset the framebuffers
    g_screen.init_framebuffers();

    char str[32] = "Now we need buttons!";
    g_screen.layer_text.putString(str, strlen(str), TEXTCELL(0, 0), COLOR_WHITE, FONT_6x8);

    g_screen.widgetsList.push_back(new W_Button("buttonDeal", Point(20, 160), BUTTON_SHAPE_RECT, Size2D(40, 20), "Deal"));
    g_screen.widgetsList.push_back(new W_Button("buttonExit", Point(260, 160), BUTTON_SHAPE_RECT, Size2D(40, 20), "Exit"));

    cursorEnable();

    g_screen.redraw();

    while(true){
        while(!timer24Hz){
            //wait for 24Hz timer to fire
        }

        MouseData mouseData = getMouseData();

        if(!lmbDown && mouseData.lmb_click){
            
            //clicking the mouse on a widget
            lmbDown = true;
            char clicked[32];
            clickedWidget = g_screen.getClickedWidget(Point(mouseData.x, mouseData.y));
            clickingOnWidgetName = clickedWidget->getName();

            //is this a button?
            W_Button* btn = dynamic_cast<W_Button*>(clickedWidget);
            if(btn != NULL){
                btn->isDown = true;
            };

            g_screen.redraw();
            
        }
        else if(lmbDown && !mouseData.lmb_click && clickingOnWidgetName == g_screen.getClickedWidget(Point(mouseData.x, mouseData.y))->getName()) {
            //released the mouse on the same widget so process our click
            if(clickingOnWidgetName == "buttonExit") exit_program("Returning to DOS...");
            else if(clickingOnWidgetName == "buttonDeal") dealHand();
            lmbDown = 0;

            //is this a button?
            W_Button* btn = dynamic_cast<W_Button*>(clickedWidget);
            if(btn != NULL){
                btn->isDown = false;
            };
            
            g_screen.redraw();
            
        }

        /*
        int key = keyInBuffer();
        if(key == 0x1B) {
            exit_program("Returning to DOS...");
        }
        */
    }
}
