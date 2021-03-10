#include <include.h>
#include <string>
#include "game.h"

#define WIDTH 400
#define HEIGHT 400
#define FPS 7

extern short move_way;
extern bool game_over;
extern int score;

void display();
void rechape(int ,int);
void arrowHandler(int,int,int);
void update(int);
void init()
{
	glClearColor(0,0,0,1);	
	InitGame(WIDTH,HEIGHT,20);
}
int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	
	glutInitWindowPosition(300,200);
	glutInitWindowSize(WIDTH,HEIGHT);
	glutCreateWindow("title");

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(rechape);
	glutTimerFunc(0,update,0);
	glutSpecialFunc(arrowHandler);

	glutMainLoop();
	return 0;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	DrawGrid();
	DrawSnake();
	SpawnFood();

	glutSwapBuffers();
}
void rechape(int w,int h)
{
	glutReshapeWindow(WIDTH,HEIGHT);
	glViewport(0,0,WIDTH,HEIGHT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,WIDTH,0,HEIGHT,-1,1);
	glMatrixMode(GL_MODELVIEW);
}
void update(int)
{
	glutTimerFunc(1000/FPS,update,0);
	MoveSnake();
	if (game_over)
	{
		std::string word = "Your Score: ";
		word.append(std::to_string(score));

		char const *num_char = word.c_str();

		MessageBox(0,num_char,"Game Over",MB_OK);
		exit(0);
	}
	glutPostRedisplay();
}
void arrowHandler(int key,int,int)
{
	switch(key)
	{
		case GLUT_KEY_RIGHT: 
			if(move_way != 2)
				move_way = -2;
		break;
		case GLUT_KEY_LEFT: 
			if(move_way != -2)
				move_way = 2;			
		break;
		case GLUT_KEY_UP: 
			if(move_way != -1)
				move_way = 1;
		break;
		case GLUT_KEY_DOWN: 
			if(move_way != 1)
				move_way = -1;
		break;
	}
}
