#pragma once
#include "MazeFactory.hpp"


// Có thể cài đặt thêm các hàm make với các tham số khác nhau, hàm cái dưới đây là constuctor mặc định
class MazeCreationInterface
{
public:
	static Maze* CreateMaze(MazeFactory factory) {
		return factory.makeMaze();
	}
	static Room* CreateRoom(MazeFactory factory) {
		return factory.makeRoom();
	}
	static Player* CreatePlayer(MazeFactory factory) {
		return factory.makePlayer();
	}
	static MazeObject* CreateMazeObject(MazeFactory factory) {
		return factory.makeMazeObject();
	}

};

