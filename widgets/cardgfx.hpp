#ifndef CARDGFX_HPP
#define CARDGFX_HPP

#include "widget.hpp"

const char RANK_ICON_ACE[] = { 15,00,00,00,15,
                               00,15,15,15,00,
                               00,00,00,00,00,
                               00,15,15,15,00,
                               00,15,15,15,00 };
                                                           
const char RANK_ICON_TWO[] = { 00,00,00,00,00,
                               15,15,15,15,00,
                               00,00,00,00,00,
                               00,15,15,15,15,
                               00,00,00,00,00 };
                                                           
const char RANK_ICON_THREE[]={ 00,00,00,00,00,
                               15,15,15,15,00,
                               15,15,00,00,00,
                               15,15,15,15,00,
                               00,00,00,00,00 };
                                                           
const char RANK_ICON_FOUR[] ={ 00,15,15,15,00,
                               00,15,15,15,00,
                               00,00,00,00,00,
                               15,15,15,15,00,
                               15,15,15,15,00 };
                                                           
const char RANK_ICON_FIVE[] ={ 00,00,00,00,00,
                               00,15,15,15,15,
                               00,00,00,00,00,
                               15,15,15,15,00,
                               00,00,00,00,00 };
                                                           
const char RANK_ICON_SIX[] = { 00,00,00,00,00,
                               00,15,15,15,15,
                               00,00,00,00,00,
                               00,15,15,15,00,
                               00,00,00,00,00 };
                                                           
const char RANK_ICON_SEVEN[]={ 00,00,00,00,00,
                               15,15,15,15,00,
                               15,15,15,15,00,
                               15,15,15,15,00,
                               15,15,15,15,00 };
                                                           
const char RANK_ICON_EIGHT[]={ 00,00,00,00,00,
                               00,15,15,15,00,
                               00,00,00,00,00,
                               00,15,15,15,00,
                               00,00,00,00,00 };
                                                           
const char RANK_ICON_NINE[]= { 00,00,00,00,00,
                               00,15,15,15,00,
                               00,00,00,00,00,
                               15,15,15,15,00,
                               15,15,15,15,00 };
                                                           
const char RANK_ICON_TEN[] = { 00,15,00,00,00,
                               00,15,00,15,00,
                               00,15,00,15,00,
                               00,15,00,15,00,
                               00,15,00,00,00 };
                                                           
const char RANK_ICON_JACK[] ={ 15,15,15,15,00,
                               15,15,15,15,00,
                               00,15,15,15,00,
                               00,15,15,15,00,
                               00,00,00,00,00 };
                                                           
const char RANK_ICON_QUEEN[]={ 00,00,00,00,00,
                               00,15,15,15,00,
                               00,15,15,15,00,
                               00,15,15,00,00,
                               00,00,00,00,00 };
                                                           
const char RANK_ICON_KING[] ={ 00,15,15,15,00,
                               00,15,15,00,15,
                               00,00,00,15,15,
                               00,15,15,00,15,
                               00,15,15,15,00 };

const char SUIT_ICON_SPADE[] = { 15,15,00,15,15,
                                 15,00,00,00,15,
                                 00,00,00,00,00,
                                 15,15,00,15,15,
                                 15,15,00,15,15 };

const char SUIT_ICON_CLUB[] = { 15,15,00,15,15,
                                15,00,00,00,15,
                                00,00,00,00,00,
                                15,15,00,15,15,
                                15,15,00,15,15 };

const char SUIT_ICON_HEART[] = { 00,04,00,04,00,
                                 04,04,04,04,04,
                                 04,04,04,04,04,
                                 00,04,04,04,00,
                                 00,00,04,00,00, };

const char SUIT_ICON_DIAMOND[] = { 00,00,04,00,00,
                                   00,04,04,04,00,
                                   04,04,04,04,04,
                                   00,04,04,04,00,
                                   00,00,04,00,00, };

const char* rankIconPointers[] = { RANK_ICON_ACE, RANK_ICON_TWO, RANK_ICON_THREE, RANK_ICON_FOUR, RANK_ICON_FIVE, RANK_ICON_SIX, RANK_ICON_SEVEN, RANK_ICON_EIGHT, RANK_ICON_NINE, RANK_ICON_TEN, RANK_ICON_JACK, RANK_ICON_QUEEN, RANK_ICON_KING };

const Size2D ICON_SIZE = Size2D(5, 5);
const Point RANK_POSITION = Point(2, 6);
const Point SUIT_POSITION = Point(2, 12);

class W_Card_Graphic : public Widget {
    char rank;
    char suit;
    
    public:
    W_Card_Graphic();
    W_Card_Graphic(std::string _name, Point _position, char _rank, char _suit);

    virtual void redraw(Framebuffer *background, Framebuffer *text);
    virtual int pointIsInside(Point _point);
    void W_Card_Graphic::drawRankAndSuitIcons(Framebuffer* layer, char rank, char suit);
    void W_Card_Graphic::drawIcon(Framebuffer*, const char*, Point, Size2D);
};

#endif
