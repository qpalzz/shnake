#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "defs.h"

class Camera {
    private:
        GLfloat radius;
        GLfloat animation[COUNT_STEPS][3];
        int anim; // шаг анимации
        int count_f; // количество кадров в текущей анимации
        gboolean loop; // зацикливать ли анимацию

    public:
        Camera(GLfloat start[3]);
        void View(); // установка положения камеры
        void CalcAnimation(GLfloat start[3], GLfloat end[3], int count);
        void StepAnimation();

};

#endif // CAMERA_H_INCLUDED
