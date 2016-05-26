#include "..\video.hpp"
#include "..\shapes\point.hpp"

class Widget {
    //An interactive control on the screen, i.e. button or something

    protected:
    Point position;
    int sizeX, sizeY, color;

    public:
    Point getPosition() { return position; };
    virtual void onClick();
    virtual void redraw(char *framebuffer);
};
