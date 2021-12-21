#include <random>
#include "Room.hpp"
#include "MazeKey.hpp"
#include "MazeChest.hpp"
#include "MazeGuard.hpp"
#include "MazeTrap.hpp"
//#include "Coordinate.hpp"
#pragma once

#define TRAP_START 3
#define GUARD_START 3

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

class Maze
{

private:
	bool isTakenKey;
	bool isTakenChest;
private:
	//X and Y counts of the maze (total rooms = X*Y)
	int mazeX_RoomCount;
	int mazeY_RoomCount;

	//Information about rendering size for the maze
	int mazeX_Offset;
	int mazeY_Offset;
	int mazeX_Size;
	int mazeY_Size;

	//All rooms in the Maze
	std::vector<std::shared_ptr<Room>> allRooms;

	//All rooms with objects in them - DON'T USE
	std::vector <std::shared_ptr<Room>> obstacleRooms;

	//All objects in this maze (guard, trap) <Don't use>
	std::vector<std::shared_ptr<MazeObject>> objectsInMaze;


public:
	std::shared_ptr<MazeGuard> mazeGuardPtr;
	std::shared_ptr<MazeTrap> mazeTrapPtr;
	std::vector<std::shared_ptr<MazeGuard>> mazeGuard;
	std::vector<std::shared_ptr<MazeTrap>> mazeTrap;
	std::shared_ptr<MazeKey> mazeKey;
	std::shared_ptr<MazeChest> mazeChest;
public:
	int mazeLevel;	//Current Game Level

	//Start and End Position of Maze
	MazeCoordinate startPos;
	MazeCoordinate finalPos;

	//Constructors and Destructors
	Maze(int xCount, int yCount, int xOffset, int yOffset, int xSize, int ySize, int level, bool showCreation, sf::RenderWindow& window);
	Maze(const Maze& other);
	Maze();
	~Maze();
public:
	void setTakenKey(bool take) {
		isTakenKey = take;
	}
	void setTakenChest(bool take) {
		isTakenChest = take;
	}

	bool getTakenKey() {
		return isTakenKey;
	}
	bool getTakenChest() {
		return isTakenChest;
	}
public:
	float getMazeX_Offset() {
		return mazeX_Offset;
	}
	float getMazeY_Offset() {
		return mazeY_Offset;
	}
	float getWidthRoom() {
		return int(mazeX_Size / mazeX_RoomCount);
	}
	float getHeightRoom() {
		return int(mazeY_Size / mazeY_RoomCount);
	}
	float getNumRow() {
		return mazeY_RoomCount;
	}
	float getNumCol() {
		return mazeX_RoomCount;
	}
public:
	//Resets the Maze based off current parameters
	void ResetMaze(sf::RenderWindow& window);

	//Sets the maze based off of input parameters
	void SetMaze(int x, int y, int level, sf::RenderWindow& window);

	//Sets the maze up for the next level
	void NextLevelMaze(sf::RenderWindow& window);

	//Checks what point is in the direction dir relative to the Coordinate pos
	void ChangePosition(MazeCoordinate& pos, directions dir);

	//Creates all the rooms and connects them
	void CreateRooms(sf::RenderWindow& window);

	//Create a maze using a backtracking algorithm
	void CarveMaze(sf::RenderWindow& window);

	//Creates objects in the maze rooms designated during the maze creation. Only called if difficulty is greater than 0

	//Put Key in a random position in the maze where there is currently no other object.
	void CreateKey();

	void CreateObjects();

	//Find a room by the position
	std::shared_ptr<Room> FindRoomByPos(MazeCoordinate pos);

	//Adds an outline of the maze area to the renderer
	void MazeOutline(sf::RenderTarget* target);

	//Adds each room and an outline to the renderer
	void AddMazeRoomsToRenderer(sf::RenderWindow& window);

	//Advances each item one increment in its own cycle of behavior

	void NextMazeCycle();

	void AddMazeObstaclesToRenderer(sf::RenderWindow& window);
	//void BFS_Algorithm(MazeCoordinate posNow);
};
