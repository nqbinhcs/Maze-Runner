#pragma once
#include "MazeObject.hpp"
#include "Room.hpp"
#include "Player.hpp"
#include "Maze.hpp"


// Có thể cài đặt thêm các hàm make với các tham số khác nhau, hàm cái dưới đây là constuctor mặc định
class MazeFactory {
public:
	MazeFactory();
	virtual Maze* makeMaze() const
	{
		return new Maze();
	}
	virtual Room* makeRoom() const
	{
		return new Room;
	}
	virtual Player* makePlayer() const
	{
		return new Player;
	}
	virtual MazeObject* makeMazeObject() const
	{
		return new MazeObject;
	}

	
};

