#include "Visuals.h"


void draw(int gameBoard[], int score, char speed)
{
    static HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE); //This section makes sure the cursor returns to the same place each time
    static COORD coord;                                 //It overwrites itself as a form of self-clearing.

    coord.X = 0;
    coord.Y = 0;

    SetConsoleCursorPosition(out, coord);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);


    for(int i = 0; i<BdArraySize; i++)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        switch(gameBoard[i])
        {
            case 0:
                std::cout<<" ";
                break;
            case 1:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                std::cout<<"A";
                break;
            case 2:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                std::cout<<"@";
                break;
            case 3:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                std::cout<<"&";
                break;
        }

        if((i+1)%ROW_WIDTH == 0) //End of row
        {
            std::cout<<"\n";
        }
        else
        {
            std::cout<<"";
        }
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    std::cout<<"\nScore:     "<<score;

    switch(speed) //the delay in FrameLimit is often not enough, so here is another artifical delay added
    {
        case '1': //fastest, no delay
            break;
        case '2': //low delay
            Sleep(10);
        case '3': //a more noticable delay
            Sleep(200);
    };
}

void FrameLimit(int gameBoard[], int snake[], int &dir, int score, char speed)
{
    static float time = timeGetTime();
    static float frameCount = 0;
    static int renderMax = 10;

    float dt = (timeGetTime() - time); //difference in time from the two measurements of timeGetTime()

    if (dt > 0.01666667f) //A delay of 0.166667 milliseconds is equal to 60 frames per second
        renderMax = 10;
    if (dt < 0.001f) //A lower delay results in a higher frame rate, but too high makes the game unplayable
        renderMax = 10000; //This is a poor work around to that by forcing more calculations and thus, slowing down the game.

    if(frameCount < renderMax)
    {
        frameCount++;
        getInput(gameBoard, snake, dir);
    }

    frameCount = 0;
    draw(gameBoard, score, speed);
}

bool drawEnd(int score)
{
    HANDLE endOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD endCoord;

    endCoord.X = 0;
    endCoord.Y = 0;

    SetConsoleCursorPosition(endOut, endCoord);

    for(int i = 0; i<BdArraySize*3; i++) //clear screen
    {
        if((i+1)%ROW_WIDTH == 0)
        {
            std::cout<<" \n";
        }
        else
        {
            std::cout<<" ";
        }
    }

    endCoord.X = 0;
    endCoord.Y = 5;

    SetConsoleCursorPosition(endOut, endCoord);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    std::cout<<"\nYOU LOSE WITH "<<score<<" POINTS.";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    std::cout<<"\nPRESS SPACE TO REPLAY. ESCAPE TO EXIT.\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    if(getInputEnd())
        return true;
    else
    {
        return false;
    }
}

/***************************************************************************

Here is a visual representation of the board array. Check the bottom of
GameLogic.cpp for a more indepth explanation.

0       1       2       3       4       5       6       7       8       9
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
