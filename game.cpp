#include "game.h"

Game::Game()
{
    score = 0;
    direct = LEFT;
    state = PLAY;

    for (int i = 0; i < HEIGHT; i++) {
        GLfloat a[3],
                b[3],
                c[3],
                d[3];
        for (int j = 0; j < HEIGHT; j++) { // передняя грань
            a[X] = -(HEIGHT/2)*CELL_WIDTH + j*CELL_WIDTH;
            a[Y] = -(HEIGHT/2)*CELL_WIDTH + i*CELL_WIDTH;
            a[Z] = (HEIGHT/2)*CELL_WIDTH;

            b[X] = -(HEIGHT/2)*CELL_WIDTH + CELL_WIDTH + j*CELL_WIDTH;
            b[Y] = -(HEIGHT/2)*CELL_WIDTH + i*CELL_WIDTH;
            b[Z] = (HEIGHT/2)*CELL_WIDTH;

            c[X] = -(HEIGHT/2)*CELL_WIDTH + CELL_WIDTH + j*CELL_WIDTH;
            c[Y] = -(HEIGHT/2)*CELL_WIDTH + CELL_WIDTH + i*CELL_WIDTH;
            c[Z] = (HEIGHT/2)*CELL_WIDTH;

            d[X] = -(HEIGHT/2)*CELL_WIDTH + j*CELL_WIDTH;
            d[Y] = -(HEIGHT/2)*CELL_WIDTH + CELL_WIDTH + i*CELL_WIDTH;
            d[Z] = (HEIGHT/2)*CELL_WIDTH;

            f[i][j].SetPoints(a,b,c,d);
        }
        for (int j = HEIGHT; j < HEIGHT*2; j++) { // правая грань
            a[X] = (HEIGHT/2)*CELL_WIDTH;
            a[Y] = -(HEIGHT/2)*CELL_WIDTH + i*CELL_WIDTH;
            a[Z] = (HEIGHT/2)*CELL_WIDTH - (j%HEIGHT)*CELL_WIDTH;

            b[X] = (HEIGHT/2)*CELL_WIDTH;
            b[Y] = -(HEIGHT/2)*CELL_WIDTH + i*CELL_WIDTH;
            b[Z] = (HEIGHT/2)*CELL_WIDTH - CELL_WIDTH - (j%HEIGHT)*CELL_WIDTH;

            c[X] = (HEIGHT/2)*CELL_WIDTH;
            c[Y] = -(HEIGHT/2)*CELL_WIDTH + CELL_WIDTH + i*CELL_WIDTH;
            c[Z] = (HEIGHT/2)*CELL_WIDTH - CELL_WIDTH - (j%HEIGHT)*CELL_WIDTH;

            d[X] = (HEIGHT/2)*CELL_WIDTH;
            d[Y] = -(HEIGHT/2)*CELL_WIDTH + CELL_WIDTH + i*CELL_WIDTH;
            d[Z] = (HEIGHT/2)*CELL_WIDTH - (j%HEIGHT)*CELL_WIDTH;

            f[i][j].SetPoints(a,b,c,d);
        }
        for (int j = HEIGHT*2; j < HEIGHT*3; j++) { // задняя грань
            a[X] = (HEIGHT/2)*CELL_WIDTH - (j%HEIGHT)*CELL_WIDTH;
            a[Y] = -(HEIGHT/2)*CELL_WIDTH + i*CELL_WIDTH;
            a[Z] = -(HEIGHT/2)*CELL_WIDTH;

            b[X] = (HEIGHT/2)*CELL_WIDTH - CELL_WIDTH - (j%HEIGHT)*CELL_WIDTH;
            b[Y] = -(HEIGHT/2)*CELL_WIDTH + i*CELL_WIDTH;
            b[Z] = -(HEIGHT/2)*CELL_WIDTH;

            c[X] = (HEIGHT/2)*CELL_WIDTH - CELL_WIDTH - (j%HEIGHT)*CELL_WIDTH;
            c[Y] = -(HEIGHT/2)*CELL_WIDTH + CELL_WIDTH + i*CELL_WIDTH;
            c[Z] = -(HEIGHT/2)*CELL_WIDTH;

            d[X] = (HEIGHT/2)*CELL_WIDTH - (j%HEIGHT)*CELL_WIDTH;
            d[Y] = -(HEIGHT/2)*CELL_WIDTH + CELL_WIDTH + i*CELL_WIDTH;
            d[Z] = -(HEIGHT/2)*CELL_WIDTH;

            f[i][j].SetPoints(a,b,c,d);
        }
        for (int j = HEIGHT*3; j < WIDTH; j++) { // левая грань
            a[X] = -(HEIGHT/2)*CELL_WIDTH;
            a[Y] = -(HEIGHT/2)*CELL_WIDTH + i*CELL_WIDTH;
            a[Z] = -(HEIGHT/2)*CELL_WIDTH + (j%HEIGHT)*CELL_WIDTH;

            b[X] = -(HEIGHT/2)*CELL_WIDTH;
            b[Y] = -(HEIGHT/2)*CELL_WIDTH + i*CELL_WIDTH;
            b[Z] = -(HEIGHT/2)*CELL_WIDTH + CELL_WIDTH + (j%HEIGHT)*CELL_WIDTH;

            c[X] = -(HEIGHT/2)*CELL_WIDTH;
            c[Y] = -(HEIGHT/2)*CELL_WIDTH + CELL_WIDTH + i*CELL_WIDTH;
            c[Z] = -(HEIGHT/2)*CELL_WIDTH + CELL_WIDTH + (j%HEIGHT)*CELL_WIDTH;

            d[X] = -(HEIGHT/2)*CELL_WIDTH;
            d[Y] = -(HEIGHT/2)*CELL_WIDTH + CELL_WIDTH + i*CELL_WIDTH;
            d[Z] = -(HEIGHT/2)*CELL_WIDTH + (j%HEIGHT)*CELL_WIDTH;

            f[i][j].SetPoints(a,b,c,d);
        }
    }

    head = new Tail();
    point = new Tail();
    head->SetParams(HEIGHT / 2, HEIGHT / 2, TAIL, direct);
    point->SetParams(2, 2, POINT, NONE);

    InitGraphic();
}

void Game::Draw()
{
    head->Projection(f);
    point->Projection(f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    GLfloat norm[3];
    head->GetPoint(f,norm);
    GLfloat r = RADIUS / sqrt(norm[X]*norm[X] + norm[Y]*norm[Y] + norm[Z]*norm[Z]);
    norm[X] *= r;
    norm[Y] *= r;
    norm[Z] *= r;

	gluLookAt( norm[X],norm[Y],norm[Z], 0,0,0, 0,1,0 );

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            f[i][j].Draw();
        }
    }
}

void Game::Move()
{
    if (state == PLAY) {
        head->SetDirection(direct);

        Type t = head->MoveHead(f);
        if (t == POINT) {
            point->SetType(TAIL);
            point->SetNext(head);
            head = point;

            point = new Tail;
            point->SetParams(rand()%HEIGHT, rand()%WIDTH, POINT, NONE);

            score += 100;
        }
        else if (t == TAIL) {
            state = STOP;
            head->SetType(OVER);
        }
    }
    glutPostRedisplay();
}

void Game::SetDirection(Direction d)
{
    direct = d;
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
