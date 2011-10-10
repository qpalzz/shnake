#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED

#include "defenitions.h"

class Cell {
    private:
        GLfloat a[3], // левая нижняя точка
                b[3], // правая нижняя
                c[3], // правая верхняя
                d[3]; // левая верхняя
        Type type;

    public:
        Cell();
        void SetPoints(GLfloat *,GLfloat *,GLfloat *,GLfloat *);
        void SetType(Type t);
        Type GetType() const;
        void Draw();
        void GetPoint(GLfloat n[3]);
};

#endif // CELL_H_INCLUDED
