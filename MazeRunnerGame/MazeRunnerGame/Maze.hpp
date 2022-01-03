#include <random>
#include "Room.hpp"
#include "MazeKey.hpp"
#include "MazeChest.hpp"
#include "MazeGuard.hpp"
#include "MazeTrap.hpp"
#include "MazeCoin.hpp"

#include <stack>
#include <queue>
#include <cstddef>
#include <iostream>
//#include "Coordinate.hpp"
#pragma once

//Random Element Function
template <typename T, typename A>
T randomElement(std::vector<T, A>& vec)
{
	std::random_device random_device;
	std::mt19937 engine{ random_device() };
	std::uniform_int_distribution<int> dist(0, vec.size() - 1);
	T element = vec[dist(engine)];
	return element;
}

class Maze {
private:
	string nameLevel;
private:
	vector<bool> isTakeKey;
	vector<bool> isTakeCoin;
	bool isTakeChest;

	int mazeX_Offset;
	int mazeY_Offset;
private:
	vector<int> countRoom_Random;
private:
	vector<int> countTrap;
	vector<int> countGuard;
	vector<int> countKey;
	vector<int> countCoin;
private:
	int level;
	int maxLevel;

	vector<int> mazeX_RoomCount;
	vector<int> mazeY_RoomCount;

	int mazeX_Size;
	int mazeY_Size;
private:
	int roomRandom;
	int numKey;
	int numTrap;
	int numGuard;
	int numRoomX;
	int numRoomY;
	int numCoin;
private:
	MazeCoordinate startPos;
	MazeCoordinate finalPos;

private:
	//All rooms in the Maze
	std::vector<std::shared_ptr<Room>> allRooms;

	//All rooms can have objects in them
	std::vector <std::shared_ptr<Room>> obstacleRooms;
	std::vector <std::shared_ptr<Room>> obstacleRoomsGuard;
public:
	std::vector<std::shared_ptr<MazeGuard>> mazeGuard;
	std::vector<std::shared_ptr<MazeTrap>> mazeTrap;

	std::vector < std::shared_ptr<MazeKey>> mazeKey;
	std::shared_ptr<MazeChest> mazeChest;
	std::vector < std::shared_ptr<MazeCoin>> mazeCoin;

public:
	string getNameLevel() {
		return nameLevel;
	}

	int getLevel() {
		return level;
	}
	MazeCoordinate getStartPos() {
		return startPos;
	}
	MazeCoordinate getFinalPos() {
		return finalPos;
	}

	int getNumRoomX() {
		return numRoomX;
	}
	int getNumRoomY() {
		return numRoomY;
	}

	int getSizeObj(int type) {
		if (type == 1) {
			return numTrap;
		}
		else if (type == 2) {
			return numGuard;
		}
		else if (type == 3) {
			return numKey;
		}
		else if (type == 4) {
			return numCoin;
		}
	}

	int getDirRoom(int i) {
		return allRooms[i]->wallDirBit;
	}
	bool getActiveTrap(int i) {
		return mazeTrap[i]->getActive();
	}
	MazeCoordinate getPos(int i, int type) {
		if (type == 1) {
			return mazeTrap[i]->getPosition();
		}
		else if (type == 2) {
			return mazeGuard[i]->getPosition();
		}
		else if (type == 3) {
			return mazeKey[i]->getPosition();
		}
		else if (type == 4) {
			return mazeCoin[i]->getPosition();
		}
	}
	MazeCoordinate getCenterPosGuard(int i) {
		return mazeGuard[i]->getPositionCenter();
	}
	bool getTake(int i, int type) {
		if (type == 1) {
			return isTakeKey[i];
		}
		else if (type == 2) {
			return isTakeCoin[i];
		}
		else if (type == 3) {
			return isTakeChest;
		}
	}

	float getWidthRoom();
	float getHeightRoom();
public:
	void setStartPos(MazeCoordinate pos) {
		startPos = pos;
	}
	void setFinalPos(MazeCoordinate pos) {
		finalPos = pos;
		mazeChest->setPosition(pos);
	}
	void setDirRoom(int i, int dir) {
		allRooms[i]->wallDirBit = dir;
	}
	void setTake(int i, int type) {
		if (type == 1) {
			isTakeKey[i] = true;
			std::shared_ptr<Room> curRoom = FindRoomByPos(mazeKey[i]->getPosition());
			auto roomTypesIter = std::find(begin(curRoom->roomTypes), end(curRoom->roomTypes), KEY);

			//Remove the "KEY" type from the roomTypes
			if (roomTypesIter != end(curRoom->roomTypes))
				curRoom->roomTypes.erase(roomTypesIter);
		}
		else if (type == 2) {
			isTakeCoin[i] = true;
			std::shared_ptr<Room> curRoom = FindRoomByPos(mazeCoin[i]->getPosition());
			auto roomTypesIter = std::find(begin(curRoom->roomTypes), end(curRoom->roomTypes), COIN);

			//Remove the "COIN" type from the roomTypes
			if (roomTypesIter != end(curRoom->roomTypes))
				curRoom->roomTypes.erase(roomTypesIter);
		}
		else if (type == 3) {
			isTakeChest = true;
		}
	}
public:
	bool completeLevel() {
		for (int i = 0; i < isTakeKey.size(); i++) {
			if (isTakeKey[i] == false) {
				return false;
			}
		}
		if (isTakeChest == false) {
			return false;
		}
		return true;
	}	
public:
	Maze(string name, int XOffset, int YOffset, int mazeX, int mazeY, vector<int> mazeX_Room, vector<int> mazeY_Room,
		int startLevel, int finalLevel, vector<int> random,
		vector<int> key, vector<int> trap, vector<int> guard, vector<int> coin) {
		nameLevel = name;

		mazeX_Offset = XOffset;
		mazeY_Offset = YOffset;

		mazeX_Size = mazeX;
		mazeY_Size = mazeY;

		mazeX_RoomCount = mazeX_Room;
		mazeY_RoomCount = mazeY_Room;

		level = startLevel;
		maxLevel = finalLevel;

		countRoom_Random = random;

		countKey = key;
		countTrap = trap;
		countGuard = guard;
		countCoin = coin;
	}

public:
	bool isWin();
	void UpdateMaze(bool next);

	void PrepareInforLevel();
	void ResetMaze();
	void UpdateLevel(bool next);

	bool checkAroundPosStart(MazeCoordinate pos);
	void CreateRooms();
public:
	bool CheckGetKeyAtPos(MazeCoordinate pos);
	bool CheckGetAllKey();

	void NextMazeCycle();

	std::shared_ptr<Room> FindRoomByPos(MazeCoordinate pos);
private:
	void ChangePosition(MazeCoordinate& pos, directions dir);
	
	void CarveMaze();

	void CreateObjects();

	void CreateKeys();
	void CreatChest();
	void CreatCoins();

	bool checkBorder(MazeCoordinate pos);
	void RandomConnectRoom();

	//FUNCTION USE INSERT INFOR FROM FILE.
public:
	void ConnectEachOther(std::shared_ptr<Room> roomNow, int x, int y);
	void addObjFromFile(int pos, int type);
	void setMazeFromFile(vector<vector<int>> maze, vector<vector<int>> mazeObj, vector<vector<int>> checkObj, MazeCoordinate startP, MazeCoordinate finalP);
public:
	void AddMazeRoomsToRenderer(sf::RenderWindow& window);
	void AddMazeObstaclesToRenderer(sf::RenderWindow& window);
};

