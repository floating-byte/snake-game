#ifndef GAME
#define GAME

#define UP    1 
#define DOWN -1 
#define LEFT  2
#define RIGHT -2

void InitGame(int,int,int);
void DrawGrid();
void OneGrid(int,int);

void DrawSnake();
void MoveSnake();

void SpawnFood();
#endif