/* Blackjack routines and hardcoded variable junk. */

#ifndef BLACKJACK_HPP
#define BLACKJACK_HPP

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <graph.h>
#include <dos.h>
#include <fcntl.h>
#include <io.h>

#include "globals.hpp"
#include "defines.hpp"
#include "framebuffer.hpp"
#include "mouse.hpp"
#include "fonts\font.hpp"
#include "widgets\button.hpp"
#include "widgets\cardgfx.hpp"

#include "bjack\deck.hpp"
#include "bjack\hand.hpp"

enum BLACKJACK_GAME_STATE { HAND_ENDED, PLAYER_TAKING_ACTION, DEALER_TAKING_ACTION, FINDING_WINNER };

Hand playerHand;
Hand dealerHand;
BLACKJACK_GAME_STATE GAME_STATE;

void blackjack();
void doGameAction(std::string widgetClicked);

//Graphical constants
Point PLAYER_CARD_START_POSITION = Point(40,60);
Point DEALER_CARD_START_POSITION = Point(205,60);
//Point CARD_INTERVAL = Point(55,0); //card position = CARD_START_POSITION + (CARD_INTERVAL * cardNumber)
Point CARD_INTERVAL = Point(15,5); //Diagonal

#endif
