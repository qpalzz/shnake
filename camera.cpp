#include "camera.h"

Camera::Camera(GLfloat start[3])
{
    count_f = 1;
    animation[0][X] = start[X];
    animation[0][Y] = start[Y];
    animation[0][Z] = start[Z];
    loop = FALSE;
    anim = 0;
    radius = RADIUS;
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
        GLfloat r = radius / sqrt(animation[i][X]*animation[i][X]
                                  + animation[i][Y]*animation[i][Y]
                                  + animation[i][Z]*animation[i][Z]);
        animation[i][X] *= r;
        animation[i][Y] *= r;
        animation[i][Z] *= r;
    }
    anim = 0;
}

void Camera::StepAnimation()
{
    if (anim < count_f-1) {
        anim++;
    }
    else {
        if (loop) {
            anim = 0;
        }
    }
}

void Camera::View()
{
    glLoadIdentity();

    gluLookAt( animation[anim][X],animation[anim][Y],animation[anim][Z], 0,0,0, 0,1,0 );
}
