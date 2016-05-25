#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <graph.h>
#include <dos.h>
#include <fcntl.h>
#include <io.h>

#ifndef POINT_HPP
#define POINT_HPP

class Point {
    long x;
    long y;

    public:
        Point();
        Point(long, long);
        Point(char*);
        long getX() { return x; };
        long getY() { return y; };
};

#endif

