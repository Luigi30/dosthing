#include "framebuffer.hpp"

Framebuffer::Framebuffer(){
    pixels = (unsigned char*)malloc(64000+1);
    memset(pixels, 0, VGA_SIZE);
}

unsigned char *Framebuffer::getPixels(){
    return pixels;
}

void Framebuffer::draw_line(Point start, Point end, int color){
    //Draw a 1-pixel thick line between two points.
    int x_distance = end.getX() - start.getX();
    int y_distance = end.getY() - start.getY();

    //is this a vertical line?
    if(x_distance == 0){
        for(int i=start.getY(); i<end.getY(); i++){
            setPixel(start.getX(), i, color);
        }
    } else if (y_distance == 0) {
        //is this a horizontal line?
        int y = start.getY();

        for(int i=0;i<x_distance;i++) {
            setPixel(start.getX() + i, y, color);
        }        
    } else {
        //calculate slope:  y = mx + b
        double slope = getSlope(start, end);
        //solve for b: y = mx + b -> y - mx = b
        double y_intercept = getYIntercept(start, slope);

        //so we have a point and a slope.
        if(x_distance < 0){
            //right to left
            for(int i = end.getX(); i < start.getX(); i++){
                setPixel(i, ((slope * i) + y_intercept), 0x02);
            }
        } else {
            for(int i = start.getX(); i < end.getX(); i++){
                setPixel(i, ((slope * i) + y_intercept), 0x02);
            }
        }
    }
    
    setPixel(start.getX(), start.getY(), color);
    setPixel(end.getX(), end.getY(), color);
}

void Framebuffer::draw_polygon(Point points[], int num_points, Point origin, int rotation_degrees, int color){    
    //Draw a line between each of the points! That's a wireframe polygon.

    double s = sin(rotation_degrees * (PI / 180.0));
    double c = cos(rotation_degrees * (PI / 180.0));

    for(int i=0;i<num_points;i++){
        //Offset the points by the origin to give us the screen coordinates.        
        Point new_start = offset(points[i], origin);
        Point new_end = offset(points[(i+1) % num_points], origin);
        
        draw_line(new_start, new_end, color);
    }
}

void Framebuffer::draw_rectangle(Point origin, int width, int height, int thickness, int color){
    //Draw a rectangle at point Origin of Height*Width area Thickness pixels thick.
    for(int cur_thickness=0;cur_thickness<thickness;cur_thickness++){
        Point topLeft       = Point(origin.getX() + cur_thickness, origin.getY() + cur_thickness);
        Point topRight      = Point(origin.getX() + width - cur_thickness, origin.getY() + cur_thickness);
        Point bottomLeft    = Point(origin.getX() + cur_thickness, origin.getY() + height - cur_thickness);
        Point bottomRight   = Point(origin.getX() + width - cur_thickness, origin.getY() + height - cur_thickness);
        
        draw_line(topLeft, topRight, color);
        draw_line(topLeft, bottomLeft, color);
        draw_line(bottomLeft, bottomRight, color);
        draw_line(topRight, bottomRight, color);   
    }
}

void Framebuffer::draw_rectangle_filled(Point origin, int width, int height, int color){ 
    for(int i=0;i<height;i++){
        draw_line(Point(origin.getX(), origin.getY() + i), Point(origin.getX() + width, origin.getY() + i), color);
    }
}

void Framebuffer::setPixel(int x, int y, int color){
    unsigned int coord = (VGA_WIDTH * y) + x;
    pixels[coord] = color;
}


void Framebuffer::setPixel(Point point, int color){
    //Set an individual pixel to a color.
    pixels[(VGA_WIDTH * point.getY()) + point.getX()] = color; 
}

void Framebuffer::overlay(Framebuffer source, int size){
    //Copy one framebuffer on top of another.
    //Any pixels in the source of color 0x00 will be considered transparent.
    
    for(UInt32 i=0;i<size;i++){
        if(source.getPixels()[i] != 0x00){
            pixels[i] = source.getPixels()[i];
        }
    }
}

double getSlope(Point start, Point end){
    //m = (startY - endY) / (startX - endX)
    return (double)(start.getY() - end.getY()) / (start.getX() - end.getX());
}

double getYIntercept(Point start, double slope){
    //Where will a line of slope M that passes through point (X,Y) pass through Y=0?
    return start.getY() - (slope * start.getX());
}

Point offset(Point local, Point origin){
    Point point = Point(local.getX() + origin.getX(), local.getY() + origin.getY());
    return point;
}

Point rotate_degrees(Point point, int rotation_degrees){
    printf("\n%f, %f", point.getX(), point.getY());
    double s = sin(rotation_degrees * (PI / 180.0));
    double c = cos(rotation_degrees * (PI / 180.0));
    
    Point rotated = Point((point.getX() * c) + (point.getY() * s), (-point.getX() * s) + (point.getY() * c));
    printf("\n%f, %f -> %f, %f\n", point.getX(), point.getY(), rotated.getX(), rotated.getY());

    return rotated;
}

/* Font routines */
void Framebuffer::putGlyph(unsigned char *tile, int sizeX, int sizeY, int destX, int destY, int vga_color){ //8x8 font tile   
    long bytePos = (destY * 320) + destX;

    for(int y=0; y<sizeY; y++) {
        //for each row of the tile
        if(tile[y] & 0x80) {
            pixels[bytePos] = vga_color;
        } else {
            pixels[bytePos] = 0x00;
        }

        if(tile[y] & 0x40) {
            pixels[bytePos+1] = vga_color;
        } else {
            pixels[bytePos+1] = 0x00;
        }

        if(tile[y] & 0x20) {
            pixels[bytePos+2] = vga_color;
        } else {
            pixels[bytePos+2] = 0x00;
        }
        
        if(tile[y] & 0x10) {
            pixels[bytePos+3] = vga_color;
        } else {
            pixels[bytePos+3] = 0x00;
        }
        
        if(tile[y] & 0x08) {
            pixels[bytePos+4] = vga_color;
        } else {
            pixels[bytePos+4] = 0x00;
        }
        
        if(tile[y] & 0x04) {
            pixels[bytePos+5] = vga_color;
        } else {
            pixels[bytePos+5] = 0x00;
        }
        
        if(tile[y] & 0x02) {
            pixels[bytePos+6] = vga_color;
        } else {
            pixels[bytePos+6] = 0x00;
        }
        
        if(tile[y] & 0x01) {
            pixels[bytePos+7] = vga_color;
        } else {
            pixels[bytePos+7] = 0x00;
        }
        
        bytePos += 320;
    }
    
};

void Framebuffer::putString(const char *str, int len, Point destination, int vga_color, Font font){
    int sizeX = font.getSizeX();
    int sizeY = font.getSizeY();

    for(int i=0;i<len;i++){        
        putGlyph(font.getGlyph(str[i]), sizeX, sizeY, destination.getX()+(sizeX * i), destination.getY(), vga_color);
    }
}

void Framebuffer::putString(std::string str, Point destination, int color, Font font){
    putString(str.c_str(), str.length(), destination, color, font);
}
