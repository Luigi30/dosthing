#ifndef POINT_HPP
#define POINT_HPP

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <graph.h>
#include <dos.h>
#include <fcntl.h>
#include <io.h>

class Point {
    int x;
    int y;

    public:
        Point();
        Point(int, int);
        Point(char*);
        int getX() { return x; };
        int getY() { return y; };
};

#endif

