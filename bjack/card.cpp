#include "card.hpp"

    char Card::getRank(){
        if(id == -1) return '?';
        switch((id % 13) + 1) {
            case 1:
                return 'A';
            case 10:
                return 'T';
            case 11:
                return 'J';
            case 12:
                return 'Q';
            case 13:
                return 'K';
            default:
                return 0x30 + (id % 13) + 1;
        }
    }

    char Card::getSuit() {
        if(id < 13) return 'h';
        else if (id >= 13 && id < 26) return 'd';
        else if (id >= 26 && id < 39) return 's';
        else if (id >= 39 && id < 52) return 'c';
        else return '?';
    }

    Card::Card(int _id){
        id = _id;
    }

    Card::Card(){
        id = -1;
    }

