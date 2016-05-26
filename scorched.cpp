#include "scorched.hpp"

char *layer_background;
char *layer_text;
char *layer_final;

void scorched_earth(){

    //Convert the first entry of SHAPES.DAT into a list of Points.
    //Shape shape = Shape("TESTSHP", rawShapes[0]);
    
    //reset the framebuffers
    layer_background    = (char*)malloc(VGA_SIZE);
    layer_text          = (char*)malloc(VGA_SIZE);
    layer_final         = (char*)malloc(VGA_SIZE);
    
    memset(layer_background, 0, VGA_SIZE);
    memset(layer_text, 0, VGA_SIZE);
    memset(layer_final, 0, VGA_SIZE);

    draw_polygon(layer_background, shapesList[0].points, shapesList[0].getNumPoints(), Point(100, 100), 0, COLOR_GREEN);
    draw_rectangle_filled(layer_background, Point(0, 160), 320, 40, COLOR_LTGRAY);
    //draw_rectangle_filled(layer_background, Point(0, 0), 320, 200, COLOR_LTGRAY);

    char str[32] = "Now we need buttons!";
    fbPutString(layer_text, str, strlen(str), TEXTCELL(0,0), COLOR_WHITE, FONT_6x8);

    myTimerTicks = 0;
    while(true){
        if(myTimerTicks > TICKS_PER_SECOND){
            break;
        }
    }

    //reset mouse
    int mouseAttached = isMouseAttached();
    char isMouse[32];
    if(mouseAttached){
        strcpy(isMouse, "Mouse detected");
        cursorEnable();
    } else {
        strcpy(isMouse, "No mouse detected");
    }
    //fbPutString(layer_text, isMouse, strlen(isMouse), TEXTCELL(0,1), COLOR_WHITE, FONT_6x8);

    W_Button btn = W_Button(Point(40,160), 40, 20);
    btn.redraw(layer_text);

    //Redraw screen
    //Painter's algorithm
    overlay_framebuffers(layer_final, layer_background, VGA_SIZE);
    overlay_framebuffers(layer_final, layer_text, VGA_SIZE);
    memcpy(VGA_PTR, layer_final, VGA_SIZE);
    
    getch();

    /*
    while(true){
        while(!timer24Hz){
            //wait for 24Hz timer to fire
        }
        layer_background[i % 64000] = 0x02;
        i++;
        
        //Painter's algorithm
        overlay_framebuffers(layer_final, layer_background, VGA_SIZE);
        overlay_framebuffers(layer_final, layer_text, VGA_SIZE);
        memcpy(VGA_PTR, layer_final, VGA_SIZE);
        
        timer60Hz = 0;
    }
    */
}

void draw_ground(char *framebuffer){
    for(int j=150;j<VGA_HEIGHT;j++){
        for(int i=0;i<VGA_WIDTH;i++){
            setPixel(framebuffer, i, j, COLOR_BROWN);
        }
    }
}
