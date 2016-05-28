#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "widget.hpp"

class W_Button : public Widget {
    ButtonShape shape;
    std::string text;
    
    public:
    W_Button();
    W_Button(Point, ButtonShape, int, int, std::string);
    void onClick();
    void redraw(Framebuffer *framebuffer);
    //void setup_trigger(char *framebuffer, int id);
};

#endif
