#include "Input.h"
#include "GameLogic.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#define KEY_SPACE 32

void getInput(int gameBoard[], int snake[], int &dir)
{
    int key = 0;
    if(kbhit())
    {
        switch(key = getch())
        {
            case KEY_UP:
                if(dir != DOWN)
                    dir = UP;
                break;
            case KEY_LEFT:
                if(dir != RIGHT)
                    dir = LEFT;
                break;
            case KEY_RIGHT:
                if(dir != LEFT)
                    dir = RIGHT;
                break;
            case KEY_DOWN:
                if(dir != UP)
                    dir = DOWN;
                break;
            default:
                break;
        };
    }
}

bool getInputEnd()
{
    int key = 0;
    switch(key = getch())
    {
        case KEY_SPACE:
            return false;
            break;
        case KEY_ESC:
            return true;
            break;
    };
}

void getSpeed(char &speed)
{

    std::cout<<"Welcome to Snake. Hold or tap the arrow keys to move.\n\nEnter your game speed <1 for fast, 2 for medium, 3 for slow>: ";
    while(true)
    {

        while(!std::cin.getline(&speed, 2)) //thorough error checking
        {
            std::cin.clear(); //this while loop applies if they enter more than 1 character
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout<<"Invalid entry. <1 for fast, 2 for medium, 3 for slow>: ";
        }

        if(speed == '1' || speed == '2' || speed == '3') //success
            break;
        else //any single character not 1, 2, or 3 is checked off here
            std::cout<<"Invalid entry. <1 for fast, 2 for medium, 3 for slow>: ";


    }
}

