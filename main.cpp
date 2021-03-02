#include "Maze.hpp"
#include "Mouse.hpp"

//Methods Declaration
void clearScreen();  //Windows Specific 

//Global Variables
bool gameover = false;

int main()
{
    //Local Declarations
    Maze *map = new Maze();
    Mouse *mouse = new Mouse(map->getStartPos(), map->getEndPos());
    
    //Main Loop
    while (!gameover)
    {
        if (mouse->hasMouseReachedEnd())
            gameover = true;
        clearScreen();
        map->Draw();
        mouse->updateMouseOnThe(map);
    }

    //Do not close window immediately
    getchar();
    

    //Clean up 
    delete map;
    delete mouse;
    return 0;
}

void clearScreen()
{
    HANDLE hOUT = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {0, 0};
    SetConsoleCursorPosition(hOUT, pos);
}
