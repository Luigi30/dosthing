#include "scorched.hpp"
#include "video.hpp"

char *layer_background;
char *layer_text;
char *layer_final;

void scorched_earth(){

    //Convert the first entry of SHAPES.DAT into a list of Points.
    int pointsFound = 0;

    //Shape shape = Shape("TESTSHP", rawShapes[0]);
    
    //reset the framebuffers
    layer_background    = (char*)malloc(VGA_SIZE);
    layer_text          = (char*)malloc(VGA_SIZE);
    layer_final         = (char*)malloc(VGA_SIZE);
    
    memset(layer_background, 0, VGA_SIZE);
    memset(layer_text, 0, VGA_SIZE);
    memset(layer_final, 0, VGA_SIZE);

    //draw_polygon(layer_background, shapesList[0].points, shapesList[0].getNumPoints(), Point(100, 100), 0, COLOR_GREEN);
    //draw_rectangle_filled(layer_background, Point(50,100), 100, 20, COLOR_GREEN);

    myTimerTicks = 0;
    while(true){
        if(myTimerTicks > TICKS_PER_SECOND){
            char buffer[64];
                        
            sprintf(buffer, "%d points found", shapesList[0].getNumPoints());
            fbPutString(layer_text, buffer, strlen(buffer), 0, 0, COLOR_WHITE, FONT8X8);
            break;
        }
    }
    
    draw_ground(layer_background);

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
