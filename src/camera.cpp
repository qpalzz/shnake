#include "camera.h"

Camera::Camera(GLfloat start[3])
{
    count_f = 1;
    animation[0][X] = start[X];
    animation[0][Y] = start[Y];
    animation[0][Z] = start[Z];
    loop = FALSE;
    anim = 0;
    for (int i = 0; i < COUNT_STEPS; i++) {
        radius_an[i] = RADIUS_START;
    }
    rad = RADIUS_START;
}

void Camera::CalcAnimation(GLfloat start[3], GLfloat end[3], int count)
{
    GLfloat dN[3];
    count_f = count;
    dN[X] = (end[X] - start[X]) / count_f;
    dN[Y] = (end[Y] - start[Y]) / count_f;
    dN[Z] = (end[Z] - start[Z]) / count_f;



    for (int i = 0; i < count_f; i++) {
        animation[i][X] = start[X] + dN[X]*i;
        animation[i][Y] = start[Y] + dN[Y]*i;
        animation[i][Z] = start[Z] + dN[Z]*i;
        GLfloat r = radius_an[i] / sqrt(animation[i][X]*animation[i][X]
                                  + animation[i][Y]*animation[i][Y]
                                  + animation[i][Z]*animation[i][Z]);
        animation[i][X] *= r;
        animation[i][Y] *= r;
        animation[i][Z] *= r;
    }
    for (int i = 0; i < count_f; i++) {
        radius_an[i] = rad;
    }
    anim = 0;
}

void Camera::CalcAnimation(GLfloat start[3], GLfloat end[3], GLfloat radius, int count)
{
    GLfloat dR = (radius - rad) / (GLfloat)count;
    for (int i = 0; i < count; i++)
    {
        radius_an[i] = rad + i*dR;
    }
    rad = radius_an[count-1];
    CalcAnimation(start, end, count);
}

int Camera::StepAnimation()
{
    if (anim < count_f-1) {
        anim++;
    }
    else {
        if (loop) {
            anim = 0;
        }
        else return TRUE;
    }
    return FALSE;
}

void Camera::View()
{
    glLoadIdentity();

    gluLookAt( animation[anim][X],animation[anim][Y],animation[anim][Z], 0,0,0, 0,1,0 );
}
