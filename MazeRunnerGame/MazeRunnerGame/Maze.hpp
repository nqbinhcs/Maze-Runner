#include <random>
#include "Room.h"
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

class Maze
{

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

	//All objects in this maze
	std::vector<std::shared_ptr<MazeObject>> objectsInMaze;

	//Rect defining maze area
	MazeObject mazeRect;

public:
	int mazeLevel;	//Current Game Level

	//Start and End Position of Maze
	MazeCoordinate startPos;
	MazeCoordinate finalPos;

	//Constructors and Destructors
	Maze(int xCount, int yCount, 
		int xOffset, int yOffset,
		int xSize, int ySize,
		int level, bool showCreation,
		sf::RenderWindow& window);
	Maze(const Maze& other);
	Maze();
	~Maze();

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

	//void CreateObjects()
	//{
	//	for_each(begin(obstacleRooms), end(obstacleRooms), [&](std::shared_ptr<Room> curRoomPtr) {
	//		if (curRoomPtr->roomTypes.size() == 0)
	//		{
	//			//If difficulty is 2 or higher and the room has 3 connected rooms, create a guard
	//			if (curRoomPtr->connectRooms.size() == 3 && mazeLevel > GUARDS_START)
	//			{
	//				std::shared_ptr<MazeGuard> mazeGuardPtr = std::shared_ptr<MazeGuard>(new MazeGuard(curRoomPtr));
	//				objectsInMaze.push_back(std::static_pointer_cast<MazeObject>(mazeGuardPtr));
	//			}
	//			//Otherwise, if the difficulty is 1 or higher, create a Trap
	//			else
	//			{
	//				std::shared_ptr<MazeTrap> mazeTrapPtr = std::shared_ptr<MazeTrap>(new MazeTrap(curRoomPtr));
	//				objectsInMaze.push_back(std::static_pointer_cast<MazeObject>(mazeTrapPtr));
	//			}
	//		}
	//		});
	//}

	//Find a room by the position
	std::shared_ptr<Room> FindRoomByPos(MazeCoordinate pos);

	//Adds an outline of the maze area to the renderer
	void MazeOutline(sf::RenderTarget* target);

	//Adds each room and an outline to the renderer
	void AddMazeRoomsToRenderer(int delay, sf::RenderWindow& window);

	//Advances each item one increment in its own cycle of behavior

	/*void NextMazeCycle()
	{
		for_each(begin(objectsInMaze), end(objectsInMaze), [&](std::shared_ptr<MazeObject> curObjPtr)
			{
				curObjPtr->NextCycle();
			});
	}*/
};
