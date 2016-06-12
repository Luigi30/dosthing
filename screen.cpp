#include "screen.hpp"
#include "mouse.hpp"

void Screen::redraw(){
    //render buttons to layer_background and text to layer_text
    memset(layer_widgets.getPixels(), 0, VGA_SIZE);
    for(int i=0;i<widgetsList.size();i++){
        widgetsList[i]->redraw(&layer_widgets, &layer_text);
    }
    
    memset(layer_final.getPixels(), 0, VGA_SIZE);    
    layer_final.overlay(layer_background, VGA_SIZE);
    layer_final.overlay(layer_widgets, VGA_SIZE);
    layer_final.overlay(layer_text, VGA_SIZE);

    //disable cursor while redrawing or we get graphic garbage on screen
    Mouse::cursorDisable();
    memcpy(VGA_PTR, layer_final.getPixels(), VGA_SIZE);
    Mouse::cursorEnable();
}

void Screen::init_framebuffers(){
    layer_background    = Framebuffer();
    layer_widgets       = Framebuffer();
    layer_text          = Framebuffer();
    layer_final         = Framebuffer();    
}

void Screen::addButton(Button _button){
    buttons.push_back(_button);
}

void Screen::drawButton(Button _button){
    
//Draw a rectangle at position.
    //if(shape == BUTTON_SHAPE_RECT) {
        layer_widgets.draw_rectangle_filled(_button.position, _button.sizeX, _button.sizeY, COLOR_LTGRAY);
        
        //shading: brighter in the upper and left sides
        layer_widgets.draw_line(_button.position,
                Point(_button.position.getX()+_button.sizeX, _button.position.getY()),
                COLOR_WHITE);
        layer_widgets.draw_line(_button.position,
                Point(_button.position.getX(), _button.position.getY()+_button.sizeY),
                COLOR_WHITE);

        //darker in the right and bottom sides
        layer_widgets.draw_line(Point(_button.position.getX()+_button.sizeX, _button.position.getY()),
                Point(_button.position.getX()+_button.sizeX, _button.position.getY()+_button.sizeY),
                COLOR_DKGRAY);
        layer_widgets.draw_line(Point(_button.position.getX(), _button.position.getY()+_button.sizeY),
                Point(_button.position.getX()+_button.sizeX, _button.position.getY()+_button.sizeY),
                COLOR_DKGRAY);
    //}

    //now draw the text
    layer_text.putString(_button.text.c_str(), _button.text.length(), Point(_button.position.getX(), _button.position.getY() + ((_button.sizeY - 6)/2)), 0x10, FONT_4x6);
}

Widget* Screen::getClickedWidget(Point _point){
    //which widget did we click? -1 if none, widget ID otherwise
    for(int i=0;i<widgetsList.size();i++){
        if(widgetsList[i]->pointIsInside(_point)){
            return widgetsList[i];
        }
    }
    return NULL;
}

std::string Screen::getClickedWidgetName(Point _point){
    Widget *clicked = getClickedWidget(_point);
    if(clicked != NULL){
        return clicked->getName();
    } else {
        return NULL;
    }
}

void Screen::removeWidget(std::string _name){
    //locate widget with the matching name and remove it from the list
    //widget names must be unique
    
    for(int i=0;i<widgetsList.size();i++){
        if(widgetsList[i]->getName() == _name){
            widgetsList.erase(widgetsList.begin() + i);
            return;
        }
    }
    
}
