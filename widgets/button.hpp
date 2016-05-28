#include "widget.hpp"


class W_Button : public Widget {
    ButtonShape shape;
    std::string text;
    
    public:
    W_Button(Point, ButtonShape, int, int, std::string);
    //void onClick();
    //void redraw(char *framebuffer);
    //void setup_trigger(char *framebuffer, int id);
};
