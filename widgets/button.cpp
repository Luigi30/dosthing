#include "button.hpp"

W_Button::W_Button(Point _pos, ButtonShape _shape, int _sizeX, int _sizeY, std::string _text){
    position = Point(_pos.getX(), _pos.getY());
    sizeX = _sizeX;
    sizeY = _sizeY;
    text = _text;
};

/*
void W_Button::redraw(char *framebuffer){
    //Draw a rectangle at position.

    if(shape == BUTTON_SHAPE_RECT) {
        draw_rectangle_filled(framebuffer, position, sizeX, sizeY, COLOR_LTGRAY);
        
        //shading: brighter in the upper and left sides
        draw_line(framebuffer,
                position,
                Point(position.getX()+sizeX, position.getY()),
                COLOR_WHITE);
        draw_line(framebuffer,
                position,
                Point(position.getX(), position.getY()+sizeY),
                COLOR_WHITE);

        //darker in the right and bottom sides
        draw_line(framebuffer,
                Point(position.getX()+sizeX, position.getY()),
                Point(position.getX()+sizeX, position.getY()+sizeY),
                COLOR_DKGRAY);
        draw_line(framebuffer,
                Point(position.getX(), position.getY()+sizeY),
                Point(position.getX()+sizeX, position.getY()+sizeY),
                COLOR_DKGRAY);
    }

    //now draw the text
    fbPutString(framebuffer, text.c_str(), text.length(), Point(position.getX(), position.getY() + ((sizeY - 6)/2)), COLOR_GRAYS+0, FONT_4x6);
}


void W_Button::setup_trigger(char *framebuffer, int id){
    //ID is the trigger from the list
    draw_rectangle_filled(framebuffer, position, sizeX, sizeY, id);
}
*/

//void W_Button::onClick() {
    //do nothing;
//}
