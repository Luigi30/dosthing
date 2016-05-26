#include "video.hpp"

#include <math.h>

void setPixel(char *framebuffer, int x, int y, int color){
    unsigned int coord = (VGA_WIDTH * y) + x;
    framebuffer[coord] = color;
}

void init_framebuffer(char *framebuffer, UInt32 size){
    framebuffer = (char*)malloc(size);
    memset(framebuffer, 0, size);
}

void overlay_framebuffers(char *destination, char *source, UInt32 size){
    //Copy one framebuffer on top of another.
    //Any pixels in the source of color 0x00 will be considered transparent.
    
    for(UInt32 i=0;i<size;i++){
        if(source[i] != 0x00){
            destination[i] = source[i];
        }
    }
}

void draw_point(char *framebuffer, Point point, int color){
    //Set an individual pixel to a color.
    //setPixel(framebuffer, point.getX(), point.getY(), color);
    framebuffer[(320*point.getY()) + point.getX()] = color; 
}

void draw_line(char *framebuffer, Point start, Point end, int color){
    //Draw a 1-pixel thick line between two points.
    int x_distance = end.getX() - start.getX();
    int y_distance = end.getY() - start.getY();

    //is this a vertical line?
    if(x_distance == 0){
        for(int i=start.getY(); i<end.getY(); i++){
            setPixel(framebuffer, start.getX(), i, color);
        }
    } else if (y_distance == 0) {
        //is this a horizontal line?
        int y = start.getY();

        for(int i=0;i<x_distance;i++) {
            setPixel(framebuffer, start.getX() + i, y, color);
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
                setPixel(framebuffer, i, ((slope * i) + y_intercept), 0x02);
            }
        } else {
            for(int i = start.getX(); i < end.getX(); i++){
                setPixel(framebuffer, i, ((slope * i) + y_intercept), 0x02);
            }
        }
    }
    
    setPixel(framebuffer, start.getX(), start.getY(), color);
    setPixel(framebuffer, end.getX(), end.getY(), color);
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

void draw_polygon(char *framebuffer, Point points[], int num_points, Point origin, int rotation_degrees, int color){    
    //Draw a line between each of the points! That's a wireframe polygon.

    double s = sin(rotation_degrees * (PI / 180.0));
    double c = cos(rotation_degrees * (PI / 180.0));

    for(int i=0;i<num_points;i++){
        //Offset the points by the origin to give us the screen coordinates.        
        Point new_start = offset(points[i], origin);
        Point new_end = offset(points[(i+1) % num_points], origin);
        
        draw_line(framebuffer, new_start, new_end, color);
    }
}

void draw_rectangle(char *framebuffer, Point origin, int width, int height, int thickness, int color){
    //Draw a rectangle at point Origin of Height*Width area Thickness pixels thick.
    for(int cur_thickness=0;cur_thickness<thickness;cur_thickness++){
        Point topLeft       = Point(origin.getX() + cur_thickness, origin.getY() + cur_thickness);
        Point topRight      = Point(origin.getX() + width - cur_thickness, origin.getY() + cur_thickness);
        Point bottomLeft    = Point(origin.getX() + cur_thickness, origin.getY() + height - cur_thickness);
        Point bottomRight   = Point(origin.getX() + width - cur_thickness, origin.getY() + height - cur_thickness);
        
        draw_line(framebuffer, topLeft, topRight, color);
        draw_line(framebuffer, topLeft, bottomLeft, color);
        draw_line(framebuffer, bottomLeft, bottomRight, color);
        draw_line(framebuffer, topRight, bottomRight, color);   
    }
}

void draw_rectangle_filled(char *framebuffer, Point origin, int width, int height, int color){ 
    for(int i=0;i<height;i++){
        draw_line(framebuffer, Point(origin.getX(), origin.getY() + i), Point(origin.getX() + width, origin.getY() + i), color);
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
