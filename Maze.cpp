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

    for (int i = 0; i < MAP_WIDTH; i++)
    {
        for (int j = 0; j < MAP_COLUMNS; j++)
        {
            visited[i][j] = false;
            map[i][j] = wall;
        }
    }
    map[1][1] = ' ';
    startEndPos[0][0] = 1;
    startEndPos[0][1] = 1;
    m_stack.push(make_pair(1, 1));
    visited[1][1] = true;
    GeneratePath();

    if (map[MAP_WIDTH - step][MAP_COLUMNS - step] = ' ' && visited[MAP_WIDTH - step][MAP_COLUMNS - step])
    {
        map[MAP_WIDTH - step][MAP_COLUMNS - step] = 'C';
        startEndPos[1][0] = MAP_WIDTH - step;
        startEndPos[1][1] = MAP_COLUMNS - step;
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
    while (m_stack.size() > 0)
    {
        vector<int> neighbours;

        //0 - NORTH
        //1 - SOUTH
        //2 - EAST
        //3 - WEST

        if (m_stack.top().first > 1 && map[m_stack.top().first - step][m_stack.top().second + 0] && !visited[m_stack.top().first - step][m_stack.top().second + 0])
            neighbours.push_back(0);
        if (m_stack.top().first < MAP_WIDTH - 2 && map[m_stack.top().first + step][m_stack.top().second + 0] && !visited[m_stack.top().first + step][m_stack.top().second + 0])
            neighbours.push_back(1);
        if (m_stack.top().second > 1 && map[m_stack.top().first + 0][m_stack.top().second - step] && !visited[m_stack.top().first + 0][m_stack.top().second - step])
            neighbours.push_back(2);
        if (m_stack.top().second < MAP_COLUMNS - 2 && map[m_stack.top().first + 0][m_stack.top().second + step] && !visited[m_stack.top().first + 0][m_stack.top().second + step])
            neighbours.push_back(3);

        if (!neighbours.empty())
        {
            int next_dir = neighbours[rand() % neighbours.size()];
            for (int j = 1; j <= 2; j++)
            {
                switch (next_dir)
                {
                case 0:
                    map[m_stack.top().first - j][m_stack.top().second + 0] = ' ';
                    visited[m_stack.top().first - j][m_stack.top().second + 0] = true;
                    if (j == step)
                        m_stack.push(make_pair(m_stack.top().first - j, m_stack.top().second + 0));
                    break;
                case 1:
                    map[m_stack.top().first + j][m_stack.top().second + 0] = ' ';
                    visited[m_stack.top().first + j][m_stack.top().second + 0] = true;
                    if (j == step)
                        m_stack.push(make_pair(m_stack.top().first + j, m_stack.top().second + 0));
                    break;
                case 2:
                    map[m_stack.top().first + 0][m_stack.top().second - j] = ' ';
                    visited[m_stack.top().first + 0][m_stack.top().second - j] = true;
                    if (j == step)
                        m_stack.push(make_pair(m_stack.top().first + 0, m_stack.top().second - j));
                    break;
                case 3:
                    map[m_stack.top().first + 0][m_stack.top().second + j] = ' ';
                    visited[m_stack.top().first + 0][m_stack.top().second + j] = true;
                    if (j == step)
                        m_stack.push(make_pair(m_stack.top().first + 0, m_stack.top().second + j));
                    break;
                default:
                    break;
                }
                visitedCells++;
            }
        }
        else
            m_stack.pop();

        clearScreen();
        Draw();
    }
}
