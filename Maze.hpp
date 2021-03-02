#ifndef MAP_H
#define MAP_H
#pragma once

#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <stack>
#include <vector>

using namespace std;

class Maze
{

public:
	//Map Size -- Modifiable
	static const int MAP_WIDTH = 23;
	static const int MAP_COLUMNS = 43;

	//public access to the map for the mouse
	char map[MAP_WIDTH][MAP_COLUMNS];

	//C-Tor and D-tor
	Maze();
	~Maze();

	//Draw Map
	void Draw();

	//ClearScreen for nicely diplay on the maze creation
	void clearScreen();

	//Getters
	COORD getStartPos();
	COORD getEndPos();
	COORD getMapSize();


private:

	//step set to 2 so it would allow a character in between (the walls)
	int step = 2;

	//Maze Creation (keeping accountable which part I have already visited)
	bool visited[MAP_WIDTH][MAP_COLUMNS];
	char wall = '#';

	//Starting and Ending Positions
	COORD startingPos{1, 1};
	COORD endingPos{(short)(MAP_WIDTH - step), (short)(MAP_COLUMNS - step)};

	//Stack to keep track of all positions which have neighbours
	stack<pair<int, int>> m_stack;

	//Create Maze
	void GeneratePath();
};
#endif