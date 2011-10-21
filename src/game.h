#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "tail.h"
#include "camera.h"

class Game {
    private:
        Cell f[HEIGHT][WIDTH];

        int score;
        GameState state;
        Direction direct;

        Tail *head;
        Tail *point;

        freetype::font_data our_font;

        bool moved;

        Camera *camera;

    protected:
        void InitGraphic();
        void DrawField();
        void DrawFace0(); // передняя грань
        void DrawFace1(); // правая грань
        void DrawFace2(); // задняя грань
        void DrawFace3(); // левая грань
        void ClearGame(); // удвление змейки, установка начальных значений
        void DeleteShnake();
        void GameInit();
    public:
        Game(); // инициализация поля, установка головы и точки
        ~Game();
        void Draw(); // вывод на экран поля (проецирование змеи на поле,
                     // установка камеры, вывод ячеек
        void Move(); // сдвиг змеи начиная с головы, обработка наступления головы на что-то кроме CLEAN
                     // перестановка направления

        void SetDirection(Direction d);

        GameState GetState();

        void New();
        void Start();
        void Pause();
};

#endif // GAME_H_INCLUDED
