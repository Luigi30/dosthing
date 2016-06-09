#include "card.hpp"

    char Card::getRank(){
        if(id == -1) return '?';
        return rankIntToChar((id % 13) + 1);
    }

    char Card::getSuit() {
        if(id < 13) return 'h';
        else if (id >= 13 && id < 26) return 'd';
        else if (id >= 26 && id < 39) return 's';
        else if (id >= 39 && id < 52) return 'c';
        else return '?';
    }

    static int Card::rankCharToInt(char _rank){
        switch (_rank) {
        case 'A':
            return 1;
        case 'T':
            return 10;
        case 'J':
            return 11;
        case 'Q':
            return 12;
        case 'K':
            return 13;
        default:
            return _rank - 0x30;
        }
    }

    static int Card::rankIntToChar(int _rank){
        switch(_rank) {
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
                return 0x30 + _rank;
        }        
    }

    Card::Card(int _id){
        id = _id;
    }

    Card::Card(){
        id = -1;
    }


