#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "tail.h"

class Game {
    private:
        Cell f[HEIGHT][WIDTH];

        int score;
        Direction direct;

        Tail head;
        Tail point;

    protected:
        void InitGraphic();
    public:
        Game(); // инициализация поля, установка головы и точки
        void Draw(); // вывод на экран поля (проецирование змеи на поле,
                     // установка камеры, вывод ячеек
        void Move(); // сдвиг змеи начиная с головы, обработка наступления головы на что-то кроме CLEAN
                     // перестановка направления

        void SetDirection(Direction d);
};

#endif // GAME_H_INCLUDED
