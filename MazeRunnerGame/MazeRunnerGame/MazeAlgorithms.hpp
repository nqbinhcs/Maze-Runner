#pragma once
#include "PathFinder.hpp"
class BFS : public PathFinder
{
	vector<shared_ptr<Room>> findPathOnly(shared_ptr<Room> start, shared_ptr<Room> end);
	vector<shared_ptr<Room>> findPathShowingProcess(shared_ptr<Room> start, shared_ptr<Room> end);
};

class DFS : public PathFinder
{
	vector<shared_ptr<Room>> findPathOnly(shared_ptr<Room> start, shared_ptr<Room> end);
	vector<shared_ptr<Room>> findPathShowingProcess(shared_ptr<Room> start, shared_ptr<Room> end);
};

class Dijkstra : public PathFinder
{
	vector<shared_ptr<Room>> findPathOnly(shared_ptr<Room> start, shared_ptr<Room> end);
	vector<shared_ptr<Room>> findPathShowingProcess(shared_ptr<Room> start, shared_ptr<Room> end);
};

class AStar : public PathFinder
{
	vector<shared_ptr<Room>> findPathOnly(shared_ptr<Room> start, shared_ptr<Room> end);
	vector<shared_ptr<Room>> findPathShowingProcess(shared_ptr<Room> start, shared_ptr<Room> end);
};

