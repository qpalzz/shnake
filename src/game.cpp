#include "game.h"

Game::Game()
{
    Config *conf = Config::Instance();
    GLfloat c_width = (GLfloat)conf->cell_width;

    our_font.init("AlphaMaleModern.ttf", 26); // Создать шрифт FreeType

    for (int i = 0; i < HEIGHT; i++) {
        GLfloat a[3],
                b[3],
                c[3],
                d[3];
        for (int j = 0; j < HEIGHT; j++) { // передняя грань
            a[X] = -(HEIGHT/2)*c_width + j*c_width + 0.1*c_width;
            a[Y] = -(HEIGHT/2)*c_width + i*c_width + 0.1*c_width;
            a[Z] = (HEIGHT/2)*c_width;

            b[X] = -(HEIGHT/2)*c_width + c_width + j*c_width - 0.1*c_width;
            b[Y] = -(HEIGHT/2)*c_width + i*c_width + 0.1*c_width;
            b[Z] = (HEIGHT/2)*c_width;

            c[X] = -(HEIGHT/2)*c_width + c_width + j*c_width - 0.1*c_width;
            c[Y] = -(HEIGHT/2)*c_width + c_width + i*c_width - 0.1*c_width;
            c[Z] = (HEIGHT/2)*c_width;

            d[X] = -(HEIGHT/2)*c_width + j*c_width + 0.1*c_width;
            d[Y] = -(HEIGHT/2)*c_width + c_width + i*c_width - 0.1*c_width;
            d[Z] = (HEIGHT/2)*c_width;

            f[i][j].SetPoints(a,b,c,d);
        }
        for (int j = HEIGHT; j < HEIGHT*2; j++) { // правая грань
            a[X] = (HEIGHT/2)*c_width;
            a[Y] = -(HEIGHT/2)*c_width + i*c_width + 0.1*c_width;
            a[Z] = (HEIGHT/2)*c_width - (j%HEIGHT)*c_width - 0.1*c_width;

            b[X] = (HEIGHT/2)*c_width;
            b[Y] = -(HEIGHT/2)*c_width + i*c_width + 0.1*c_width;
            b[Z] = (HEIGHT/2)*c_width - c_width - (j%HEIGHT)*c_width + 0.1*c_width;

            c[X] = (HEIGHT/2)*c_width;
            c[Y] = -(HEIGHT/2)*c_width + c_width + i*c_width - 0.1*c_width;
            c[Z] = (HEIGHT/2)*c_width - c_width - (j%HEIGHT)*c_width + 0.1*c_width;

            d[X] = (HEIGHT/2)*c_width;
            d[Y] = -(HEIGHT/2)*c_width + c_width + i*c_width - 0.1*c_width;
            d[Z] = (HEIGHT/2)*c_width - (j%HEIGHT)*c_width - 0.1*c_width;

            f[i][j].SetPoints(a,b,c,d);
        }
        for (int j = HEIGHT*2; j < HEIGHT*3; j++) { // задняя грань
            a[X] = (HEIGHT/2)*c_width - (j%HEIGHT)*c_width - 0.1*c_width;
            a[Y] = -(HEIGHT/2)*c_width + i*c_width + 0.1*c_width;
            a[Z] = -(HEIGHT/2)*c_width;

            b[X] = (HEIGHT/2)*c_width - c_width - (j%HEIGHT)*c_width + 0.1*c_width;
            b[Y] = -(HEIGHT/2)*c_width + i*c_width + 0.1*c_width;
            b[Z] = -(HEIGHT/2)*c_width;

            c[X] = (HEIGHT/2)*c_width - c_width - (j%HEIGHT)*c_width + 0.1*c_width;
            c[Y] = -(HEIGHT/2)*c_width + c_width + i*c_width - 0.1*c_width;
            c[Z] = -(HEIGHT/2)*c_width;

            d[X] = (HEIGHT/2)*c_width - (j%HEIGHT)*c_width - 0.1*c_width;
            d[Y] = -(HEIGHT/2)*c_width + c_width + i*c_width - 0.1*c_width;
            d[Z] = -(HEIGHT/2)*c_width;

            f[i][j].SetPoints(a,b,c,d);
        }
        for (int j = HEIGHT*3; j < WIDTH; j++) { // левая грань
            a[X] = -(HEIGHT/2)*c_width;
            a[Y] = -(HEIGHT/2)*c_width + i*c_width + 0.1*c_width;
            a[Z] = -(HEIGHT/2)*c_width + (j%HEIGHT)*c_width + 0.1*c_width;

            b[X] = -(HEIGHT/2)*c_width;
            b[Y] = -(HEIGHT/2)*c_width + i*c_width + 0.1*c_width;
            b[Z] = -(HEIGHT/2)*c_width + c_width + (j%HEIGHT)*c_width - 0.1*c_width;

            c[X] = -(HEIGHT/2)*c_width;
            c[Y] = -(HEIGHT/2)*c_width + c_width + i*c_width - 0.1*c_width;
            c[Z] = -(HEIGHT/2)*c_width + c_width + (j%HEIGHT)*c_width - 0.1*c_width;

            d[X] = -(HEIGHT/2)*c_width;
            d[Y] = -(HEIGHT/2)*c_width + c_width + i*c_width - 0.1*c_width;
            d[Z] = -(HEIGHT/2)*c_width + (j%HEIGHT)*c_width + 0.1*c_width;

            f[i][j].SetPoints(a,b,c,d);
        }
    }

    GameInit();

    InitGraphic();
}

Game::~Game()
{
    DeleteShnake();
}

void Game::Draw()
{
    head->Projection(f);
    point->Projection(f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera->View();
//    camera->StepAnimation()

    switch (state) {
        case NEW:
            // не делать шаги камеры
            break;
        case START:
            if (camera->StepAnimation()) // пока не пройдет стартовая анимация
                state = PLAY;
            break;
        case PLAY:
            camera->StepAnimation();
            break;
        case PAUSE:
            // не делать шаги камеры
            break;
        case END:
            if (camera->StepAnimation()) // пока не пройдет финишная анимация
                state = STOP;
            break;
        case STOP:
            // не делать шаги камеры
            break;
    }

    DrawField();


    glLoadIdentity();

    glColor3ub(0,0xff,0);
    freetype::print(our_font, 30, 30, "SCORE: %d", score);
}

void Game::Move()
{
    if (state == PLAY) {
        moved = true;
        head->SetDirection(direct);

        GLfloat start[3];
        head->GetPoint(f,start);

        Type t = head->MoveHead(f);

        GLfloat end[3];
        head->GetPoint(f,end);
        camera->CalcAnimation(start, end, COUNT_FRAMES);

        if (t == POINT) {
            point->SetType(TAIL);
            point->SetNext(head);
            head = point;

            point = new Tail;
            point->SetParams(rand()%HEIGHT, rand()%WIDTH, POINT, NONE);

            score += 100;
        }
        else if (t == TAIL) {
            GameEnd();
        }
    }
}

void Game::SetDirection(Direction d)
{
    if (moved && ((d == UP && direct != DOWN) || (d == DOWN && direct != UP) ||
        (d == RIGHT && direct != LEFT) || (d == LEFT && direct != RIGHT))) {
        direct = d;
        moved = !moved;
    }
}

GameState Game::GetState()
{
    return state;
}

void Game::New()
{
    ClearGame();
    state = NEW;
}

void Game::Start()
{
    if (state == NEW) state = START;
}

void Game::Pause()
{
    if (state == PAUSE) state = PLAY;
    else if (state == PLAY) state = PAUSE;
}

void Game::End()
{
    if (state != END) GameEnd();
}
// --------------- protected ------------------------------------

void Game::InitGraphic()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LINE_SMOOTH | GL_DEPTH_TEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

void Game::DrawField()
{
    int I,J;
    head->GetIJ(&I,&J);
    if (J / HEIGHT == 0) {
        DrawFace2();
        DrawFace3();
        DrawFace1();
        DrawFace0();
    }
    if (J / HEIGHT == 1) {
        DrawFace3();
        DrawFace2();
        DrawFace0();
        DrawFace1();
    }
    if (J / HEIGHT == 2) {
        DrawFace0();
        DrawFace1();
        DrawFace3();
        DrawFace2();
    }
    if (J / HEIGHT == 3) {
        DrawFace1();
        DrawFace2();
        DrawFace0();
        DrawFace3();
    }
}

void Game::DrawFace0() // передняя грань
{
    for (int i = 0; i < HEIGHT; i++) { // передняя грань
        for (int j = HEIGHT*0; j < HEIGHT*1; j++) {
            f[i][j].Draw();
        }
    }
}

void Game::DrawFace1() // правая грань
{
    for (int i = 0; i < HEIGHT; i++) { // правая грань
        for (int j = HEIGHT; j < HEIGHT*2; j++) {
            f[i][j].Draw();
        }
    }
}

void Game::DrawFace2() // задняя грань
{
    for (int i = 0; i < HEIGHT; i++) { // задняя грань
        for (int j = HEIGHT*2; j < HEIGHT*3; j++) {
            f[i][j].Draw();
        }
    }
}

void Game::DrawFace3() // левая грань
{
    for (int i = 0; i < HEIGHT; i++) { // левая грань
        for (int j = HEIGHT*3; j < WIDTH; j++) {
            f[i][j].Draw();
        }
    }
}

void Game::ClearGame()
{
    DeleteShnake();
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            f[i][j].SetType(CLEAN);
        }
    }
    GameInit();
}

void Game::DeleteShnake()
{
    while (head) {
        Tail *tmp = head->GetNext();
        delete []head;
        head = tmp;
    }
    delete []point;
    delete []camera;
}

void Game::GameInit()
{
    Config *conf = Config::Instance();

    score = 0;
    direct = LEFT;
    state = NEW;

    head = new Tail();
    point = new Tail();

    head->SetParams(HEIGHT / 2, HEIGHT / 2, TAIL, direct);

    GLfloat start[3];
    head->GetPoint(f,start);
    camera = new Camera(start);
    GLfloat end[3];
            end[X] = start[X];
            end[Y] = HEIGHT*conf->cell_width / 2.5;
            end[Z] = start[Z];
    camera->CalcAnimation(end, start, conf->radius, 15);
    point->SetParams(rand()%HEIGHT, rand()%HEIGHT, POINT, NONE);
}

void Game::GameEnd()
{
    Config *conf = Config::Instance();

    GLfloat start[3];
    head->GetPoint(f,start);
    state = END;
    head->SetType(OVER);
    GLfloat end[3];
    end[X] = start[X];
    end[Y] = HEIGHT*conf->cell_width / 2.5;
    end[Z] = start[Z];
    camera->CalcAnimation(start, end, conf->radius_start, 15);
}
