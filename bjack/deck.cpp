#include "deck.hpp"

Deck::Deck(){
    availableCards.clear();
    for(int i=0;i<52;i++){
        Card card = Card(i);
        availableCards.push_back(card);
    }
}

Card Deck::popCard(int id){
    Card card = availableCards[id];
    availableCards.erase(availableCards.begin()+id);
    return card;
}

Card Deck::getRandomCard() {
    Card card = popCard(std::rand() % availableCards.size());
    return card;
}
