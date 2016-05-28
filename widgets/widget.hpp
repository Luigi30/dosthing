#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "..\defines.hpp"
#include "..\fonts\font.hpp"
#include "..\shapes\shapes.hpp"

class Widget {
    //An interactive control on the screen, i.e. button or something

    protected:
    Point position;
    int sizeX, sizeY, color;

    public:
    Point getPosition() { return position; };
    //virtual void onClick();
    //virtual void redraw(Framebuffer framebuffer);
};

#endif
