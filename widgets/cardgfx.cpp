#include "cardgfx.hpp"
#include "..\framebuffer.hpp"
#include "..\pcx.hpp"
#include "..\bjack\card.hpp"

W_Card_Graphic::W_Card_Graphic(std::string _name, Point _position, char _rank, char _suit){
    //size is fixed at 50x70
    name = _name;
    size = Size2D(50, 70);
    position = _position;
    rank = _rank;
    suit = _suit;
}

int W_Card_Graphic::pointIsInside(Point _point){
    int minX = position.getX() * 2;
    int maxX = minX + size.getX() * 2;

    int minY = position.getY();
    int maxY = minY + size.getY();

    if(_point.getX() >= minX && _point.getX() <= maxX && _point.getY() >= minY && _point.getY() <= maxY){
        return true;
    } else {
        return false;
    }
}

void W_Card_Graphic::drawIcon(Framebuffer *layer, const char *icon, Point _pos, Size2D _size){

    int i=0;
    int sizeX = _size.getX();
    int sizeY = _size.getY();
    Point localPosition = position + _pos;
    
    for(int y=0; y<sizeY; y++){
        for(int x=0; x<sizeX; x++){
            layer->setPixel(localPosition.getX() + x, localPosition.getY() + y, icon[i]);
            i++;
        }
    }

}

void W_Card_Graphic::drawRankAndSuitIcons(Framebuffer *layer, char rank, char suit){
    switch(suit){
        case 's':
            drawIcon(layer, SUIT_ICON_SPADE, SUIT_POSITION, ICON_SIZE);
            break;
        case 'c':
            drawIcon(layer, SUIT_ICON_CLUB, SUIT_POSITION, ICON_SIZE);
            break;
        case 'h':
            drawIcon(layer, SUIT_ICON_HEART, SUIT_POSITION, ICON_SIZE);
            break;
        case 'd':
            drawIcon(layer, SUIT_ICON_DIAMOND, SUIT_POSITION, ICON_SIZE);
            break;
    }

    drawIcon(layer, rankIconPointers[Card::rankCharToInt(rank) - 1], RANK_POSITION, ICON_SIZE);
}

void W_Card_Graphic::redraw(Framebuffer *background, Framebuffer *text){

    PCX blankGraphic = PCX("C_BLANK.PCX");
    unsigned char *cardPixels = blankGraphic.getPixelData();
    int i=0;

    for(int y=0; y<size.getY(); y++){
        for(int x=0; x<size.getX()+2; x++){
            background->setPixel(position.getX() + x, position.getY() + y, cardPixels[i]);
            i++;
        }
    }

    //draw the suit icon on the card
    drawRankAndSuitIcons(background, rank, suit);

    char str[32];
    sprintf(str, "PCX is %dx%d", blankGraphic.getHeader().HScrSize, blankGraphic.getHeader().VScrSize);
    text->putString(str, strlen(str), TEXTCELL(0, 3), COLOR_WHITE, FONT_6x8);
    
}
