#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <iostream>
#include <stdlib.h>
#include <time.h>

#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define UP 4

void clearBoard(int gameBoard[]);
void clearSnake(int snake[], int size);
void spawnFruit(int gameBoard[]);
void moveSnake(int snake[], int size, int dir, int gameBoard[]);
void SnakeToBoard(int gameBoard[], int snake[], int size);
void checkCollision(int gameBoard[], int snake[], int &size, bool &play, int &score, int &dir, char &speed);


#endif
