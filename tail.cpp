#include "tail.h"

Tail::Tail()
{
    i = 0;
    j = 0;

    next = NULL;

    type = CLEAN;
    direct = NONE;
}

void Tail::SetParams(int i, int j, Type t, Direction d)
{
    this->i = i;
    this->j = j;
    this->type = t;
    this->direct = d;
}

void Tail::Projection(Cell f[HEIGHT][WIDTH])
{
    f[i][j].SetType(type);
    if (next) next->Projection(f);
}

void Tail::SetDirection(Direction d)
{
    if (next) next->SetDirection(direct);
    direct = d;
}

Type Tail::MoveHead(Cell f[HEIGHT][WIDTH])
{

    int step_i, step_j;
    GetNext(&step_i, &step_j);
    Type t = f[step_i][step_j].GetType();
    Move(f);
    return t;
}


void Tail::SetType(Type t)
{
    type = t;
}

void Tail::SetNext(Tail *n)
{
    next = n;
}

void Tail::GetPoint(Cell f[HEIGHT][WIDTH], GLfloat n[3])
{
    f[i][j].GetPoint(n);
}

void Tail::GetIJ(int *_i, int *_j)
{
    *_i = i;
    *_j = j;
}

// ----------------------- protected ------------------------------

void Tail::ClearProjection(Cell f[HEIGHT][WIDTH])
{
    f[i][j].SetType(CLEAN);
}

void Tail::GetNext(int *next_i, int *next_j)
{
    switch (direct) {
        case UP:
            *next_i = (i == 0)?HEIGHT-1:i-1;
            *next_j = j;
            break;
        case DOWN:
            *next_i = (i == HEIGHT-1)?0:i+1;
            *next_j = j;
            break;
        case LEFT:
            *next_i = i;
            *next_j = (j == 0)?WIDTH-1:j-1;
            break;
        case RIGHT:
            *next_i = i;
            *next_j = (j == WIDTH-1)?0:j+1;
            break;
        default:
            *next_i = i;
            *next_j = j;
            break;
    }
}

void Tail::Move(Cell f[HEIGHT][WIDTH])
{
    ClearProjection(f);
    GetNext(&i, &j);
    if (next) next->Move(f);
}
