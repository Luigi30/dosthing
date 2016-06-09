#include "cardgfx.hpp"
#include "..\framebuffer.hpp"

W_Card_Graphic::W_Card_Graphic(std::string _name, Point _position, char _rank, char _suit){
    //size is fixed at 50x60
    name = _name;
    size = Size2D(50, 60);
    position = _position;
    rank = _rank;
    suit = _suit;
}

W_Card_Graphic::W_Card_Graphic(std::string _name, Point _position, Card _card){
    //size is fixed at 50x60
    name = _name;
    size = Size2D(50, 60);
    position = _position;
    rank = _card.getRank();
    suit = _card.getSuit();
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
    int sizeX = _size.getX() * ICON_SCALE_FACTOR;
    int sizeY = _size.getY() * ICON_SCALE_FACTOR;
    Point localPosition = position + _pos;
    
    for(int y=0; y<sizeY; y++){
        for(int x=0; x<sizeX; x++){
            if(icon[i] != 0x0D){
                layer->setPixel(localPosition.getX() + x, localPosition.getY() + y, icon[i]);
            }
            i++;
        }
    }

}

void W_Card_Graphic::loadGraphics(){
    
    for(int y=0;y<10;y++){
        for(int x=0;x<10;x++){
            PCX_SUIT_ICON_DIAMOND[y*10 + x] = suitIconPixels[y*40 + x];
        }
    }

    for(int y=0;y<10;y++){
        for(int x=0;x<10;x++){
            PCX_SUIT_ICON_HEART[y*10 + x] = suitIconPixels[y*40 + 10 + x];
        }
    }

    for(int y=0;y<10;y++){
        for(int x=0;x<10;x++){
            PCX_SUIT_ICON_CLUB[y*10 + x] = suitIconPixels[y*40 + 20 + x];
        }
    }

    for(int y=0;y<10;y++){
        for(int x=0;x<10;x++){
            PCX_SUIT_ICON_SPADE[y*10 + x] = suitIconPixels[y*40 + 30 + x];
        }
    }

}

void W_Card_Graphic::drawRankAndSuitIcons(Framebuffer *layer, char rank, char suit){
    switch(suit){
        case 's':
            drawIcon(layer, (char*)PCX_SUIT_ICON_SPADE, SUIT_POSITION, ICON_SIZE);
            break;
        case 'c':
            drawIcon(layer, (char*)PCX_SUIT_ICON_CLUB, SUIT_POSITION, ICON_SIZE);
            break;
        case 'h':
            drawIcon(layer, (char*)PCX_SUIT_ICON_HEART, SUIT_POSITION, ICON_SIZE);
            break;
        case 'd':
            drawIcon(layer, (char*)PCX_SUIT_ICON_DIAMOND, SUIT_POSITION, ICON_SIZE);
            break;
    }

    drawIcon(layer, rankIconPointers[Card::rankCharToInt(rank) - 1], RANK_POSITION, ICON_SIZE);
}

void W_Card_Graphic::redraw(Framebuffer *background, Framebuffer *text){

    int sizeX = size.getX();
    int sizeY = size.getY();
    int i=0;
    for(int y=0; y<sizeY; y++){
        for(int x=0; x<size.getX(); x++){
            if(blankCardPixels[i] != 0x00) {
                background->setPixel(position.getX()+x, position.getY()+y, blankCardPixels[i]);
            }
            i++;
        }
    }

    /*
    for(int y=0; y<sizeY; y++){
        for(int x=0; x<size.getX()+2; x++){
            background->setPixel(position.getX() + x, position.getY() + y, COLOR_WHITE);
        }
    }
    */

    //draw the suit icon on the card
    drawRankAndSuitIcons(background, rank, suit);

    //char str[32];
    //sprintf(str, "PCX is %dx%d", blankCard.getHeader().HScrSize, blankCard.getHeader().VScrSize);
    //text->putString(str, strlen(str), TEXTCELL(0, 3), COLOR_WHITE, FONT_6x8);
    
}
