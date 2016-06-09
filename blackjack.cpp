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
    //Deal a hand.

    deck = Deck(); //reset deck between hands

    //delete the existing card widgets
    for(int i=0;i<6;i++){
        g_screen.removeWidget("playerCard" + (i + 0x30));
        g_screen.removeWidget("dealerCard" + (i + 0x30));
    }

    //reset the player's hand and add the new card widgets to the screen
    playerHand.clear();
    playerHand.addCard(deck.getRandomCard());
    playerHand.addCard(deck.getRandomCard());

    g_screen.widgetsList.push_back(new W_Card_Graphic("playerCard1", PLAYER_CARD_START_POSITION, playerHand.getCards()[0]));
    g_screen.widgetsList.push_back(new W_Card_Graphic("playerCard2", PLAYER_CARD_START_POSITION + CARD_INTERVAL, playerHand.getCards()[1]));

    //reset the dealer's hand and add the new card widgets to the screen
    dealerHand.clear();
    dealerHand.addCard(deck.getRandomCard());
    dealerHand.addCard(deck.getRandomCard());

    g_screen.widgetsList.push_back(new W_Card_Graphic("dealerCard1", DEALER_CARD_START_POSITION, dealerHand.getCards()[0]));
    g_screen.widgetsList.push_back(new W_Card_Graphic("dealerCard2", DEALER_CARD_START_POSITION + CARD_INTERVAL, dealerHand.getCards()[1]));        
}

void playerHit(){
    //The player hit...
    playerHand.addCard(deck.getRandomCard());
    int numCards = playerHand.numCards();
    char str[4];
    itoa(numCards, str, 10);
    
    std::string widgetName = "playerCard" + std::string(str);
    Point cardPosition = PLAYER_CARD_START_POSITION;

    for(int i=0;i<numCards-1;i++){
        cardPosition = cardPosition + CARD_INTERVAL;
    }
    
    g_screen.widgetsList.push_back(new W_Card_Graphic(widgetName, cardPosition, playerHand.getCards()[numCards-1]));
}

void dealerHit(){
    ///The dealer hit...
    dealerHand.addCard(deck.getRandomCard());
    int numCards = dealerHand.numCards();
    char str[4];
    itoa(numCards, str, 10);
    
    std::string widgetName = "dealerCard" + std::string(str);
    Point cardPosition = DEALER_CARD_START_POSITION;

    for(int i=0;i<numCards-1;i++){
        cardPosition = cardPosition + CARD_INTERVAL;
    }
    
    g_screen.widgetsList.push_back(new W_Card_Graphic(widgetName, cardPosition, dealerHand.getCards()[numCards-1]));   
}

//What was the result of the hand?
void playerWins(){
    g_screen.layer_text.putString("PLAYER WINS! ", strlen("PLAYER WINS! "), TEXTCELL(40, 18), COLOR_WHITE, FONT_6x8);
}
void playerLoses(){
    g_screen.layer_text.putString("PLAYER LOSES!", strlen("PLAYER LOSES!"), TEXTCELL(40, 18), COLOR_WHITE, FONT_6x8);
}
void playerPushes(){
    g_screen.layer_text.putString("PLAYER PUSHED", strlen("PLAYER PUSHED"), TEXTCELL(40, 18), COLOR_WHITE, FONT_6x8);
}

void doGameAction(std::string widgetClicked){
    //Blackjack game logic function.

    //always enable the exit widget
    if(clickingOnWidgetName == "buttonExit") exit_program("Returning to DOS...");

    if(GAME_STATE == HAND_ENDED){
        //Active: buttonDeal
        if(clickingOnWidgetName == "buttonDeal") {
            dealHand();
            
            g_screen.removeWidget("buttonDeal");
            g_screen.widgetsList.push_back(new W_Button("buttonHit",   Point(65, 160),  BUTTON_SHAPE_RECT, Size2D(40, 20), "Hit"));
            g_screen.widgetsList.push_back(new W_Button("buttonStand", Point(110, 160), BUTTON_SHAPE_RECT, Size2D(40, 20), "Stand"));
            g_screen.layer_text.putString("PLAYER      ", strlen("PLAYER      "), TEXTCELL(40, 18), COLOR_WHITE, FONT_6x8);
            GAME_STATE = PLAYER_TAKING_ACTION;
        }
    } else if(GAME_STATE == PLAYER_TAKING_ACTION) {
        //Active: buttonHit and buttonStand

        if(clickingOnWidgetName == "buttonHit") {
            playerHit();
            if(playerHand.getTotal() > 21){
                GAME_STATE = HAND_ENDED;
                playerLoses();
                g_screen.removeWidget("buttonHit");
                g_screen.removeWidget("buttonStand");
                g_screen.widgetsList.push_back(new W_Button("buttonDeal", Point(20, 160), BUTTON_SHAPE_RECT, Size2D(40, 20), "Deal"));
            }
        } else if(clickingOnWidgetName == "buttonStand") {
            if(dealerHand.getTotal() < 17){
                dealerHit();
            }

            if(dealerHand.getTotal() > 21 || playerHand.getTotal() > dealerHand.getTotal()) {
                playerWins();
            } else if(dealerHand.getTotal() > playerHand.getTotal()) {
                playerLoses();
            } else if(dealerHand.getTotal() == playerHand.getTotal()) {
                playerPushes();
            } else {
                g_screen.layer_text.putString("PLAYER ERROR?", strlen("PLAYER ERROR?"), TEXTCELL(40, 18), COLOR_WHITE, FONT_6x8);
            }
                        
            GAME_STATE = HAND_ENDED;
            g_screen.widgetsList.push_back(new W_Button("buttonDeal", Point(20, 160), BUTTON_SHAPE_RECT, Size2D(40, 20), "Deal"));
        }
    }

}

void blackjack(){
    //Entry point for blackjack game.

    //reset the game state
    GAME_STATE = HAND_ENDED;

    //load the PCX files
    W_Card_Graphic::loadGraphics();
     
    //reset the framebuffers
    g_screen.init_framebuffers();

    //Add the deal and exit button
    g_screen.widgetsList.push_back(new W_Button("buttonDeal", Point(20, 160), BUTTON_SHAPE_RECT, Size2D(40, 20), "Deal"));
    g_screen.widgetsList.push_back(new W_Button("buttonExit", Point(260, 160), BUTTON_SHAPE_RECT, Size2D(40, 20), "Exit"));

    //Enable the cursor
    Mouse::cursorEnable();

    g_screen.redraw();

    while(true){
        while(!timer24Hz){
            //wait for 24Hz timer to fire
        }           

        MouseData mouseData = Mouse::getMouseData();

        if(mouseData.lmb_click){
            
            //clicking the mouse on a widget
            clickedWidget = g_screen.getClickedWidget(Point(mouseData.x, mouseData.y));
            if(clickedWidget != NULL){
                clickingOnWidgetName = clickedWidget->getName();

                //is this a button?
                W_Button* btn = dynamic_cast<W_Button*>(clickedWidget);
                if(btn != NULL){
                    btn->isDown = true;
                };
            }

            g_screen.redraw();
            
        }
        else if(!mouseData.lmb_click && clickingOnWidgetName == g_screen.getClickedWidgetName(Point(mouseData.x, mouseData.y))) {
            //released the mouse on the same widget so process our click

            doGameAction(clickingOnWidgetName);

            if(clickedWidget != NULL) {
                //is this a button?
                W_Button* btn = dynamic_cast<W_Button*>(clickedWidget);
                if(btn != NULL){
                    btn->isDown = false;
                };
            }

            clickingOnWidgetName = "";
            
            g_screen.redraw();
            
        } else if(!mouseData.lmb_click) {
            clickingOnWidgetName = "";
        }

        /*
        int key = keyInBuffer();
        if(key == 0x1B) {
            exit_program("Returning to DOS...");
        }
        */
    }
}
