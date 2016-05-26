#include "button.hpp"

W_Button::W_Button(Point _pos, int _sizeX, int _sizeY){
    position = Point(_pos.getX(), _pos.getY());
    sizeX = _sizeX;
    sizeY = _sizeY;
};

void W_Button::redraw(char *framebuffer){
    //Draw a rectangle at position.
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

void W_Button::onClick() {
    //do nothing;
}
