#include "ContinueGame.hpp"


void SaveLoadGame::LoadGameContinue(shared_ptr<Maze>& curMaze, shared_ptr<Player>& m_Player) {
	fstream f;
	f.open(nameFile.c_str(), ios::in);
	string sLevel;
	int numLevel;
	f >> sLevel;
	f >> numLevel;
	if (sLevel == "EASY") {
		std::shared_ptr<LevelMaze> levelMaze = std::shared_ptr<LevelMaze>(new EasyLevelMaze());
		curMaze = levelMaze->OrderLevelMaze();;
	}
	else if (sLevel == "MEDIUM") {
		std::shared_ptr<LevelMaze> levelMaze = std::shared_ptr<LevelMaze>(new MediumLevelMaze());
		curMaze = levelMaze->OrderLevelMaze();;
	}
	else if (sLevel == "HARD") {
		std::shared_ptr<LevelMaze> levelMaze = std::shared_ptr<LevelMaze>(new HardLevelMaze());
		curMaze = levelMaze->OrderLevelMaze();;
	}
	//Change to level equal level now.
	while (numLevel != curMaze->getLevel()) {
		curMaze->ResetMaze();
		curMaze->UpdateLevel(true);
		//Don't carveMaze new.
	}
	//Creat all room.
	curMaze->ResetMaze();
	curMaze->UpdateLevel(false);
	curMaze->CreateRooms();

	//Get timesPlayed
	int timesPlayed;
	f >> timesPlayed;

	//Get coin
	int coin;
	f >> coin;
	

	//Get mazeStartPos, mazeFinalPos, playerPos
	MazeCoordinate startPos, finalPos, playerPos;
	int x_pos, y_pos;

	f >> x_pos >> y_pos;
	startPos.setX(x_pos);
	startPos.setY(y_pos);

	f >> x_pos >> y_pos;
	finalPos.setX(x_pos);
	finalPos.setY(y_pos);

	f >> x_pos >> y_pos;
	playerPos.setX(x_pos);
	playerPos.setY(y_pos);

	//Set size of matrix.
	vector<vector<int>> maze;
	vector<vector<int>> mazeObject;
	vector<vector<int>> mazeCheckTake;

	int X = curMaze->getNumRoomX();
	int Y = curMaze->getNumRoomY();

	maze.resize(Y);
	mazeObject.resize(Y);
	mazeCheckTake.resize(Y);

	for (int i = 0; i < Y; i++) {
		maze[i].resize(X);
		for (int j = 0; j < X; j++) {
			f >> maze[i][j];
		}
	}
	for (int i = 0; i < Y; i++) {
		mazeObject[i].resize(X);
		for (int j = 0; j < X; j++) {
			f >> mazeObject[i][j];
		}
	}
	for (int i = 0; i < Y; i++) {
		mazeCheckTake[i].resize(X);
		for (int j = 0; j < X; j++) {
			f >> mazeCheckTake[i][j];
		}
	}

	//Set image new and postion of room, object and coin or key have appear or hide.
	curMaze->setMazeFromFile(maze, mazeObject, mazeCheckTake, startPos, finalPos);

	//After creat maze, then creat player.
	m_Player = std::shared_ptr<Player>(new Player(curMaze->getStartPos(), OFFSET_MAZE_X, OFFSET_MAZE_Y, curMaze->getWidthRoom(), curMaze->getHeightRoom()));
	m_Player->setPosition(playerPos);
	m_Player->setTotalCoin(coin);
	m_Player->setTimes(timesPlayed);
}
void SaveLoadGame::SaveGameContiune(shared_ptr<Maze> curMaze, shared_ptr<Player> m_Player) {
	fstream f;
	f.open(nameFile.c_str(), ios::out);

	f << curMaze->getNameLevel() << endl;
	f << curMaze->getLevel() << endl;
	f << m_Player->getTimesPlayed() << endl;
	f << m_Player->getTotalCoin() << endl;

	MazeCoordinate pos = curMaze->getStartPos();
	f << pos.getX() << " " << pos.getY() << endl;

	pos = curMaze->getFinalPos();
	f << pos.getX() << " " << pos.getY() << endl;

	pos = m_Player->getPosition();
	f << pos.getX() << " " << pos.getY() << endl;

	int X = curMaze->getNumRoomX();
	int Y = curMaze->getNumRoomY();
	for (int i = 0; i < Y; i++) {
		int j = 0;
		int a;
		for (; j < X - 1; j++) {
			a = curMaze->getDirRoom(j * Y + i);
			f << a << " ";
		}
		a = curMaze->getDirRoom(j * Y + i);
		f << a << endl;
	}

	//TRAP 1;	GUARD 2;	KEY 3;	COIN 4
	vector<vector<int>> matrix;
	matrix.resize(Y);
	for (int i = 0; i < Y; i++) {
		matrix[i].resize(X);
		for (int j = 0; j < X; j++) {
			matrix[i][j] = 0;
		}
	}

	//TRAP
	for (int t = 0; t < curMaze->getSizeObj(1); t++) {
		pos = curMaze->getPos(t, 1);
		matrix[pos.getY()][pos.getX()] += 1;
	}
	//GUARD
	for (int t = 0; t < curMaze->getSizeObj(2); t++) {
		pos = curMaze->getCenterPosGuard(t);
		matrix[pos.getY()][pos.getX()] += 2;
	}
	//KEY
	for (int t = 0; t < curMaze->getSizeObj(3); t++) {
		pos = curMaze->getPos(t, 3);
		matrix[pos.getY()][pos.getX()] += 3;
	}
	//COIN
	for (int t = 0; t < curMaze->getSizeObj(4); t++) {
		pos = curMaze->getPos(t, 4);
		matrix[pos.getY()][pos.getX()] += 4;
	}

	//SAVE
	for (int i = 0; i < Y; i++) {
		int j = 0;
		for (; j < X - 1; j++) {
			f << matrix[i][j] << " ";
		}
		f << matrix[i][j] << endl;
	}


	//Save position appear(1) or hide(0) of COIN AND KEY.
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			matrix[i][j] = 0;
		}
	}
	//KEY
	for (int t = 0; t < curMaze->getSizeObj(3); t++) {
		pos = curMaze->getPos(t, 3);
		matrix[pos.getY()][pos.getX()] = curMaze->getTake(t, 1);
	}
	//COIN
	for (int t = 0; t < curMaze->getSizeObj(4); t++) {
		pos = curMaze->getPos(t, 4);
		matrix[pos.getY()][pos.getX()] = curMaze->getTake(t, 2);
	}

	//SAVE
	for (int i = 0; i < Y; i++) {
		int j = 0;
		for (; j < X - 1; j++) {
			f << matrix[i][j] << " ";
		}
		f << matrix[i][j] << endl;
	}
	f.close();
}
