#ifndef CARD_HPP
#define CARD_HPP

/* Playing card. */

class Card {
    int id;

    public:
    char getRank();
    char getSuit();

    static int rankCharToInt(char rank);
    static int rankIntToChar(int rank);

    Card();
    Card(int);
};

#endif
