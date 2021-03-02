#ifndef MOUSE_H
#define MOUSE_H
#pragma once
#include "Maze.hpp"

class Mouse
{
private:
	//Positions
	COORD currentPos{0, 0};
	COORD endingPos{0, 0};
	
	//Amount to move at the time
	int step = 1;

	//Character defining Mouse
	char character = 'M';

	//Copy of maze (keeping accountable of which cells I visited)
	bool visited[Maze::MAP_WIDTH][Maze::MAP_COLUMNS];

	//Stack (keeping accountable for every cell that has at least one neighbour)
	stack<pair<int, int>> m_stack;

public:
	//C-tor / D-tor
	Mouse(COORD startPos,COORD endPos);
	~Mouse();

	//Update maze with the mouse position
	void updateMouseOnThe(Maze *maze);

	//Check if endPos == currentPos
	bool hasMouseReachedEnd();
};
#endif