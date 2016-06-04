#ifndef CARD_HPP
#define CARD_HPP

class Card {
    int id;

    public:
    char getRank();
    char getSuit();

    static int rankCharToInt(char rank);

    Card();
    Card(int);
};

#endif
