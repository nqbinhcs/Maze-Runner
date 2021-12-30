#include "Maze.hpp"

bool Maze::isWin() {
	if (level == maxLevel - 1) {
		return true;
	}
	return false;
}

void Maze::UpdateMaze(bool next) {
	if (next == true) {
		ResetMaze();
		UpdateLevel(next);

		//Create Maze.
		CreateRooms();
		CarveMaze();

		RandomConnectRoom();

		CreatChest();
		CreateKeys();
		CreatCoins();

		CreateObjects();
		cout << "LEVEL: " << level << endl;
	}
}

float Maze::getWidthRoom() {
	return int(mazeX_Size / numRoomX);
}
float Maze::getHeightRoom() {
	return int(mazeY_Size / numRoomY);
}

bool Maze::CheckGetKeyAtPos(MazeCoordinate pos) {
	for (int i = 0; i < mazeKey.size(); i++) {
		if (mazeKey[i]->getPosition() == pos) {
			isTakeKey[i] = true;
			return true;
		}
	}
}
bool Maze::CheckGetAllKey() {
	for (int i = 0; i < isTakeKey.size(); i++) {
		if (isTakeKey[i] == false) {
			return false;
		}
	}
	return true;
}

void Maze::PrepareInforLevel() {
	roomRandom = countRoom_Random[level];
	numKey = countKey[level];
	numTrap = countTrap[level];
	numGuard = countGuard[level];
	numCoin = countCoin[level];

	numRoomX = mazeX_RoomCount[level];
	numRoomY = mazeY_RoomCount[level];

	for (int i = 0; i < numKey; i++) {
		isTakeKey.push_back(false);
	}
	for (int i = 0; i < numCoin; i++) {
		isTakeCoin.push_back(false);
	}
	isTakeChest = false;
}
void Maze::ResetMaze() {
	//Clear all previous vectors
	allRooms.clear();
	obstacleRooms.clear();
	mazeGuard.resize(0);
	mazeTrap.resize(0);
	mazeKey.resize(0);
	mazeCoin.resize(0);

}
void Maze::UpdateLevel(bool next) {
	if (next == true) {
		level++;
	}
	PrepareInforLevel();
}

void Maze::ChangePosition(MazeCoordinate& pos, directions dir) {
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
void Maze::CreateRooms() {
	directions allDir[] = { UP, LEFT, DOWN, RIGHT };

	//Creates all the rooms
	for (int x = 0; x < numRoomX; x++)
	{
		for (int y = 0; y < numRoomY; y++)
		{
			int widthRoom = (int)ceil(mazeX_Size / (numRoomX));
			int heightRoom = (int)ceil(mazeY_Size / (numRoomX));
			std::shared_ptr<Room> newPtr(new Room(MazeCoordinate(x, y), widthRoom, heightRoom));

			newPtr->MakeRoomRect(mazeX_Offset, mazeY_Offset, numRoomX, numRoomY, mazeX_Size, mazeY_Size);
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
void Maze::CarveMaze() {
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

	while (inMazeCounter < numRoomX * numRoomY)
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

			//If the maze level passes the level at which we want to spawn traps, we start spawning traps
			if (numGuard != 0 || numTrap != 0)
			{
				//Places rooms that can have obstacles a distance apart based off of trap spacing
				int obstacleSpacing = 3;
				if (currentPath.size() % obstacleSpacing == 0)
				{
					obstacleRooms.push_back(curRoomPtr);
				}
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
}

void Maze::CreateObjects() {
	std::shared_ptr<Room> curRoomPtr;
	for (int i = 0; i < numTrap; i++) {
		do
		{
			curRoomPtr = randomElement(obstacleRooms);
		} while (curRoomPtr->roomTypes.size() != 0);
		curRoomPtr->roomTypes.push_back(TRAP);
		mazeTrap.push_back(std::shared_ptr<MazeTrap>(new MazeTrap(curRoomPtr->roomPos, mazeX_Offset, mazeY_Offset, int(mazeX_Size / numRoomX), int(mazeY_Size / numRoomY))));
	}
	for (int i = 0; i < numGuard; i++) {
		do
		{
			curRoomPtr = randomElement(obstacleRooms);
			if (curRoomPtr->roomTypes.size() == 0 && curRoomPtr->connectRooms.size() == 3) {
				break;
			}
		} while (1);
		cout << "Connect: " << curRoomPtr->connectRooms.size() << endl;
		curRoomPtr->roomTypes.push_back(TRAP);
		mazeGuard.push_back(std::shared_ptr<MazeGuard>(new MazeGuard(curRoomPtr, curRoomPtr->roomPos, mazeX_Offset, mazeY_Offset, int(mazeX_Size / numRoomX), int(mazeY_Size / numRoomY))));
	}


	/*
	int trap = numTrap;
	int guard = numGuard;

	for (int i = 0; i < obstacleRooms.size() - 1; i++) {
		if (obstacleRooms[i]->roomTypes.size() == 0)
		{
			i++;
			if (obstacleRooms[i]->connectRooms.size() == 3 && guard > 0 && i % 3 == 0)
			{
				guard--;
				obstacleRooms[i]->roomTypes.push_back(GUARD);
				mazeGuard.push_back(std::shared_ptr<MazeGuard>(new MazeGuard(obstacleRooms[i], obstacleRooms[i]->roomPos, mazeX_Offset, mazeY_Offset, int(mazeX_Size / numRoomX), int(mazeY_Size / numRoomY))));
			}
			else if (trap > 0 && i % 3 == 0)
			{
				trap--;
				obstacleRooms[i]->roomTypes.push_back(TRAP);
				mazeTrap.push_back(std::shared_ptr<MazeTrap>(new MazeTrap(obstacleRooms[i]->roomPos, mazeX_Offset, mazeY_Offset, int(mazeX_Size / numRoomX), int(mazeY_Size / numRoomY))));
			}
		}
	}*/


	/*if (guard == numGuard) {
		for (int i = 0; i < numGuard * 2; i++) {
			if (guard == 0) {
				return;
			}
			std::shared_ptr<Room> curRoomPtr = randomElement(obstacleRooms);
			if (curRoomPtr->connectRooms.size() == 3 && guard > 0)
			{
				guard--;
				curRoomPtr->roomTypes.push_back(GUARD);
				mazeGuard.push_back(std::shared_ptr<MazeGuard>(new MazeGuard(curRoomPtr, curRoomPtr->roomPos, mazeX_Offset, mazeY_Offset, int(mazeX_Size / numRoomX), int(mazeY_Size / numRoomY))));
			}
		}
	}*/
}
void Maze::NextMazeCycle() {
	for (int i = 0; i < mazeGuard.size(); i++) {
		mazeGuard[i]->NextCycle();
	}

	for (int i = 0; i < mazeTrap.size(); i++) {
		mazeTrap[i]->NextCycle();
	}
}

void Maze::CreateKeys() {
	std::shared_ptr<Room> curRoomPtr;
	for (int i = 0; i < numKey; i++) {
		do
		{
			curRoomPtr = randomElement(allRooms);
		} while (curRoomPtr->roomTypes.size() > 0);
		curRoomPtr->roomTypes.push_back(KEY);
		mazeKey.push_back(std::shared_ptr<MazeKey>(new MazeKey(curRoomPtr->roomPos, mazeX_Offset, mazeY_Offset, int(mazeX_Size / numRoomX), int(mazeY_Size / numRoomY))));
	}

}
void Maze::CreatChest() {
	//Places the exit to the maze
	std::shared_ptr<Room> finalRoom = FindRoomByPos(finalPos);
	mazeChest = std::shared_ptr<MazeChest>(new MazeChest(finalRoom->roomPos, mazeX_Offset, mazeY_Offset, int(mazeX_Size / numRoomX), int(mazeY_Size / numRoomY)));
	finalRoom->roomTypes.push_back(END);
}
void Maze::CreatCoins() {
	std::shared_ptr<Room> curRoomPtr;
	for (int i = 0; i < numCoin; i++) {
		do
		{
			curRoomPtr = randomElement(allRooms);
		} while (curRoomPtr->roomTypes.size() > 0);
		curRoomPtr->roomTypes.push_back(COIN);
		mazeCoin.push_back(std::shared_ptr<MazeCoin>(new MazeCoin(curRoomPtr->roomPos, mazeX_Offset, mazeY_Offset, int(mazeX_Size / numRoomX), int(mazeY_Size / numRoomY))));
	}
}

bool Maze::checkBorder(MazeCoordinate pos) {
	if (pos.getX() == 0 || pos.getX() == numRoomX || pos.getY() == 0 || pos.getY() == numRoomY) {
		return true;
	}
	return false;
}
void Maze::RandomConnectRoom() {
	for (int i = 1; i < numRoomY - 1; i += 1) {
		for (int j = 1; j < numRoomX - 1; j += 1) {
			if (roomRandom == 0) {
				return;
			}
			int pos = i * numRoomX + j;
			if (pos % 4 == 0) {

				MazeCoordinate posCenter = allRooms[i * numRoomX + j]->roomPos;
				int random[4] = { 1, 2, 3 ,4 };
				int i_ran = 0;
				while (checkBorder(posCenter) == false && allRooms[i * numRoomX + j]->connectRooms.size() <= 2) {
					//int random = rand() % 4 + 1;
					if (random[i_ran] == 1) {
						//Kiểm tra ô bên trái có đã kết nối với room center
						std::shared_ptr<Room> checkRoom = allRooms[i * numRoomX + j]->checkPosConnectRoom(MazeCoordinate(posCenter.getX() - 1, posCenter.getY()));
						if (checkRoom == NULL) {
							checkRoom = FindRoomByPos(MazeCoordinate(posCenter.getX() - 1, posCenter.getY()));
							if (checkRoom != NULL) {
								allRooms[i * numRoomX + j]->ConnectRoom(checkRoom);
								checkRoom->ConnectRoom(allRooms[i * numRoomX + j]);

								//Assign each room's respective room texture then add them to the renderer
								allRooms[i * numRoomX + j]->AssignRoomTextures();
								checkRoom->AssignRoomTextures();
								roomRandom--;
							}
						}
						i_ran++;
					}
					else if (random[i_ran] == 2) {
						//Kiểm tra ô bên phải có đã kết nối với room center
						std::shared_ptr<Room> checkRoom = allRooms[i * numRoomX + j]->checkPosConnectRoom(MazeCoordinate(posCenter.getX() + 1, posCenter.getY()));
						if (checkRoom == NULL) {
							checkRoom = FindRoomByPos(MazeCoordinate(posCenter.getX() + 1, posCenter.getY()));
							if (checkRoom != NULL) {
								allRooms[i * numRoomX + j]->ConnectRoom(checkRoom);
								checkRoom->ConnectRoom(allRooms[i * numRoomX + j]);

								//Assign each room's respective room texture then add them to the renderer
								allRooms[i * numRoomX + j]->AssignRoomTextures();
								checkRoom->AssignRoomTextures();
								roomRandom--;
							}
						}
						i_ran++;
					}
					else if (random[i_ran] == 3) {
						//Kiểm tra ô bên trên có đã kết nối với room center
						std::shared_ptr<Room> checkRoom = allRooms[i * numRoomX + j]->checkPosConnectRoom(MazeCoordinate(posCenter.getX(), posCenter.getY() - 1));
						if (checkRoom == NULL) {
							checkRoom = FindRoomByPos(MazeCoordinate(posCenter.getX(), posCenter.getY() - 1));
							if (checkRoom != NULL) {
								allRooms[i * numRoomX + j]->ConnectRoom(checkRoom);
								checkRoom->ConnectRoom(allRooms[i * numRoomX + j]);

								//Assign each room's respective room texture then add them to the renderer
								allRooms[i * numRoomX + j]->AssignRoomTextures();
								checkRoom->AssignRoomTextures();
								roomRandom--;
							}
						}
						i_ran++;
					}
					else if (random[i_ran] == 4) {
						//Kiểm tra ô bên dưới có đã kết nối với room center
						std::shared_ptr<Room> checkRoom = allRooms[i * numRoomX + j]->checkPosConnectRoom(MazeCoordinate(posCenter.getX(), posCenter.getY() + 1));
						if (checkRoom == NULL) {
							checkRoom = FindRoomByPos(MazeCoordinate(posCenter.getX(), posCenter.getY() + 1));
							if (checkRoom != NULL) {
								allRooms[i * numRoomX + j]->ConnectRoom(checkRoom);
								checkRoom->ConnectRoom(allRooms[i * numRoomX + j]);

								//Assign each room's respective room texture then add them to the renderer
								allRooms[i * numRoomX + j]->AssignRoomTextures();
								checkRoom->AssignRoomTextures();
								roomRandom--;
							}
						}
						i_ran++;
					}
				}
			}
		}
	}
}

std::shared_ptr<Room> Maze::FindRoomByPos(MazeCoordinate pos) {
	auto iter = (std::find_if(begin(allRooms), end(allRooms), [&](std::shared_ptr<Room> checkRoom) {
		return checkRoom->roomPos == pos;
		}));
	if (iter != end(allRooms))
	{
		return *iter;
	}
	else
	{
		return NULL;
	}
}

void Maze::AddMazeRoomsToRenderer(sf::RenderWindow& window) {
	for_each(begin(allRooms), end(allRooms), [&](std::shared_ptr<Room> curRoomPtr)
		{
			curRoomPtr->AddRoomToRenderer(window);
		});

	for (int i = 0; i < mazeKey.size(); i++) {
		if (isTakeKey[i] == false) {
			mazeKey[i]->render(window);
		}
	}
	for (int i = 0; i < mazeCoin.size(); i++) {
		if (isTakeCoin[i] == false) {
			mazeCoin[i]->render(window);
		}
	}
	if (isTakeChest == false) {
		mazeChest->render(window);
	}
}
void Maze::AddMazeObstaclesToRenderer(sf::RenderWindow& window) {
	for (int i = 0; i < mazeGuard.size(); i++) {
		mazeGuard[i]->render(window);
	}

	for (int i = 0; i < mazeTrap.size(); i++) {
		mazeTrap[i]->render(window);
	}
}
