#pragma once
#include "PathFinder.hpp"

enum AlgorithmIndex
{
	iBFS = 0,
	iDFS = 1,
	iAStar = 2
};

class BFS : public PathFinder
{
public:
	vector<shared_ptr<Room>> findPath(shared_ptr<Room> start, shared_ptr<Room> end, bool option = 0);
};

class DFS : public PathFinder
{
public:
	vector<shared_ptr<Room>> findPath(shared_ptr<Room> start, shared_ptr<Room> end, bool option = 0);
};

//class Dijkstra : public PathFinder
//{
//public:
//	static vector<shared_ptr<Room>> findPath(shared_ptr<Room> start, shared_ptr<Room> end, bool option = 0);
//};

class AStar : public PathFinder
{
public:
	int calcH(shared_ptr<Room> room, shared_ptr<Room> end);
	vector<shared_ptr<Room>> findPath(shared_ptr<Room> start, shared_ptr<Room> end, bool option = 0);
};

