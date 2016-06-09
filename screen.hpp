#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <vector>
#include <stdlib>
#include "framebuffer.hpp"
#include "widgets\widget.hpp"

struct Button {
    Point position;
    int sizeX;
    int sizeY;
    std::string text;

    Button(){};

    Button(Point _pos, int _x, int _y, std::string _text){
        position = Point(_pos.getX(), _pos.getY());
        sizeX = _x;
        sizeY = _y;
        text = _text;
    }
};

class Screen {
    std::vector<Button> buttons;
    
    public:
    Framebuffer layer_background;
    Framebuffer layer_widgets;
    Framebuffer layer_text;
    Framebuffer layer_final;

    void drawMouseCursor(Framebuffer layer);
    Widget* getClickedWidget(Point);
    std::string getClickedWidgetName(Point);

    std::vector<Widget*> widgetsList;
    void removeWidget(std::string _name);

    void addButton(Button);
    void drawButton(Button);

    void init_framebuffers();
    void redraw();
};

#endif
