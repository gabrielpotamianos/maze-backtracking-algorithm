#include "Maze.hpp"
void Maze::clearScreen()
{
    HANDLE hOUT = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {0, 0};
    SetConsoleCursorPosition(hOUT, pos);
}

Maze::Maze()
{
    srand(time(NULL));

    //Create Map
    for (int i = 0; i < MAP_WIDTH; i++)
    {
        for (int j = 0; j < MAP_COLUMNS; j++)
        {
            visited[i][j] = false;
            map[i][j] = wall;
        }
    }

    //modify map for starting point
    map[startingPos.X][startingPos.Y] = ' ';

    //Every starting point will have neighbours
    m_stack.push(make_pair(startingPos.X, startingPos.Y));

    //mark as visited
    visited[startingPos.X][startingPos.Y] = true;

    //Create paths
    GeneratePath();

    int randEndPosX = 0;
    int randEndPosY = 0;

    //if end Pos are not odd, then get random positions until both are odds
    while (randEndPosX % 2 != 1 || randEndPosY % 2 != 1)
    {
        randEndPosX = rand() % MAP_WIDTH - 1 + 1;
        randEndPosY = rand() % MAP_COLUMNS - 1 + 1;
    }

    //Check if the position is within a path
    if (map[randEndPosX][randEndPosY] = ' ' && visited[randEndPosX][randEndPosY])
    {
        //If it is, place C (Cheese)
        map[randEndPosX][randEndPosY] = 'C';
        endingPos.X = randEndPosX;
        endingPos.Y = randEndPosY;
    }
}

Maze::~Maze()
{
}

void Maze::Draw()
{
    for (int i = 0; i < MAP_WIDTH; i++)
    {
        for (int j = 0; j < MAP_COLUMNS; j++)
            cout << map[i][j];
        cout << endl;
    }
}
void Maze::GeneratePath()
{
    //until the last stack member has no neighbours --> meaning map is completed
    while (m_stack.size() > 0)
    {
        vector<int> neighbours;

        //0 - NORTH
        //1 - SOUTH
        //2 - EAST
        //3 - WEST

        // # # # # # # # # # # # 0
        // #                   # 1
        // #                   # 2
        // #                   # 3
        // #                   # 4
        // #                   # 5
        // #                   # 6
        // #                   # 7
        // # # # # # # # # # # # 8
        // 0 1 2 3 4 5 6 7 8 9 10

        //ALL CHECKS EXCLUDE BORDERS

        //if it is higher than 1 on X
        //and has a space on top of the current cell
        //and that cell has not been visited ------------> 0 = NORTH
        if (m_stack.top().first > 1 && map[m_stack.top().first - step][m_stack.top().second + 0] && !visited[m_stack.top().first - step][m_stack.top().second + 0])
            neighbours.push_back(0);

        //if it is less than the mapwidth-2 on X
        //and it has a space below the current cell
        //and that cell has not been visited ------------> 1 = SOUTH
        if (m_stack.top().first < MAP_WIDTH - 2 && map[m_stack.top().first + step][m_stack.top().second + 0] && !visited[m_stack.top().first + step][m_stack.top().second + 0])
            neighbours.push_back(1);

        //if it is higher than 1 on Y
        //and it has a space on the left of the current cell
        //and that cell has not been visited ------------> 2 = WEST
        if (m_stack.top().second > 1 && map[m_stack.top().first + 0][m_stack.top().second - step] && !visited[m_stack.top().first + 0][m_stack.top().second - step])
            neighbours.push_back(2);

        //if it is less than the map columns - 2 on Y
        //and it has a space on the right of the current cell
        //and that cell has not been visited ------------> 3 = EAST
        if (m_stack.top().second < MAP_COLUMNS - 2 && map[m_stack.top().first + 0][m_stack.top().second + step] && !visited[m_stack.top().first + 0][m_stack.top().second + step])
            neighbours.push_back(3);

        //if there are neighbbours
        if (!neighbours.empty())
        {
            //Get a random position (key part in randomization of the maze)
            int next_dir = neighbours[rand() % neighbours.size()];

            //every two characters must be erased (allowing space for the walls)
            for (int j = 1; j <= 2; j++)
            {
                switch (next_dir)
                {
                case 0:
                    //North
                    map[m_stack.top().first - j][m_stack.top().second + 0] = ' ';
                    visited[m_stack.top().first - j][m_stack.top().second + 0] = true;

                    //if this is the last step -> Store it
                    if (j == step)
                        m_stack.push(make_pair(m_stack.top().first - j, m_stack.top().second + 0));
                    break;
                case 1:
                    //South
                    map[m_stack.top().first + j][m_stack.top().second + 0] = ' ';
                    visited[m_stack.top().first + j][m_stack.top().second + 0] = true;

                    //if this is the last step -> Store it
                    if (j == step)
                        m_stack.push(make_pair(m_stack.top().first + j, m_stack.top().second + 0));
                    break;
                case 2:
                    //West
                    map[m_stack.top().first + 0][m_stack.top().second - j] = ' ';
                    visited[m_stack.top().first + 0][m_stack.top().second - j] = true;

                    //if this is the last step -> Store it
                    if (j == step)
                        m_stack.push(make_pair(m_stack.top().first + 0, m_stack.top().second - j));
                    break;
                case 3:
                    //East
                    map[m_stack.top().first + 0][m_stack.top().second + j] = ' ';
                    visited[m_stack.top().first + 0][m_stack.top().second + j] = true;

                    //if this is the last step -> Store it
                    if (j == step)
                        m_stack.push(make_pair(m_stack.top().first + 0, m_stack.top().second + j));
                    break;
                default:
                    break;
                }
            }
        }

        //if no neighbours go the the last place you had neighbours
        //and check again
        else
            m_stack.pop();

        //Display the construction of the maze
        clearScreen();
        Draw();
    }
}

COORD Maze::getStartPos()
{
    return startingPos;
}

COORD Maze::getEndPos()
{
    return endingPos;
}
