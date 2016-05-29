#include "scorched.hpp"

//std::vector<W_Button> screenWidgets;
W_Button screenWidgets[16];

int keyInBuffer(){
    union REGS regs;
    regs.h.ah = 0x01;
    int386(0x16, &regs, &regs);

    if(regs.h.al){
        regs.h.ah = 0x00;
        int386(0x16, &regs, &regs);
        return regs.h.al;
    }

    return 0x00;
}

void scorched_earth(){

    //Convert the first entry of SHAPES.DAT into a list of Points.
    //Shape shape = Shape("TESTSHP", rawShapes[0]);

    PCX pcx = PCX("DAMFERBO.PCX");
    
    //reset the framebuffers
    layer_background    = Framebuffer();
    layer_text          = Framebuffer();
    layer_final         = Framebuffer();
    layer_trigger       = Framebuffer();
    
    layer_background.draw_polygon(shapesList[0].points, shapesList[0].getNumPoints(), Point(100, 100), 0, COLOR_GREEN);
    layer_background.draw_rectangle_filled(Point(0, 160), 320, 40, COLOR_LTGRAY);

    char str[32] = "Now we need buttons!";
    //layer_text.putString(str, strlen(str), TEXTCELL(0, 0), COLOR_WHITE, FONT_6x8);

    myTimerTicks = 0;
    while(true){
        if(myTimerTicks > TICKS_PER_SECOND){
            break;
        }
    }
    //reset mouse
    MouseData mouseData;
    int mouseAttached = isMouseAttached();
    char isMouse[32];
    if(mouseAttached){
        strcpy(isMouse, "Mouse detected");
        cursorEnable();
    } else {
        strcpy(isMouse, "No mouse detected");
    }

    std::string testStr = "Test";
    screenWidgets[0] = W_Button(Point(240,160), BUTTON_SHAPE_RECT, 40, 20, testStr);
    
    while(true){
        while(!timer24Hz){
            //wait for 24Hz timer to fire
        }

                /*
        mouseData = getMouseData();
        if(mouseData.lmb_click){
            //fbPutString(layer_text, "LMB down", strlen("LMB down"), TEXTCELL(0, 3), COLOR_WHITE, FONT_6x8);
            layer_text.putString("LMB down", strlen("LMB down"), TEXTCELL(0, 3), COLOR_WHITE, FONT_6x8);
        } else {
            //fbPutString(layer_text, "LMB up  ", strlen("LMB up  "), TEXTCELL(0, 3), COLOR_WHITE, FONT_6x8);
            layer_text.putString("LMB up  ", strlen("LMB up  "), TEXTCELL(0, 3), COLOR_WHITE, FONT_6x8);
        }
                */
        int key = keyInBuffer();
        if(key) {
            char buf[32];
            sprintf(buf, "You pressed %d   ", key);
            //layer_text.putString(buf, strlen(buf), TEXTCELL(0,2), COLOR_WHITE, FONT_6x8);

            if(key == 0x1B) {
                exit_program("Returning to DOS...");
            }

        }

        //if(needsRedraw){
        redraw_screen();
        //}
        timer24Hz = 0;
    }
}

void draw_ground(Framebuffer framebuffer){
    for(int j=150;j<VGA_HEIGHT;j++){
        for(int i=0;i<VGA_WIDTH;i++){
            framebuffer.setPixel(i, j, COLOR_BROWN);
        }
    }
}

void redraw_screen(){
    //widgets go on the text layer
    layer_text.draw_widget(screenWidgets[0]);
    
    //Painter's algorithm        
    memset(layer_final.getPixels(), 0, VGA_SIZE);    
    layer_final.overlay(layer_background, VGA_SIZE);
    layer_final.overlay(layer_text, VGA_SIZE);    
    memcpy(VGA_PTR, layer_final.getPixels(), VGA_SIZE);

    needsRedraw = false;
}

void exit_program(std::string msg) {
    _setvideomode(_DEFAULTMODE);
    printf(msg.c_str());
    exit(0);
}

    /*    
    unsigned char* pcxPixels = pcx.getPixelData();
    int pcxSizeX = pcx.getHeader().HScrSize + 1;//DAMFERBO needs + 1? why?
    int pcxSizeY = pcx.getHeader().VScrSize;

    for(int y = 0; y < 200; y++){
        for(int x = 0; x < pcxSizeX; x++){
            layer_background.setPixel(x, y, pcxPixels[x + (y * pcxSizeX)]);
        }
    }
    */
