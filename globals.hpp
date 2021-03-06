// GLOBALS.H
//
// Global Include file

//#if !defined( GLOBALS_H )
//#define GLOBALS_H

#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <vector>
#include <string>

#include "serial.hpp"
#include "pcx.hpp"
#include "framebuffer.hpp"
#include "screen.hpp"
#include "fonts\font.hpp"
#include "shapes\shapes.hpp"
#include "widgets\widget.hpp"

//Global data
char messages[64][4];
std::vector<Shape> shapesList;

Screen g_screen;

//Framebuffer layer_background;
//Framebuffer layer_text;
//Framebuffer layer_final;
//Framebuffer layer_trigger;

int needsRedraw = false;
#endif
