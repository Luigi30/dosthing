#include "widget.hpp"

class W_Button : public Widget {
    public:
    W_Button(Point, int, int);
    void onClick();
    void redraw(char *framebuffer);
};
