#include "game.h"
#include <GL/glut.h>
#include <iostream>
#include <ctime>
#include <vector>

void GameOverCheck();
bool FoodPosCheck(int x, int y);

int w,h;
int grid_size;

short move_way = RIGHT;
int posX , posY;

bool game_over = false;

int foodX , foodY;
bool is_there = false;

int max_size = 30;
int now_size = 1;

std::vector<int> possX;
std::vector<int> possY;
int vec_size;


int score = 0;
int random(int min,int max)
{
	srand(time(0));
	return min + rand() % (max - min);     
}

void InitGame(int width,int height,int size)
{
	w = width;
	h = height;
	grid_size = size; 

	posX = w/2;
	posY = h/2;
}
void DrawGrid()
{
	for(int x = 0; x <= w; x+=grid_size)
	{
		for(int y = 0; y <= h ; y+=grid_size)
		{
			OneGrid(x,y);			
		}
	}
}
void OneGrid(int x,int y)
{
	if(x == 0 || x == w-grid_size || y == 0 || y == h-grid_size)
	{
		glColor3f(1,0,0);
		glLineWidth(2);
	}
	else
	{
		glColor3f(1,1,1);
		glLineWidth(1);	
	}

	glBegin(GL_LINE_LOOP);
		glVertex2i(x,y);
		glVertex2i(x+grid_size,y);
		glVertex2i(x+grid_size,y+grid_size);
		glVertex2i(x,y+grid_size);
	glEnd();
}
bool start = false;
void DrawSnake()
{
	int now_vec_size = possX.size();
	if(now_vec_size >= max_size)
	{
		possX.erase(possX.begin());
		possY.erase(possY.begin());		
	}
	possX.push_back(posX);
	possY.push_back(posY);			
		

	vec_size = possX.size();

	glColor3f(1,0,1);
	glRecti(posX,posY,posX+grid_size,posY+grid_size);

	glColor3f(1,1,1);
	for(int i = now_size; 1 < i  ; i--)
	{
		glRecti(possX[vec_size-i],possY[vec_size-i],possX[vec_size-i]+grid_size,possY[vec_size-i]+grid_size);
	}
}
void MoveSnake()
{

	switch(move_way)
	{
		case RIGHT: posX+= grid_size; break;
		case LEFT: 	posX-= grid_size; break;
		case UP:    posY+= grid_size; break;
		case DOWN:  posY-= grid_size; break;
	}

	GameOverCheck();
	if(posX == foodX & posY == foodY)
	{
		if(now_size < max_size)
			now_size++;
		is_there = false;
		score++;
	}
}
void GameOverCheck()
{
	if(posX == 0 || posX == w-grid_size ||posY == 0 || posY == h-grid_size)
	{
		game_over = true;	
	}

	vec_size = possX.size();
	for(int i = now_size; 1 < i  ; i--)
	{
		if(posX == possX[vec_size-i] & posY == possY[vec_size-i] )
		{
			game_over = true;	
		}
	}
}


void SpawnFood()
{
	if(!is_there)
	{

		while(true)
		{
			foodX = random(1,(w/grid_size)-1)*grid_size ;
			foodY = random(1,(h/grid_size)-1)*grid_size ;
			if(FoodPosCheck(foodX,foodY))
			{
				break;
			}
		}
		is_there = true;
	}
	glColor3f(1,1,0);
	glRecti(foodX,foodY,foodX+grid_size,foodY+grid_size);
}
bool FoodPosCheck(int x, int y)
{
	for(int i = now_size; 0 < i  ; i--)
	{
		if (x == possX[vec_size-i] & y == possY[vec_size-i])
		{
			return false;
		}
	}	
	return true;
}