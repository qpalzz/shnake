#ifndef TAIL_H_INCLUDED
#define TAIL_H_INCLUDED

#include "cell.h"

class Tail {
    private:
        int i,j;
        Tail *next;
        Type type;
        Direction direct;

    protected:
        void ClearProjection(Cell f[HEIGHT][WIDTH]); // очистка текущей ячейки на поле f
        void GetNext(int *next_i, int *next_j);
        void Move(Cell f[HEIGHT][WIDTH]); // очищает текущую точку, двигает текущую точку и следующую

    public:
        Tail();
        void SetParams(int i, int j, Type t, Direction d);
        void Projection(Cell f[HEIGHT][WIDTH]); // проецировать часть змейки на поле f и следующий
        void SetDirection(Direction d); // передать следующему свое направление и установить себе новое
        Type MoveHead(Cell f[HEIGHT][WIDTH]); // вызывается для головы змейки
                                // двигает в соответств. направлении,
                                // если на следующей ячейке не CLEAN, то возвращает ее тип,
                                // иначе двигает хвост защищенным методом Move
};

#endif // TAIL_H_INCLUDED
