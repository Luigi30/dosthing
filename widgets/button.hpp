#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "widget.hpp"

class W_Button : public Widget {
    ButtonShape shape;
    std::string text;
    
    public:
    W_Button();
    W_Button(std::string, Point, ButtonShape, int, int, std::string);
    void onClick();
    virtual void redraw(Framebuffer *background, Framebuffer *text);
    virtual int pointIsInside(Point _point);
    virtual std::string getName();
};

#endif
