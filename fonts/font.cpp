#include <iterator>
#include <algorithm>
#include <stdio>

#include "font.hpp"

void fbPutGlyph(char *framebuffer, unsigned char *tile, int sizeX, int sizeY, int destX, int destY, int vga_color){ //8x8 font tile   
    long bytePos = (destY * 320) + destX;

    for(int y=0; y<sizeY; y++){
        for(int x=sizeX-1; x>0; x--){
            if(tile[y] & 1 << x){
                framebuffer[bytePos] = vga_color;
            }
            bytePos++;
        }
        bytePos += (320 - sizeX+1);
    }

/*
    for(int y=sizeY; y>0; y--){
        for(int x=0; x<sizeX; x++){
            if(tile[x] & 1 << y) {
                framebuffer[bytePos] = vga_color;
            }
            bytePos += 320;
        }
        bytePos++;
        bytePos -= (320 * sizeY);
    }
*/
    
};

//void putFontStringIntoFramebuffer(char *framebuffer, char *str, int len, int destX, int destY, int vga_color, unsigned char *font, int sizeX, int sizeY){
void fbPutString(char *framebuffer, char *str, int len, int destX, int destY, int vga_color, Font font){
    for(int i=0;i<len;i++){
        int sizeX = font.getSizeX();
        int sizeY = font.getSizeY();
        
        fbPutGlyph(framebuffer, font.getGlyph(str[i]), sizeX, sizeY, destX+(sizeX * i), destY, vga_color);
    }
}
