#include "button.hpp"
#include "..\framebuffer.hpp"

W_Button::W_Button(){};

W_Button::W_Button(Point _pos, ButtonShape _shape, int _sizeX, int _sizeY, std::string _text){
    position = Point(_pos.getX(), _pos.getY());
    shape = _shape;
    sizeX = _sizeX;
    sizeY = _sizeY;
    text = _text;
};

void W_Button::redraw(Framebuffer *framebuffer){
    //Draw a rectangle at position.
    framebuffer->putString("Drawing button!", strlen("Drawing button!"), Point(0, 8), COLOR_WHITE, FONT_4x6);

    //if(shape == BUTTON_SHAPE_RECT) {
        framebuffer->draw_rectangle_filled(position, sizeX, sizeY, COLOR_LTGRAY);
        
        //shading: brighter in the upper and left sides
        framebuffer->draw_line(position,
                Point(position.getX()+sizeX, position.getY()),
                COLOR_WHITE);
        framebuffer->draw_line(position,
                Point(position.getX(), position.getY()+sizeY),
                COLOR_WHITE);

        //darker in the right and bottom sides
        framebuffer->draw_line(Point(position.getX()+sizeX, position.getY()),
                Point(position.getX()+sizeX, position.getY()+sizeY),
                COLOR_DKGRAY);
        framebuffer->draw_line(Point(position.getX(), position.getY()+sizeY),
                Point(position.getX()+sizeX, position.getY()+sizeY),
                COLOR_DKGRAY);
    //}

    //now draw the text
    framebuffer->putString(text.c_str(), text.length(), Point(position.getX(), position.getY() + ((sizeY - 6)/2)), COLOR_GRAYS+0, FONT_4x6);
}
/*
void W_Button::setup_trigger(char *framebuffer, int id){
    //ID is the trigger from the list
    draw_rectangle_filled(framebuffer, position, sizeX, sizeY, id);
}
*/

void W_Button::onClick() {
    //do nothing;
}
