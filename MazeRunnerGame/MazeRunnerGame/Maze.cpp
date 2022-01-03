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
	obstacleRoomsGuard.clear();
	mazeGuard.clear();
	mazeTrap.clear();
	mazeKey.clear();
	mazeCoin.clear();
	isTakeCoin.clear();
	isTakeKey.clear();

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

bool Maze::checkAroundPosStart(MazeCoordinate pos) {
	//Nearest is 4 rooms
	for (int i = 1; i <= 4; i++) {
		if (startPos.getX() - i == pos.getX() && startPos.getY() == pos.getY()) {
			return false;
		}
		if (startPos.getX() + i == pos.getX() && startPos.getY() == pos.getY()) {
			return false;
		}
		if (startPos.getX() == pos.getX() && startPos.getY() - i == pos.getY()) {
			return false;
		}
		if (startPos.getX() == pos.getX() && startPos.getY() + i == pos.getY()) {
			return false;
		}
	}
	return true;
}
void Maze::CreateObjects() {
	std::shared_ptr<Room> curRoomPtr;

	for (int i = 0; i < allRooms.size(); i++) {
		curRoomPtr = allRooms[i];
		if ((curRoomPtr->roomTypes.size() == 0 && curRoomPtr->connectRooms.size() == 3))
		{
			obstacleRoomsGuard.push_back(curRoomPtr);
		}
	}

	int i = 0;
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
			curRoomPtr = randomElement(obstacleRoomsGuard);
			if (curRoomPtr->roomTypes.size() == 0 && curRoomPtr->connectRooms.size() == 3 && checkAroundPosStart(curRoomPtr->roomPos)) {
				break;
			}
		} while (1);
		curRoomPtr->roomTypes.push_back(TRAP);
		mazeGuard.push_back(std::shared_ptr<MazeGuard>(new MazeGuard(curRoomPtr, curRoomPtr->roomPos, mazeX_Offset, mazeY_Offset, int(mazeX_Size / numRoomX), int(mazeY_Size / numRoomY))));
	}
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

void Maze::ConnectEachOther(std::shared_ptr<Room> roomNow, int x, int y) {
	std::shared_ptr<Room> room = FindRoomByPos(MazeCoordinate(roomNow->roomPos.getX() + x, roomNow->roomPos.getY() + y));
	roomNow->connectRooms.push_back(room);
}
void Maze::addObjFromFile(int pos, int type) {
	//TRAP 1;	GUARD 2;	KEY 3;	COIN 4
	std::shared_ptr<Room> curRoomPtr = allRooms[pos];
	if (type == 1) {
		curRoomPtr->roomTypes.push_back(TRAP);
		mazeTrap.push_back(std::shared_ptr<MazeTrap>(new MazeTrap(curRoomPtr->roomPos, mazeX_Offset, mazeY_Offset, int(mazeX_Size / numRoomX), int(mazeY_Size / numRoomY))));
	}
	else if (type == 2) {
		curRoomPtr->roomTypes.push_back(GUARD);
		mazeGuard.push_back(std::shared_ptr<MazeGuard>(new MazeGuard(curRoomPtr, curRoomPtr->roomPos, mazeX_Offset, mazeY_Offset, int(mazeX_Size / numRoomX), int(mazeY_Size / numRoomY))));
	}
	else if (type == 3) {
		curRoomPtr->roomTypes.push_back(KEY);
		mazeKey.push_back(std::shared_ptr<MazeKey>(new MazeKey(curRoomPtr->roomPos, mazeX_Offset, mazeY_Offset, int(mazeX_Size / numRoomX), int(mazeY_Size / numRoomY))));
	}
	else if (type == 4) {
		curRoomPtr->roomTypes.push_back(COIN);
		mazeCoin.push_back(std::shared_ptr<MazeCoin>(new MazeCoin(curRoomPtr->roomPos, mazeX_Offset, mazeY_Offset, int(mazeX_Size / numRoomX), int(mazeY_Size / numRoomY))));
	}
}
void Maze::setMazeFromFile(vector<vector<int>> maze, vector<vector<int>> mazeObj, vector<vector<int>> checkObj, MazeCoordinate startP, MazeCoordinate finalP) {
	//Set start and final.
	setStartPos(startP);
	setFinalPos(finalP);

	//Set image to Room.
	for (int i = 0; i < maze.size(); i++) {
		for (int j = 0; j < maze[i].size(); j++) {
			setDirRoom(j * maze.size() + i, maze[i][j]);
		}
	}

	//Change image of Room.
	for (int i = 0; i < allRooms.size(); i++) {
		allRooms[i]->AssignRoomTextures();
	}

	//Connect room with each other.
	for (int i = 0; i < allRooms.size(); i++) {
		//1-D; 2-L, 8-R, 4-U, 3-DL, 9-DR, 5-DU, 
		// 10-LR, 6-LU, 12-UR,	11 - DLR, 7 - DLU, 
		//13 - DUR 14 - LUR    15NULL
		if (allRooms[i]->wallDirBit == 1) {
			//Connect Room Left, Right, Up
			ConnectEachOther(allRooms[i], -1, 0);
			ConnectEachOther(allRooms[i], 1, 0);
			ConnectEachOther(allRooms[i], 0, -1);
		}
		else if (allRooms[i]->wallDirBit == 2) {
			//Connect Room Right and Down, UP
			ConnectEachOther(allRooms[i], 1, 0);
			ConnectEachOther(allRooms[i], 0, 1);
			ConnectEachOther(allRooms[i], 0, -1);
		}
		else if (allRooms[i]->wallDirBit == 3) {
			//Connect Room Right and up
			ConnectEachOther(allRooms[i], 1, 0);
			ConnectEachOther(allRooms[i], 0, -1);
		}
		else if (allRooms[i]->wallDirBit == 4) {
			//Connect Room Right and Down,left
			ConnectEachOther(allRooms[i], 1, 0);
			ConnectEachOther(allRooms[i], -1, 0);
			ConnectEachOther(allRooms[i], 0, 1);
		}
		else if (allRooms[i]->wallDirBit == 5) {
			//Connect Room Right and left
			ConnectEachOther(allRooms[i], 1, 0);
			ConnectEachOther(allRooms[i], -1, 0);
		}
		else if (allRooms[i]->wallDirBit == 6) {
			//Connect Room Right and down
			ConnectEachOther(allRooms[i], 1, 0);
			ConnectEachOther(allRooms[i], 0, 1);
		}
		else if (allRooms[i]->wallDirBit == 7) {
			//Connect Room right
			ConnectEachOther(allRooms[i], 1, 0);
		}
		else if (allRooms[i]->wallDirBit == 8) {
			//Connect Room left, down, up
			ConnectEachOther(allRooms[i], -1, 0);
			ConnectEachOther(allRooms[i], 0, 1);
			ConnectEachOther(allRooms[i], 0, -1);
		}
		else if (allRooms[i]->wallDirBit == 9) {
			//Connect Room left, up
			ConnectEachOther(allRooms[i], -1, 0);
			ConnectEachOther(allRooms[i], 0, -1);
		}
		else if (allRooms[i]->wallDirBit == 10) {
			//Connect Room down, up
			ConnectEachOther(allRooms[i], 0, 1);
			ConnectEachOther(allRooms[i], 0, -1);
		}
		else if (allRooms[i]->wallDirBit == 11) {
			//Connect Room up
			ConnectEachOther(allRooms[i], 0, -1);
		}
		else if (allRooms[i]->wallDirBit == 12) {
			//Connect Room left, down
			ConnectEachOther(allRooms[i], -1, 0);
			ConnectEachOther(allRooms[i], 0, 1);
		}
		else if (allRooms[i]->wallDirBit == 13) {
			//Connect Room left
			ConnectEachOther(allRooms[i], -1, 0);
		}
		else if (allRooms[i]->wallDirBit == 14) {
			//Connect Room down
			ConnectEachOther(allRooms[i], 0, 1);
		}
	}

	//TRAP 1;	GUARD 2;	KEY 3;	COIN 4
	for (int i = 0; i < mazeObj.size(); i++) {
		for (int j = 0; j < mazeObj[i].size(); j++) {
			if (mazeObj[i][j] == 1) {
				addObjFromFile(j * mazeObj.size() + i, 1);
			}
			else if (mazeObj[i][j] == 2) {
				addObjFromFile(j * mazeObj.size() + i, 2);
			}
			else if (mazeObj[i][j] == 3) {
				addObjFromFile(j * mazeObj.size() + i, 3);
				if (checkObj[i][j] == 1) {
					setTake(mazeKey.size() - 1, 1);
				}
			}
			else if (mazeObj[i][j] == 4) {
				addObjFromFile(j * mazeObj.size() + i, 4);
				if (checkObj[i][j] == 1) {
					setTake(mazeCoin.size() - 1, 2);
				}
			}
		}
	}

	//Set chest.
	CreatChest();
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
