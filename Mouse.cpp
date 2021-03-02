#include "Mouse.hpp"
#include <bits/stdc++.h>

Mouse::Mouse(COORD startPos, COORD endPos)
{
    //Store Positions
    currentPos = startPos;
    endingPos = endPos;

    //Surely initial position has neighbours, so the position
    m_stack.push(make_pair(currentPos.X, currentPos.Y));

    //Initialize copy of the maze
    for (int i = 0; i < Maze::MAP_WIDTH; i++)
        for (int j = 0; j < Maze::MAP_COLUMNS; j++)
            visited[i][j] = false;
}

Mouse::~Mouse()
{
}

void Mouse::updateMouseOnThe(Maze *maze)
{
    //if stack is populated, means I still have places to visit
    if (m_stack.size() > 0 && (currentPos.X != endingPos.X || currentPos.Y != endingPos.Y))
    {
        //vector to store all neighbours
        vector<int> neighbours;

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
        if (m_stack.top().first > 1 && maze->map[m_stack.top().first - step][m_stack.top().second + 0] != '#' && !visited[m_stack.top().first - step][m_stack.top().second + 0])
            neighbours.push_back(0);

        //if it is less than the mapwidth-2 on X
        //and it has a space below the current cell
        //and that cell has not been visited ------------> 1 = SOUTH
        if (m_stack.top().first < Maze::MAP_WIDTH - 2 && maze->map[m_stack.top().first + step][m_stack.top().second + 0] != '#' && !visited[m_stack.top().first + step][m_stack.top().second + 0])
            neighbours.push_back(1);

        //if it is higher than 1 on Y
        //and it has a space on the left of the current cell
        //and that cell has not been visited ------------> 2 = WEST
        if (m_stack.top().second > 1 && maze->map[m_stack.top().first + 0][m_stack.top().second - step] != '#' && !visited[m_stack.top().first + 0][m_stack.top().second - step])
            neighbours.push_back(2);

        //if it is less than the map columns - 2 on Y
        //and it has a space on the right of the current cell
        //and that cell has not been visited ------------> 3 = EAST
        if (m_stack.top().second < Maze::MAP_COLUMNS - 2 && maze->map[m_stack.top().first + 0][m_stack.top().second + step] != '#' && !visited[m_stack.top().first + 0][m_stack.top().second + step])
            neighbours.push_back(3);

        //If there are neighbours
        if (!neighbours.empty())
        {
            int next_dir;

            //if has a neighbour to the EAST
            //and the mouse is positioned to the west from the cheese
            if ((currentPos.Y < endingPos.Y) && ((std::find(std::begin(neighbours), std::end(neighbours), 3) != neighbours.end())))
                next_dir = 3;

            //if has a neighbour to the WEST
            //and the mouse is positioned to the east from the cheese
            else if (currentPos.Y > endingPos.Y && ((std::find(std::begin(neighbours), std::end(neighbours), 2) != neighbours.end())))
                next_dir = 2;

            //if has a neighbour to the NORTH
            //and the mouse is positioned to the south from the cheese
            else if (currentPos.X > endingPos.X && ((std::find(std::begin(neighbours), std::end(neighbours), 0) != neighbours.end())))
                next_dir = 0;

            //if has a neighbour to the SOUTH
            //and the mouse is positioned to the north from the cheese
            else if (currentPos.X < endingPos.X && ((std::find(std::begin(neighbours), std::end(neighbours), 1) != neighbours.end())))
                next_dir = 1;

            //go randomly if neighbour is not present
            else
                next_dir = neighbours[rand() % neighbours.size()];

            switch (next_dir)
            {

            //NORTH
            case 0:
                maze->map[currentPos.X][currentPos.Y] = '.';
                currentPos.X = m_stack.top().first - step;
                currentPos.Y = m_stack.top().second + 0;

                visited[m_stack.top().first - step][m_stack.top().second + 0] = true;
                m_stack.push(make_pair(m_stack.top().first - step, m_stack.top().second + 0));
                break;
            
            //SOUTH
            case 1:
                maze->map[currentPos.X][currentPos.Y] = '.';
                currentPos.X = m_stack.top().first + step;
                currentPos.Y = m_stack.top().second + 0;

                visited[m_stack.top().first + step][m_stack.top().second + 0] = true;
                m_stack.push(make_pair(m_stack.top().first + step, m_stack.top().second + 0));
                break;
            
            //WEST
            case 2:
                maze->map[currentPos.X][currentPos.Y] = '.';
                currentPos.X = m_stack.top().first + 0;
                currentPos.Y = m_stack.top().second - step;

                visited[m_stack.top().first + 0][m_stack.top().second - step] = true;
                m_stack.push(make_pair(m_stack.top().first + 0, m_stack.top().second - step));
                break;
            
            //EAST
            case 3:
                maze->map[currentPos.X][currentPos.Y] = '.';
                currentPos.X = m_stack.top().first + 0;
                currentPos.Y = m_stack.top().second + step;

                visited[m_stack.top().first + 0][m_stack.top().second + step] = true;
                m_stack.push(make_pair(m_stack.top().first + 0, m_stack.top().second + step));
                break;
            default:
                break;
            }
        }

        //If no neighbour is present --> Dead End
        else
        {
            m_stack.pop();
            maze->map[currentPos.X][currentPos.Y] = '.';
            currentPos.X = m_stack.top().first;
            currentPos.Y = m_stack.top().second;
        }
    }
    maze->map[currentPos.X][currentPos.Y] = 'M';
}

bool Mouse::hasMouseReachedEnd()
{
    return (currentPos.X == endingPos.X && currentPos.Y == endingPos.Y);
}