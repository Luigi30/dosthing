#ifndef VIDEO_HPP
#define VIDEO_HPP

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <graph.h>
#include <dos.h>
#include <fcntl.h>
#include <io.h>

#include "globals.hpp"

void init_framebuffer(char*, UInt32);
void setPixel(char*, int, int, int);
void overlay_framebuffers(char*, char*, UInt32);

//drawing routines
void draw_point(char*, Point, int);
void draw_line(char*, Point, Point, int);
void draw_polygon(char *framebuffer, Point points[], int num_points, Point origin, int rotation_angle, int color);
void draw_rectangle(char*, Point, int, int, int, int);
void draw_rectangle_filled(char*, Point, int, int, int);

double getSlope(Point, Point);
double getYIntercept(Point, double);

#endif

