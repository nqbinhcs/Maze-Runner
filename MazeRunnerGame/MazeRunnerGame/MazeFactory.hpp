#pragma once
#include "MazeObject.hpp"
#include "Room.hpp"
#include "Player.hpp"
#include "Maze.hpp"


//// Có thể cài đặt thêm các hàm make với các tham số khác nhau, hàm cái dưới đây là constuctor mặc định
//class MazeFactory {
//public:
//	MazeFactory();
//	virtual Maze* makeMaze() const
//	{
//		return new Maze();
//	}
//	virtual Room* makeRoom() const
//	{
//		return new Room;
//	}
//	virtual Player* makePlayer() const
//	{
//		return new Player;
//	}
//	virtual MazeObject* makeMazeObject() const
//	{
//		return new MazeObject;
//	}
//
//	
//};

class LevelMaze {
private:
public:
	LevelMaze() {

	}
	~LevelMaze() {

	}
public:
	std::shared_ptr<Maze> OrderLevelMaze() {
		std::shared_ptr<Maze> maze = CreatLevelMaze();
		maze->UpdateMaze(true);
		return maze;
	}
	virtual std::shared_ptr<Maze> CreatLevelMaze() = 0;
};

class EasyLevelMaze : public LevelMaze {
public:
	EasyLevelMaze() {

	}
	~EasyLevelMaze() {

	}
public:
	std::shared_ptr<Maze> CreatLevelMaze() {
		vector<int> mazeX_Room = { 5, 6, 7, 8 };
		vector<int> mazeY_Room = { 5, 6, 7, 8 };
		vector<int> random = { 2, 5, 10, 15 };
		vector<int> key = { 1, 2, 3, 4 };
		vector<int> trap = { 0,0, 2, 4 };
		vector<int> guard = { 0,0,0,3 };
		vector<int> coin = { 2, 5, 7, 9 };
		std::shared_ptr<Maze> maze(new Maze("EASY", OFFSET_MAZE_X, OFFSET_MAZE_Y, SCREEN_MAZE_X, SCREEN_MAZE_Y, mazeX_Room, mazeY_Room, -1, 4, random,
			key, trap, guard, coin));
		return maze;
	}
};

class MediumLevelMaze : public LevelMaze {
public:
	MediumLevelMaze() {

	}
	~MediumLevelMaze() {

	}
public:
	std::shared_ptr<Maze> CreatLevelMaze() {
		vector<int> mazeX_Room = { 9, 10, 11, 12 };
		vector<int> mazeY_Room = { 9, 10, 11, 12 };
		vector<int> random = { 19, 27, 32, 52 };
		vector<int> key = { 2, 2, 4, 5 };
		vector<int> trap = { 3,5, 7, 9 };
		vector<int> guard = { 2,3,4,6 };
		vector<int> coin = { 5, 7, 9, 11 };
		std::shared_ptr<Maze> maze(new Maze("MEDIUM", OFFSET_MAZE_X, OFFSET_MAZE_Y, SCREEN_MAZE_X, SCREEN_MAZE_Y, mazeX_Room, mazeY_Room, -1, 4, random,
			key, trap, guard, coin));
		return maze;
	}
};

class HardLevelMaze : public LevelMaze {
public:
	HardLevelMaze() {

	}
	~HardLevelMaze() {

	}
public:
	std::shared_ptr<Maze> CreatLevelMaze() {
		vector<int> mazeX_Room = { 13, 18, 22, 25 };
		vector<int> mazeY_Room = { 13, 18, 22, 25 };
		vector<int> random = { 52, 68, 98, 131 };
		vector<int> key = { 6, 8, 10, 13 };
		vector<int> trap = { 8, 11, 15, 18 };
		vector<int> guard = { 5, 7, 10, 13 };
		vector<int> coin = { 11, 15, 17, 21 };
		std::shared_ptr<Maze> maze(new Maze("HARD", OFFSET_MAZE_X, OFFSET_MAZE_Y, SCREEN_MAZE_X, SCREEN_MAZE_Y, mazeX_Room, mazeY_Room, -1, 4, random,
			key, trap, guard, coin));
		return maze;
	}
};

class DemoMaze : public LevelMaze {
public:
	DemoMaze() {

	}
	~DemoMaze() {

	}
public:
	std::shared_ptr<Maze> CreatLevelMaze() {
		vector<int> mazeX_Room = { 25 };
		vector<int> mazeY_Room = { 25 };
		vector<int> random = { 150 };
		vector<int> key = { 0 };
		vector<int> trap = { 0 };
		vector<int> guard = { 0 };
		vector<int> coin = { 0 };
		std::shared_ptr<Maze> maze(new Maze("DEMO ALGORITHMS", OFFSET_MAZE_X, OFFSET_MAZE_Y, SCREEN_MAZE_X, SCREEN_MAZE_Y, mazeX_Room, mazeY_Room, -1, 1, random,
			key, trap, guard, coin));
		return maze;
	}
};
