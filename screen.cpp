#include "screen.hpp"

void Screen::redraw(){
    //render buttons to layer_background and text to layer_text
    for(int i=0;i<widgetsList.size();i++){
        widgetsList[i]->redraw(&layer_background, &layer_text);
    }
    
    memset(layer_final.getPixels(), 0, VGA_SIZE);    
    layer_final.overlay(layer_background, VGA_SIZE);
    layer_final.overlay(layer_text, VGA_SIZE);    
    memcpy(VGA_PTR, layer_final.getPixels(), VGA_SIZE);    
}

void Screen::init_framebuffers(){
    layer_background    = Framebuffer();
    layer_text          = Framebuffer();
    layer_final         = Framebuffer();    
}

void Screen::addButton(Button _button){
    buttons.push_back(_button);
}

void Screen::drawButton(Button _button){
    
//Draw a rectangle at position.
    //if(shape == BUTTON_SHAPE_RECT) {
        layer_background.draw_rectangle_filled(_button.position, _button.sizeX, _button.sizeY, COLOR_LTGRAY);
        
        //shading: brighter in the upper and left sides
        layer_background.draw_line(_button.position,
                Point(_button.position.getX()+_button.sizeX, _button.position.getY()),
                COLOR_WHITE);
        layer_background.draw_line(_button.position,
                Point(_button.position.getX(), _button.position.getY()+_button.sizeY),
                COLOR_WHITE);

        //darker in the right and bottom sides
        layer_background.draw_line(Point(_button.position.getX()+_button.sizeX, _button.position.getY()),
                Point(_button.position.getX()+_button.sizeX, _button.position.getY()+_button.sizeY),
                COLOR_DKGRAY);
        layer_background.draw_line(Point(_button.position.getX(), _button.position.getY()+_button.sizeY),
                Point(_button.position.getX()+_button.sizeX, _button.position.getY()+_button.sizeY),
                COLOR_DKGRAY);
    //}

    //now draw the text
    layer_text.putString(_button.text.c_str(), _button.text.length(), Point(_button.position.getX(), _button.position.getY() + ((_button.sizeY - 6)/2)), 0x10, FONT_4x6);
}

std::string Screen::getClickedWidget(Point _point){
    //which widget did we click? -1 if none, widget ID otherwise
    for(int i=0;i<widgetsList.size();i++){
        if(widgetsList[i]->pointIsInside(_point)){
            return widgetsList[i]->getName();
        }
    }
    return NULL;
}
