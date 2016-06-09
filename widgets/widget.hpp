#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "..\defines.hpp"
#include "..\fonts\font.hpp"
#include "..\shapes\shapes.hpp"

class Framebuffer;

class Widget {
    //An interactive control on the screen, i.e. button or something

    protected:
    Point position;
    Size2D size;
    int color;
    std::string name;

    public:
    virtual std::string getName();
    Point getPosition() { return position; };
    virtual void onClick(){};
    virtual void redraw(Framebuffer *layer, Framebuffer *text){};
    virtual void remove(Framebuffer *layer, Framebuffer *text){};
    virtual int pointIsInside(Point);
};

#endif
