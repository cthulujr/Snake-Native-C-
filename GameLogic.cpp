#include "GameLogic.h"
#include "Visuals.h"


void clearBoard(int gameBoard[])
{
    for(int i = 0; i<BdArraySize; i++)
        if(i < ROW_WIDTH || i >= BdArraySize-ROW_WIDTH || i%ROW_WIDTH == 0 || (i+1)%ROW_WIDTH == 0) //Border numbers, check bottom for array reference
            gameBoard[i] = 3;
        else
            gameBoard[i] = 0;
}

void clearSnake(int snake[], int size)
{
    for(int i = 0; i<BdArraySize; i++)
        snake[i] = 0;

    snake[2] = ROW_WIDTH+size; //inital snake position on the board
    snake[1] = snake[2]++;
    snake[0] = snake[1]++;
}

void SnakeToBoard(int gameBoard[], int snake[], int size)
{
    for(int i = 0; i < size; i++)
    {
            gameBoard[snake[i]] = 1;
    }
}

void moveSnake(int snake[], int size, int dir, int gameBoard[])
{
    int tmp = snake[size-1];
    for(int i = size-1; i > 0; i--) //the last element moves up a position until you reach the head
    {
            snake[i] = snake[i-1];
    }

    switch(dir) //element 0 is the snake's head
    {
        case UP:
            snake[0] -= ROW_WIDTH; //go up a row
            break;
        case LEFT:
            snake[0] -= 1;
            break;
        case RIGHT:
            snake[0] += 1;
            break;
        case DOWN:
            snake[0] += ROW_WIDTH; //go down a row
            break;
    };

    gameBoard[tmp] = 0;
}

void spawnFruit(int gameBoard[])
{
    srand(time(NULL));
    int f;

    while(true)
    {
        f = rand()%(BdArraySize-ROW_WIDTH-1)+ROW_WIDTH+1; //Non border numbers
        if(gameBoard[f] == 0) //if a space is available i.e. not part of the snake, spawn a fruit
        {
            gameBoard[f] = 2;
            break;
        }
    }
}

void growSnake(int gameBoard[], int snake[], int &size, int &score)
{
    if(snake[size-1]-snake[size-2] == ROW_WIDTH) //determines where to place the tail piece
        snake[size] = snake[size-1]+ROW_WIDTH;
    else if(snake[size-1]-snake[size-2] == -ROW_WIDTH)
        snake[size] = snake[size-1]-ROW_WIDTH;
    else if(snake[size-1]-snake[size-2] == 1)
        snake[size] = snake[size-1]+1;
    else if(snake[size-1]-snake[size-2] == -1)
        snake[size] = snake[size-1]-1;

    size++;
    score++;
    spawnFruit(gameBoard);
}


void end(int gameBoard[], int snake[], int &size, bool &play, int &score, int &dir, char &speed)
{
    bool end = drawEnd(score);
    if(end)
        play = false;
    else //reset everything
    {
        size = 3;
        score = 0;
        getSpeed(speed);
        clearBoard(gameBoard);
        clearSnake(snake, size);
        dir = RIGHT;
        SnakeToBoard(gameBoard, snake, size);
        spawnFruit(gameBoard);
    }
}


void checkCollision(int gameBoard[], int snake[], int &size, bool &play, int &score, int &dir, char &speed)
{
    if(snake[0] < ROW_WIDTH || snake[0] > BdArraySize-ROW_WIDTH-1 || snake[0]%ROW_WIDTH == 0 || (snake[0]+1)%ROW_WIDTH == 0) //border collision
    {
        end(gameBoard, snake, size, play, score, dir, speed);
    }


    int tmp = snake[0]; //this is for the fruit collision
    switch(dir) //you can't check if gameBoard[snake[0]] == 2 because the snake overrides it when it moves
    {
        case UP:
            tmp -= ROW_WIDTH; //so instead you check the direction and look at the tile in front of the snake's head
            break;
        case LEFT:
            tmp -= 1;
            break;
        case RIGHT:
            tmp += 1;
            break;
        case DOWN:
            tmp += ROW_WIDTH;
            break;
    };

    if(gameBoard[tmp] == 2)
    {
        growSnake(gameBoard, snake, size, score);
    }

    if(gameBoard[tmp] == 1 && size > 6) //detects if the snake hits itself. The size reuirement is necessary to prevent a false hit at the game's start
    {
        end(gameBoard, snake, size, play, score, dir, speed);
    }

}


/***************************************************************************
                Board array reference

                Check Visuals.h for the size definitions

0       1       2       3       4       5       6       7       8       9  //ROW_WIDTH - 1
10      11      12      13      14      15      16      17      18      19
20      21      22      23      24      25      26      27      28      29
30      31      32      33      34      35      36      37      38      39
40      41      42      43      44      45      46      47      48      49
50      51      52      53      54      55      56      57      58      59
60      61      62      63      64      65      66      67      68      69
70      71      72      73      74      75      76      77      78      79
80      81      82      83      84      85      86      87      88      89
90      91      92      93      94      95      96      97      98      99
100     101     102     103     104     105     106     107     108     109
110     111     112     113     114     115     116     117     118     119
120     121     122     123     124     125     126     127     128     129
130     131     132     133     134     135     136     137     138     139


*****************************************************************************/
