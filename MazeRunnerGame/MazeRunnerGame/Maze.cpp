#include "Maze.hpp"

Maze::Maze(int xCount, int yCount, int xOffset, int yOffset, int xSize, int ySize, int level, bool showCreation, sf::RenderWindow& window) :
	mazeX_RoomCount(xCount), 
	mazeY_RoomCount(yCount),
	mazeX_Offset(xOffset), 
	mazeY_Offset(yOffset), 
	mazeX_Size(xSize), 
	mazeY_Size(ySize), 
	mazeLevel(level)
{
	mazeRect.setPosition(xOffset, yOffset);
	//mazeRect.(xSize, ySize);
	CreateRooms(window);
	CarveMaze(window);
}

Maze::Maze(const Maze& other) :
	mazeRect(other.mazeRect),
	mazeX_RoomCount(other.mazeX_RoomCount),
	mazeY_RoomCount(other.mazeY_RoomCount),
	allRooms(other.allRooms),
	objectsInMaze(other.objectsInMaze),
	startPos(other.startPos),
	finalPos(other.finalPos)
{
}

Maze::Maze()
{
}
/*
Maze& Maze::operator=(const Maze &other)
{
	allRooms = other.allRooms;
	allTraps = other.allTraps;
	mazeX_RoomCount = other.mazeX_RoomCount;
	mazeY_RoomCount = other.mazeY_RoomCount;
	mazeKeyPtr = other.mazeKeyPtr;
	mazeDoorPtr = other.mazeDoorPtr;
	startPos = other.startPos;
	finalPos = other.finalPos;
	return *this;
}*/

Maze::~Maze()
{
}


//@DESCR: Resets the Maze based off current parameters
//@PARAM: None.
//@RETURN: None
void Maze::ResetMaze(sf::RenderWindow& window)
{
	//Clear all previous vectors
	allRooms.clear();
	obstacleRooms.clear();
	objectsInMaze.clear();

	//Create Maze.
	CreateRooms(window);
	CarveMaze(window);
}

//@DESCR: Sets the maze based off of input parameters
//@PARAM: None.
//@RETURN: None
void Maze::SetMaze(int x, int y, int level, sf::RenderWindow& window)
{
	mazeX_RoomCount = x;
	mazeY_RoomCount = y;
	mazeLevel = level;
	ResetMaze(window);
}

//@DESCR: Sets the maze up for the next level
//@PARAM: None.
//@RETURN: None
void Maze::NextLevelMaze(sf::RenderWindow& window)
{
	mazeLevel++;
	mazeX_RoomCount++;
	mazeY_RoomCount++;
	ResetMaze(window);
}

//@DESCR: Checks what point is in the direction dir relative to the Coordinate pos
//@PARAM: None.
//@RETURN: None
void Maze::ChangePosition(MazeCoordinate& pos, directions dir)
{
	switch (dir)
	{
	case UP:
		pos.setY(pos.getY() - 1);
		//pos.y--;
		break;
	case LEFT:
		pos.setX(pos.getX() - 1);
		//pos.x--;
		break;
	case DOWN:
		pos.setY(pos.getY() + 1);
		//pos.y++;
		break;
	case RIGHT:
		pos.setX(pos.getX() + 1);
		//pos.x++;
		break;
	}
}

//@DESCR: Creates all the rooms and connects them
//@PARAM: None.
//@RETURN: None
void Maze::CreateRooms(sf::RenderWindow& window)
{
	directions allDir[] = { UP, LEFT, DOWN, RIGHT };

	//Creates all the rooms
	for (int x = 0; x < mazeX_RoomCount; x++)
	{
		for (int y = 0; y < mazeY_RoomCount; y++)
		{
			int widthRoom = (int)ceil(mazeX_Size / (mazeX_RoomCount));
			int heightRoom = (int)ceil(mazeY_Size / (mazeY_RoomCount));
			std::shared_ptr<Room> newPtr(new Room(MazeCoordinate(x, y), widthRoom, heightRoom));

			newPtr->MakeRoomRect(mazeX_Offset, mazeY_Offset, mazeX_RoomCount, mazeY_RoomCount, mazeX_Size, mazeY_Size);
			//newPtr->AddRoomToRenderer(window);
			allRooms.push_back(newPtr);
		}
	}

	//Go through all the rooms and make sure each knows what they are adjacent to
	for_each(begin(allRooms), end(allRooms), [&](std::shared_ptr<Room>& curRoomPtr)
		{
			std::for_each(std::begin(allDir), std::end(allDir), [&](directions dir)
				{
					MazeCoordinate testPos = curRoomPtr->roomPos;
					ChangePosition(testPos, dir);
					auto adjRoom = find_if(begin(allRooms), end(allRooms), [&](std::shared_ptr<Room>& checkRoomPtr)
						{
							return checkRoomPtr->roomPos == testPos;
						});
					if (adjRoom != end(allRooms))
					{
						curRoomPtr->adjRooms.push_back((*adjRoom));
						curRoomPtr->availRooms.push_back((*adjRoom));
					}
				});
		});
}

//@DESCR: Create a maze using a backtracking algorithm
//@PARAM: None.
//@RETURN: shared_ptr<Room>
void Maze::CarveMaze(sf::RenderWindow& window)
{
	//This vector acts as a stack that contains the current maze path
	std::vector<std::shared_ptr<Room>> currentPath;

	//Integer that tells us how long the longest path currently is
	size_t longestPath = 0;

	//Checks how many rooms have been added to the maze
	int inMazeCounter = 0;

	//Points to the current room (the top of the stack) and sets it as the starting room
	std::shared_ptr<Room> curRoomPtr = randomElement(allRooms);
	startPos = curRoomPtr->roomPos;
	curRoomPtr->roomTypes.push_back(START);

	while (inMazeCounter < mazeX_RoomCount * mazeY_RoomCount)
	{
		//If the current room is not in the maze yet, put it into the maze and remove it from any available rooms vectors on adjacent rooms
		if (!curRoomPtr->inMaze)
		{
			//Put it into the collection of maze pointers
			currentPath.push_back(curRoomPtr);
			//Set it as in the maze
			curRoomPtr->inMaze = true;
			//Increase the maze counter
			inMazeCounter++;
			//Removes the current room from Available Rooms Vector in any room adjacent to the current one.
			for_each(begin(curRoomPtr->adjRooms), end(curRoomPtr->adjRooms), [&](std::shared_ptr<Room>  adjRoomPtr)
				{
					//Find if the current room is in the available rooms of the current adjacent room
					auto roomToRemoveIter = std::find(begin(adjRoomPtr->availRooms), end(adjRoomPtr->availRooms), curRoomPtr);
					//If the room is found, remove it from the available rooms
					if (roomToRemoveIter != end(adjRoomPtr->availRooms))
					{
						adjRoomPtr->availRooms.erase(roomToRemoveIter);
					}
				});

			//Updates the longest path if the current path (a vector of pointers to the rooms in the path) is longer
			if (longestPath < currentPath.size())
			{
				longestPath = currentPath.size();
				finalPos = curRoomPtr->roomPos;
			}

		}

		//Find the next room if there is one available and connect the current and next room together
		if (!curRoomPtr->availRooms.empty())
		{
			//Sets the pointer for the next room by choosing a random element from rooms available to the current one
			std::shared_ptr <Room> nextRoomPtr = randomElement(curRoomPtr->availRooms);

			//Connects the next room to the current one and vice versa
			curRoomPtr->ConnectRoom(nextRoomPtr);
			nextRoomPtr->ConnectRoom(curRoomPtr);

			//Assign each room's respective room texture then add them to the renderer
			curRoomPtr->AssignRoomTextures();
			nextRoomPtr->AssignRoomTextures();

			//Don't draw step by step.
			//curRoomPtr->AddRoomToRenderer(window);
			//nextRoomPtr->AddRoomToRenderer(window);

			//Removes the next room from the available rooms for the current room 
			curRoomPtr->availRooms.erase(std::find(begin(curRoomPtr->availRooms), end(curRoomPtr->availRooms), nextRoomPtr));

			//Sets the next room pointer as the current room pointer																													
			curRoomPtr = nextRoomPtr;
		}
		//If there is not a room available adjacent to the current one, go back to the previous room
		else
		{
			currentPath.pop_back();
			curRoomPtr = currentPath.back();
		}
	}

	//Places the exit to the maze
	std::shared_ptr<Room> finalRoom = FindRoomByPos(finalPos);
	//mazeDoorPtr = std::shared_ptr<MazeDoor>(new MazeDoor(finalRoom));
	finalRoom->roomTypes.push_back(END);
}

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

//@DESCR: Find a room by the position
//@PARAM: Base on position of room.
//@RETURN: shared_ptr<Room>
std::shared_ptr<Room> Maze::FindRoomByPos(MazeCoordinate pos)
{
	auto iter = (std::find_if(begin(allRooms), end(allRooms), [&](std::shared_ptr<Room> checkRoom) {
		return checkRoom->roomPos == pos;
		}));
	if (iter != end(allRooms))
	{
		return *iter;
	}
	else
	{
		return nullptr;
	}
}

//@DESCR: None
//@PARAM: None
//@RETURN: None
void Maze::MazeOutline(sf::RenderTarget* target)
{
	mazeRect.update(target);
}

//@DESCR: Render maze on window.  Draw each cell(room)
//@PARAM: delay const 0.
//@RETURN: None
void Maze::AddMazeRoomsToRenderer(sf::RenderWindow& window)
{
	for_each(begin(allRooms), end(allRooms), [&](std::shared_ptr<Room> curRoomPtr)
		{
			curRoomPtr->AddRoomToRenderer(window);
		});
	//MazeOutline();
}
