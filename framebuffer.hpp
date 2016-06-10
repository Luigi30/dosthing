#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include <math.h>

#include "defines.hpp"
#include "fonts\font.hpp"
#include "shapes\shapes.hpp"

class Framebuffer {
    unsigned char *pixels;

    public:
    void draw_line(Point, Point, int);
    void draw_polygon(Point points[], int num_points, Point origin, int rotation_angle, int color);
    void draw_rectangle(Point, int, int, int, int);
    void draw_rectangle_filled(Point, int, int, int);
    void draw_area(unsigned char *source, Point start, Size2D size);
    void setPixel(Point, int);
    void setPixel(int, int, int);
    void overlay(Framebuffer source, int size);
    unsigned char *getPixels();

    void putString(const char *str, int len, Point destination, int vga_color, Font font);
    void putString(std::string str, Point destination, int color, Font font);
    void putGlyph(unsigned char *tile, int sizeX, int sizeY, int destX, int destY, int vga_color);

    Framebuffer();
};

//drawing routines
double getSlope(Point, Point);
double getYIntercept(Point, double);
Point offset(Point, Point);

#endif
