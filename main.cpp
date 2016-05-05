//Created by Zack Savoia
#include <iostream>
#include "Visuals.h"
#include "GameLogic.h"

using namespace std;

void setConsole() //Sets the windcow information
{
    COORD c;
    HANDLE conOut = GetStdHandle(STD_OUTPUT_HANDLE);

    int width = GetSystemMetrics(SM_CXSCREEN)/2; //buffer based off native resolution
    int height = GetSystemMetrics(SM_CYSCREEN)/2;
    c.X = width;
    c.Y = height;

    SetConsoleScreenBufferSize(conOut, c); //the coord struct is has its size in pixels

    SMALL_RECT r = {0, 0, width/10, height/16}; //the actual window size does not
    SetConsoleWindowInfo(conOut, 1, &r);

    SetConsoleTitle("Snake in Native C++");
}


int main()
{
    setConsole();

    int Bd[BdArraySize];
    int p1[BdArraySize];

    int snakeSize = 3;
    int score = 0;
    char speed = '0';

    clearBoard(Bd); //set board
    clearSnake(p1, snakeSize);
    int dir = RIGHT; //directions defined in GameLogic.h
    SnakeToBoard(Bd, p1, snakeSize);
    spawnFruit(Bd);

    bool play = true;

    getSpeed(speed);

    while(play)
    {
        FrameLimit(Bd, p1, dir, score, speed);
        checkCollision(Bd, p1, snakeSize, play, score, dir, speed);

        if(!play) //the end condition would have been met in the checkCollision function, so there's no need to go through the functions below.
            return 0;

        moveSnake(p1, snakeSize, dir, Bd);
        SnakeToBoard(Bd, p1, snakeSize);
    }

    return 0;
}
