#include "Maze.hpp"
#include <conio.h>
void clearScreen();
void Input();
bool gameover = false;

int main()
{
    Maze *map = new Maze();
    while (!gameover)
    {
        clearScreen();
        map->Draw();
        Input();
    }
    getchar();
    delete map;
    return 0;
}

void clearScreen()
{
    HANDLE hOUT = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {0, 0};
    SetConsoleCursorPosition(hOUT, pos);
}

void Input()
{
    if (kbhit())
    {
        switch (getch())
        {
        case 'q':
            gameover = true;
            break;
        }
    }
}