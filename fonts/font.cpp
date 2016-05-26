#include <iterator>
#include <algorithm>
#include <stdio>

#include "font.hpp"

void fbPutGlyph(char *framebuffer, unsigned char *tile, int sizeX, int sizeY, int destX, int destY, int vga_color){ //8x8 font tile   
    long bytePos = (destY * 320) + destX;

    for(int y=0; y<sizeY; y++) {
        //for each row of the tile
        if(tile[y] & 0x80) {
            framebuffer[bytePos] = vga_color;
        }
        if(tile[y] & 0x40) {
            framebuffer[bytePos+1] = vga_color;
        }
        if(tile[y] & 0x20) {
            framebuffer[bytePos+2] = vga_color;
        }
        if(tile[y] & 0x10) {
            framebuffer[bytePos+3] = vga_color;
        }
        if(tile[y] & 0x08) {
            framebuffer[bytePos+4] = vga_color;
        }
        if(tile[y] & 0x04) {
            framebuffer[bytePos+5] = vga_color;
        }
        if(tile[y] & 0x02) {
            framebuffer[bytePos+6] = vga_color;
        }
        if(tile[y] & 0x01) {
            framebuffer[bytePos+7] = vga_color;
        }
        bytePos += 320;
    }
    
};

//void putFontStringIntoFramebuffer(char *framebuffer, char *str, int len, int destX, int destY, int vga_color, unsigned char *font, int sizeX, int sizeY){
void fbPutString(char *framebuffer, char *str, int len, int destX, int destY, int vga_color, Font font){
    for(int i=0;i<len;i++){
        int sizeX = font.getSizeX();
        int sizeY = font.getSizeY();
        
        fbPutGlyph(framebuffer, font.getGlyph(str[i]), sizeX, sizeY, destX+(sizeX * i), destY, vga_color);
    }
}
