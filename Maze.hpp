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

enum Direction
{
	TOP = 0,
	LEFT = 1,
	DOWN = 2,
	RIGHT = 3,
	COUNT = 4
};

class Maze
{
private:
	static const int MAP_WIDTH = 17;
	static const int MAP_COLUMNS = 23;

	int startEndPos[2][2];
	int borders[4] = {0,0,MAP_WIDTH-1,MAP_COLUMNS-1};
	
	char map[MAP_WIDTH][MAP_COLUMNS];
	char wall = '#';
	bool visited[MAP_WIDTH][MAP_COLUMNS];
	stack<pair<int,int>> m_stack;
	int visitedCells=1, step=2;

	enum 
	{
		CELL_PATH_N = 0x01,
		CELL_PATH_E = 0x02,
		CELL_PATH_S = 0x04,
		CELL_PATH_W = 0x08,
		CELL_VISITED = 0x10
	};


	void GeneratePath();

public:
	Maze();
	void Draw();
	void clearScreen();
	~Maze();
};
#endif