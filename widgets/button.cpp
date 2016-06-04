#include "button.hpp"
#include "..\framebuffer.hpp"

W_Button::W_Button(){};

W_Button::W_Button(std::string _name, Point _pos, ButtonShape _shape, Size2D _size, std::string _text){
    name = _name;
    position = Point(_pos.getX(), _pos.getY());
    shape = _shape;
    size = _size;
    text = _text;
};

void W_Button::redraw(Framebuffer *layer_background, Framebuffer *layer_text){
    //Draw a rectangle at position.
    layer_text->putString("Drawing button!", strlen("Drawing button!"), Point(0, 8), COLOR_WHITE, FONT_4x6);

    //if(shape == BUTTON_SHAPE_RECT) {
        layer_background->draw_rectangle_filled(position, size.getX(), size.getY(), COLOR_LTGRAY);
        
        //shading: brighter in the upper and left sides
        layer_background->draw_line(position,
                Point(position.getX()+size.getX(), position.getY()),
                COLOR_WHITE);
        layer_background->draw_line(position,
                Point(position.getX(), position.getY()+size.getY()),
                COLOR_WHITE);

        //darker in the right and bottom sides
        layer_background->draw_line(Point(position.getX()+size.getX(), position.getY()),
                Point(position.getX()+size.getX(), position.getY()+size.getY()),
                COLOR_DKGRAY);
        layer_background->draw_line(Point(position.getX(), position.getY()+size.getY()),
                Point(position.getX()+size.getX(), position.getY()+size.getY()),
                COLOR_DKGRAY);
    //}

    //now draw the text
    layer_text->putString(text.c_str(), text.length(), Point(position.getX(), position.getY() + ((size.getY() - 6)/2)), COLOR_BLUE, FONT_4x6);
}

int W_Button::pointIsInside(Point _point){
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

void W_Button::onClick() {
    //do nothing;
}
