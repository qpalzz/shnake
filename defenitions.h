#ifndef DEFENITIONS_H_INCLUDED
#define DEFENITIONS_H_INCLUDED

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define HEIGHT  10
#define WIDTH   HEIGHT*4

#define CELL_WIDTH  0.5

enum Type {
    CLEAN,
    TAIL,
    POINT
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

#endif // DEFENITIONS_H_INCLUDED
