/* entrypoint */
#include "main.hpp"

/* Functions */
void init_global_pointers(){
    VGA_PTR = (char*)VGA_LINEAR_ADDRESS;
}

void abort(char *msg){
    printf("Critical error: %s", msg);
    exit(255);
}

// PIT interrupt handler
void __interrupt __far timerHandler () {
    //This will fire at a rate set in init_timer()
    myTimerTicks++;

    if(myTimerTicks % 4 == 0) {
        timer60Hz = 1;
    }

    if(myTimerTicks % 10 == 0) {
        timer24Hz = 1;
    }
    
    // increment the tick counter by the value we loaded into the timer
    biosClockTicks += timerReload;
    // should we also call the BIOS handler?
    if ( biosClockTicks >= 0x10000 ) {
        // decrement the value
        biosClockTicks -= 0x10000;
      
        // call the BIOS handler
        _chain_intr( biosTimerHandler );
    } else {
        // we didn't call the BIOS handler so acknowledge the interrupt
        outp( 0x20, 0x20 );
    }
}

void init_timer(int rate){
    //Initialize our timer
    myTimerTicks = 0;
    
    long timerReload = rate;
    biosTimerHandler = _dos_getvect(0x08); //DOS timer handler

    _disable();
    _dos_setvect(0x08, timerHandler);
    outp(0x43, 0x34);
    outp(0x40, timerReload & 0xFF);
    outp(0x40, timerReload >> 8);
    _enable();
}

void load_shapes(){
    //Read SHAPES.DAT
    FILE *hShapesFile;
    hShapesFile = fopen("SHAPES.DAT", "r");

    char rawShapes[64][4];

    int numShapes = 0;

    if(hShapesFile != NULL){
        while(fgets(rawShapes[numShapes], 255, hShapesFile) != NULL){
            numShapes++;
        }
    } else {
        abort("SHAPES.DAT not found.");
    }

    //printf("Found %d shapes...", numShapes);

    for(int i=0;i<numShapes;i++){        
        shapesList.push_back(Shape("NEWSHAPE", rawShapes[i])); //TODO: shape names
    }
}

void load_strings(){
    FILE *stringsData = fopen("STRINGS.DAT", "r");

    //Read STRINGS.DAT
    if(stringsData != NULL){
        int i = 0;
        while(fgets(messages[i], 255, stringsData) != NULL) {
            i++;
        }
    } else {
        abort("STRINGS.DAT not found.");
    }
}

int main () {

    DEBUG("Serial connected\r\n");
       
    sleep(1);

    init_timer(4970); //240Hz timer    
    init_global_pointers();

    load_strings();
    load_shapes();
    
    _setvideomode(_MRES256COLOR); //Change to mode 13h
    _setcolor(COLOR_WHITE);

    scorched_earth();

    //Back to normal
    _setvideomode(_DEFAULTMODE);
    exit(0);
}