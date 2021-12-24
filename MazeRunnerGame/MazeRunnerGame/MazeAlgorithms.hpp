#pragma once
#include "PathFinder.hpp"
class BFS : public PathFinder
{
	virtual vector<shared_ptr<Room>> findPath(shared_ptr<Room> start, shared_ptr<Room> end, bool option = 0);
};

class DFS : public PathFinder
{
	virtual vector<shared_ptr<Room>> findPath(shared_ptr<Room> start, shared_ptr<Room> end, bool option = 0);
};

class Dijkstra : public PathFinder
{
	virtual vector<shared_ptr<Room>> findPath(shared_ptr<Room> start, shared_ptr<Room> end, bool option = 0);
};

class AStar : public PathFinder
{
	int calcH(shared_ptr<Room> room, shared_ptr<Room> end);
	virtual vector<shared_ptr<Room>> findPath(shared_ptr<Room> start, shared_ptr<Room> end, bool option = 0);
};

