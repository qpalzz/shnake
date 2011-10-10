#include "game.h"

Game::Game()
{
    score = 0;
    direct = LEFT;

    for (int i = 0; i < HEIGHT; i++) {
        GLfloat a[3],
                b[3],
                c[3],
                d[3];
        for (int j = 0; j < HEIGHT; j++) { // передняя грань
            a[X] = -(HEIGHT/2)*CELL_WIDTH + j*CELL_WIDTH;
            a[Y] = (HEIGHT/2)*CELL_WIDTH + i*CELL_WIDTH;
            a[Z] = (HEIGHT/2)*CELL_WIDTH;

            b[X] = -(HEIGHT/2)*CELL_WIDTH + CELL_WIDTH + j*CELL_WIDTH;
            b[Y] = (HEIGHT/2)*CELL_WIDTH + i*CELL_WIDTH;
            b[Z] = (HEIGHT/2)*CELL_WIDTH;

            c[X] = -(HEIGHT/2)*CELL_WIDTH + CELL_WIDTH + j*CELL_WIDTH;
            c[Y] = (HEIGHT/2)*CELL_WIDTH + CELL_WIDTH + i*CELL_WIDTH;
            c[Z] = (HEIGHT/2)*CELL_WIDTH;

            d[X] = -(HEIGHT/2)*CELL_WIDTH + j*CELL_WIDTH;
            d[Y] = (HEIGHT/2)*CELL_WIDTH + CELL_WIDTH + i*CELL_WIDTH;
            d[Z] = (HEIGHT/2)*CELL_WIDTH;

            f[i][j].SetPoints(a,b,c,d);
        }
        for (int j = HEIGHT; j < HEIGHT*2; j++) { // правая грань
            a[X] = (HEIGHT/2)*CELL_WIDTH;
            a[Y] = (HEIGHT/2)*CELL_WIDTH + i*CELL_WIDTH;
            a[Z] = (HEIGHT/2)*CELL_WIDTH - (j%HEIGHT)*CELL_WIDTH;

            b[X] = (HEIGHT/2)*CELL_WIDTH;
            b[Y] = (HEIGHT/2)*CELL_WIDTH + i*CELL_WIDTH;
            b[Z] = +(HEIGHT/2)*CELL_WIDTH - CELL_WIDTH - (j%HEIGHT)*CELL_WIDTH;

            c[X] = (HEIGHT/2)*CELL_WIDTH;
            c[Y] = (HEIGHT/2)*CELL_WIDTH + CELL_WIDTH + i*CELL_WIDTH;
            c[Z] = (HEIGHT/2)*CELL_WIDTH - CELL_WIDTH - (j%HEIGHT)*CELL_WIDTH;

            d[X] = (HEIGHT/2)*CELL_WIDTH;
            d[Y] = (HEIGHT/2)*CELL_WIDTH + CELL_WIDTH + i*CELL_WIDTH;
            d[Z] = +(HEIGHT/2)*CELL_WIDTH - (j%HEIGHT)*CELL_WIDTH;

            f[i][j].SetPoints(a,b,c,d);
        }
        for (int j = HEIGHT*2; j < HEIGHT*3; j++) { // задняя грань
            a[X] = (HEIGHT/2)*CELL_WIDTH - (j%HEIGHT)*CELL_WIDTH;
            a[Y] = (HEIGHT/2)*CELL_WIDTH + i*CELL_WIDTH;
            a[Z] = -(HEIGHT/2)*CELL_WIDTH;

            b[X] = (HEIGHT/2)*CELL_WIDTH - CELL_WIDTH - (j%HEIGHT)*CELL_WIDTH;
            b[Y] = (HEIGHT/2)*CELL_WIDTH + i*CELL_WIDTH;
            b[Z] = -(HEIGHT/2)*CELL_WIDTH;

            c[X] = (HEIGHT/2)*CELL_WIDTH - CELL_WIDTH - (j%HEIGHT)*CELL_WIDTH;
            c[Y] = (HEIGHT/2)*CELL_WIDTH + CELL_WIDTH + i*CELL_WIDTH;
            c[Z] = -(HEIGHT/2)*CELL_WIDTH;

            d[X] = (HEIGHT/2)*CELL_WIDTH - (j%HEIGHT)*CELL_WIDTH;
            d[Y] = (HEIGHT/2)*CELL_WIDTH + CELL_WIDTH + i*CELL_WIDTH;
            d[Z] = -(HEIGHT/2)*CELL_WIDTH;

            f[i][j].SetPoints(a,b,c,d);
        }
        for (int j = HEIGHT*3; j < WIDTH; j++) { // левая грань
            a[X] = -(HEIGHT/2)*CELL_WIDTH;
            a[Y] = (HEIGHT/2)*CELL_WIDTH + i*CELL_WIDTH;
            a[Z] = -(HEIGHT/2)*CELL_WIDTH + (j%HEIGHT)*CELL_WIDTH;

            b[X] = -(HEIGHT/2)*CELL_WIDTH;
            b[Y] = (HEIGHT/2)*CELL_WIDTH + i*CELL_WIDTH;
            b[Z] = -(HEIGHT/2)*CELL_WIDTH + CELL_WIDTH + (j%HEIGHT)*CELL_WIDTH;

            c[X] = -(HEIGHT/2)*CELL_WIDTH;
            c[Y] = (HEIGHT/2)*CELL_WIDTH + CELL_WIDTH + i*CELL_WIDTH;
            c[Z] = -(HEIGHT/2)*CELL_WIDTH + CELL_WIDTH + (j%HEIGHT)*CELL_WIDTH;

            d[X] = -(HEIGHT/2)*CELL_WIDTH;
            d[Y] = (HEIGHT/2)*CELL_WIDTH + CELL_WIDTH + i*CELL_WIDTH;
            d[Z] = -(HEIGHT/2)*CELL_WIDTH + (j%HEIGHT)*CELL_WIDTH;

            f[i][j].SetPoints(a,b,c,d);
        }
    }

    head.SetParams(HEIGHT / 2, HEIGHT / 2, TAIL, LEFT);
    point.SetParams(2, 2, POINT, NONE);

    InitGraphic();
}

void Game::Draw()
{
    head.Projection(f);
    point.Projection(f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	gluLookAt( 10,10,10, 0,3,0, 0,1,0 );

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            f[i][j].Draw();
        }
    }

    glLineWidth(2);
	glBegin(GL_LINES);
		glColor4f(0,0,1,1);
		glVertex3f(0, 0, 0);
		glVertex3f(1, 0, 0); // Ox
		glColor4f(0,1,0,1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 1, 0); // Oy
		glColor4f(1,0,0,1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 1); // Oz
	glEnd();
}

void Game::Move()
{

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
