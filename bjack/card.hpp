#ifndef CARD_HPP
#define CARD_HPP

class Card {
    int id;

    public:
    char getRank();
    char getSuit();

    Card();
    Card(int);
};

#endif