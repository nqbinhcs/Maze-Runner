#pragma once
#include "Maze.hpp"

class PathFinder
{
public:
	virtual vector<shared_ptr<Room>> findPathOnly(shared_ptr<Room> start, shared_ptr<Room> end) = 0;
	virtual vector<shared_ptr<Room>> findPathShowingProcess(shared_ptr<Room> start, shared_ptr<Room> end) = 0;
};

