#ifndef DEFENITIONS_H_INCLUDED
#define DEFENITIONS_H_INCLUDED

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "freetype.h"

#define HEIGHT  12
#define WIDTH   HEIGHT*4

#define CELL_WIDTH  0.6
#define RADIUS      19

#define IDLE    40000

enum Type {
    CLEAN,
    TAIL,
    POINT,
    OVER
};

enum Direction {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum Coords {
    X = 0,
    Y = 1,
    Z = 2
};

enum GameState {
    PLAY,
    STOP,
    MENU
};

#endif // DEFENITIONS_H_INCLUDED