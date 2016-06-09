/* A hand of playing cards. */

#ifndef HAND_HPP
#define HAND_HPP

#include <vector>
#include "card.hpp"

class Hand {
    std::vector<Card> cards;
    
    public:
    void clear();
    std::vector<Card> getCards();
    void addCard(Card card);
    int numCards() { return cards.size(); };
    int getTotal();
};

#endif HAND_HPP