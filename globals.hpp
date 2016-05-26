// GLOBALS.H
//
// Global Include file

//#if !defined( GLOBALS_H )
//#define GLOBALS_H

#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <vector>
#include <string>

double PI = 3.14159265;

/******** Common Type Definitons ********/
// unsigned types
typedef unsigned char         Byte;
typedef unsigned short        UInt16;
typedef unsigned long         UInt32;
typedef unsigned long long    UInt64;
// signed types
typedef signed char           SByte;
typedef signed short          Int16;
typedef signed long           Int32;
typedef signed long long      Int64;

#include "shapes\shapes.hpp"

/*
#include "colors.hpp"
#include "defines.hpp"
#include "scorched.hpp"
#include "video.hpp"
#include "mouse.hpp"
#include "colors.hpp"
#include "fonts\font.hpp"
#include "shapes\point.hpp"
#include "shapes\shapes.hpp"
#include "video.hpp"
#include "widgets\widget.hpp"
#include "scorched.hpp"
*/

//Global data
char messages[64][4];
std::vector<Shape> shapesList;

#endif
