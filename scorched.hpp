#ifndef SCORCHED_HPP
#define SCORCHED_HPP

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <graph.h>
#include <dos.h>
#include <fcntl.h>
#include <io.h>

#include "globals.hpp"
#include "defines.hpp"
#include "framebuffer.hpp"
#include "mouse.hpp"
#include "fonts\font.hpp"
#include "widgets\button.hpp"

void scorched_earth();
void draw_ground(Framebuffer framebuffer);
void read_shape(char *buffer, int shapeNum);
void redraw_screen();
void exit_program(std::string msg);

#endif SCORCHED_HPP
