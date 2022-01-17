#include "Maze.hpp"
#include "Player.hpp"
#include "MazeFactory.hpp"
#include <fstream>
#pragma once
class SaveLoadGame
{
	string nameFile;
public:
	SaveLoadGame(string file) {
		nameFile = file;
	}

	//FORM SAVE:
	//EASY/MEDIUM/HARD.
	//Level.
	//TimesPlayed.
	//Start Position.
	//Final Position.
	//Player Position.
	//Maze.
	//MazeConnect.
	//Maze of position Trap/Guard/Coin/Key.
	//Maze appear or hide of coin and key.
	void LoadGameContinue(shared_ptr<Maze>& curMaze, shared_ptr<Player>& m_Player);
	void SaveGameContiune(shared_ptr<Maze> curMaze, shared_ptr<Player> m_Player);

	static void copyFileToFile(string src, string des)
	{
		ifstream source(src.c_str(), ios::binary);
		if (!source.is_open()) return;
		ofstream dest(des.c_str(), ios::binary);

		dest << source.rdbuf();

		source.close();
		dest.close();
	}
};

