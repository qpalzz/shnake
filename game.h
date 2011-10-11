#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "tail.h"

class Game {
    private:
        Cell f[HEIGHT][WIDTH];

        int score;
        GameState state;
        Direction direct;

        Tail *head;
        Tail *point;

        freetype::font_data our_font;

    protected:
        void InitGraphic();
        void DrawField();
        void DrawFace0(); // передняя грань
        void DrawFace1(); // правая грань
        void DrawFace2(); // задняя грань
        void DrawFace3(); // левая грань
    public:
        Game(); // инициализация поля, установка головы и точки
        void Draw(); // вывод на экран поля (проецирование змеи на поле,
                     // установка камеры, вывод ячеек
        void Move(); // сдвиг змеи начиная с головы, обработка наступления головы на что-то кроме CLEAN
                     // перестановка направления

        void SetDirection(Direction d);
};

#endif // GAME_H_INCLUDED
