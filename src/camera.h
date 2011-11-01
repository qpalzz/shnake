#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "defs.h"
#include "config.h"

class Camera {
    private:
        GLfloat animation[COUNT_STEPS][3];
        GLfloat radius_an[COUNT_STEPS];
        GLfloat rad;
        int anim; // шаг анимации
        int count_f; // количество кадров в текущей анимации
        gboolean loop; // зацикливать ли анимацию

    public:
        Camera(GLfloat start[3]);
        void View(); // установка положения камеры
        void CalcAnimation(GLfloat start[3], GLfloat end[3], int count);
        void CalcAnimation(GLfloat start[3], GLfloat end[3], GLfloat radius, int count);
        int StepAnimation();

};

#endif // CAMERA_H_INCLUDED
