#include "hand.hpp"

std::vector<Card> Hand::getCards(){
    return cards;
}

void Hand::clear(){
    cards.clear();
}

void Hand::addCard(Card card){
    cards.push_back(card);
}

int Hand::getTotal(){
    int total = 0;
    int numAces = 0;
    
    for(int i=0;i<numCards();i++){
        int rank = Card::rankCharToInt(cards[i].getRank());
        if(rank == 1) numAces++; //this is an ace
        else if(rank >= 2 && rank <= 10) total = total + rank;
        else if(rank >= 11 && rank <= 13) total = total + 10;
    }

    for(int i=0;i<numAces;i++){
        if(total + 11 > 21) {
            total = total + 1;
        } else {
            total = total + 11;
        }
    }

    return total;
}