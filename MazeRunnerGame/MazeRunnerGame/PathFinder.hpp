#pragma once
#include "Maze.hpp"
#include <queue>

class PathFinder
{
public:
	virtual vector<shared_ptr<Room>> findPath(shared_ptr<Room> start, shared_ptr<Room> end, bool option = 0) = 0;
};

