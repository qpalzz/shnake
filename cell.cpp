#include "cell.h"

Cell::Cell()
{
    a[0] = 0;
    a[1] = 0;
    a[2] = 0;

    b[0] = 0;
    b[1] = 0;
    b[2] = 0;

    c[0] = 0;
    c[1] = 0;
    c[2] = 0;

    d[0] = 0;
    d[1] = 0;
    d[2] = 0;

    type = CLEAN;
}
void Cell::SetPoints(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d)
{
    this->a[0] = a[0];
    this->a[1] = a[1];
    this->a[2] = a[2];

    this->b[0] = b[0];
    this->b[1] = b[1];
    this->b[2] = b[2];

    this->c[0] = c[0];
    this->c[1] = c[1];
    this->c[2] = c[2];

    this->d[0] = d[0];
    this->d[1] = d[1];
    this->d[2] = d[2];
}

void Cell::SetType(Type t)
{
    this->type = t;
}

Type Cell::GetType() const
{
    return type;
}

void Cell::Draw()
{
    GLfloat color_fill[4] = { 0.0, 0.0, 0.0, 0.3 };
    GLfloat color_border[4] = { 0.0, 0.0, 0.0, 0.6 };
    switch (type) {
        case CLEAN:
            color_fill[2] = 1;
            color_border[2] = 1;
            break;
        case TAIL:
            color_fill[1] = 1;
            color_border[1] = 1;
            break;
        case POINT:
            color_fill[0] = 1;
            color_border[0] = 1;
            break;
    }
    glColor4fv(color_fill);
    glBegin(GL_QUADS);
        glVertex3fv(a);
        glVertex3fv(b);
        glVertex3fv(c);
        glVertex3fv(d);
    glEnd();
    glColor4fv(color_border);
    glBegin(GL_LINE_LOOP);
        glVertex3fv(a);
        glVertex3fv(b);
        glVertex3fv(c);
        glVertex3fv(d);
    glEnd();
}
