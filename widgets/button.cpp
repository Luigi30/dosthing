#include "button.hpp"
#include "..\framebuffer.hpp"

W_Button::W_Button(){};

W_Button::W_Button(std::string _name, Point _pos, ButtonShape _shape, int _sizeX, int _sizeY, std::string _text){
    name = _name;
    position = Point(_pos.getX(), _pos.getY());
    shape = _shape;
    sizeX = _sizeX;
    sizeY = _sizeY;
    text = _text;
};

std::string W_Button::getName(){
    return name;
}

void W_Button::redraw(Framebuffer *layer_background, Framebuffer *layer_text){
    //Draw a rectangle at position.
    layer_text->putString("Drawing button!", strlen("Drawing button!"), Point(0, 8), COLOR_WHITE, FONT_4x6);

    //if(shape == BUTTON_SHAPE_RECT) {
        layer_background->draw_rectangle_filled(position, sizeX, sizeY, COLOR_LTGRAY);
        
        //shading: brighter in the upper and left sides
        layer_background->draw_line(position,
                Point(position.getX()+sizeX, position.getY()),
                COLOR_WHITE);
        layer_background->draw_line(position,
                Point(position.getX(), position.getY()+sizeY),
                COLOR_WHITE);

        //darker in the right and bottom sides
        layer_background->draw_line(Point(position.getX()+sizeX, position.getY()),
                Point(position.getX()+sizeX, position.getY()+sizeY),
                COLOR_DKGRAY);
        layer_background->draw_line(Point(position.getX(), position.getY()+sizeY),
                Point(position.getX()+sizeX, position.getY()+sizeY),
                COLOR_DKGRAY);
    //}

    //now draw the text
    layer_text->putString(text.c_str(), text.length(), Point(position.getX(), position.getY() + ((sizeY - 6)/2)), COLOR_BLUE, FONT_4x6);
}

int W_Button::pointIsInside(Point _point){
    int minX = position.getX() * 2;
    int maxX = minX + sizeX * 2;

    int minY = position.getY();
    int maxY = minY + sizeY;

    if(_point.getX() >= minX && _point.getX() <= maxX && _point.getY() >= minY && _point.getY() <= maxY){
        return true;
    } else {
        return false;
    }
}

void W_Button::onClick() {
    //do nothing;
}
