#include "game.h"

Game *game;

GLvoid display()
{
    game->Draw();
    glutSwapBuffers();
}

GLvoid idle() {

}

GLvoid SetProjectionMatrix(GLsizei width, GLsizei height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,width/height,1,-100);
}

GLvoid SetModelviewMatrix(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

GLvoid reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	SetProjectionMatrix(width,height);
	SetModelviewMatrix();
}

GLvoid keyDown (unsigned char key, int x, int y)
{
    game->Move();
}

GLvoid keyUp (unsigned char key, int x, int y)
{

}

GLvoid specDown (int key, int x, int y)
{

}

GLvoid specUp (int key, int x, int y)
{

}

GLvoid mouse(GLsizei button, GLsizei state, GLsizei x, GLsizei y)
{
	if( state == GLUT_DOWN ) {

	}
	else if (state == GLUT_UP) {

	}
}

GLvoid motion(GLsizei x, GLsizei y)
{

}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Shnake");

    game = new Game();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(specDown);
	glutSpecialUpFunc(specUp);

	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	glutMainLoop();
	return 0;
}
