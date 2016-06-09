/* A deck of cards. */

#ifndef DECK_HPP
#define DECK_HPP

#include <cstdlib>
#include <vector>
#include "card.hpp"

class Deck {
    std::vector<Card> availableCards;
    Card popCard(int);

    public:
    Deck();
    Card getRandomCard();
};

#endif
