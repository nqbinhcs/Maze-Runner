#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <time.h>

#include<iostream>
#include<ctime>
#include<vector>
#include<sstream>

#include "Clock.hpp"
#include "Player.hpp"
#include "DefinedVariables.hpp"
#include "Maze.hpp"
#include "GameOver.hpp"
#include "NextStage.hpp"
#include "LevelComplete.hpp"
#include "Menu.hpp"
#include "ModeGame.hpp"
#include "Button.hpp"
#include "Helper.hpp"
#include "HelpAlgorithmMenu.hpp"
#include "MazeFactory.hpp"

using namespace sf;

enum GameState { MenuState, InGameState, InHelpState, LevelCompleteState, GameOverState, NextStageState, DifficultyCompleteState};

struct MyLevel {
	int x, y;
};


class Game
{
private:
	static std::shared_ptr<LevelMaze> levelMaze;
	//I don't know how to categorize the methods which be used in each function ._.
	//I think the effective ways in this situation are semantic comments :<
	//I will group all revelant functions into a block and descibe some new functions and attributes
public:
	sf::RenderWindow* m_pWindow;
private:
	sf::VideoMode m_VideoMode;
	bool m_EndGame;
	sf::Event m_Event;

	//----------------Game State atrributes----------------
	GameState m_State;
	Helper m_Helper;

	//----------------Display attributes----------------
	//@DESCR: Proven some displays for user such as: Menu screen, GameOver screen, ....
	shared_ptr<Menu> m_pMenu; //New Game, Continue, ....
	shared_ptr<ModeGame> m_pModeGame; //Easy, Medium, Hard, ....
	shared_ptr<GameOver> m_pGameOver;
	shared_ptr<NextStage> m_pNextStage;
	shared_ptr<HelpAlgorithmMenu> m_pHelpMenu;
	shared_ptr<LevelComplete> m_pLevelComplete;


	//----------------"In Game processing"  atrributes----------------
	shared_ptr<Maze> curMaze;
	shared_ptr<Player> m_Player;
	int m_Points;

	//----------------Stat attributes----------------
	MyClock m_Time; //total times
	int m_Level; //current levels


	//----------------GUI atrributes----------------
	sf::Font m_Font;
	sf::Text m_GuiText;
	sf::Text m_EndGameText;

	MyText m_Title;
	MyText m_LevelInfo;
	MyText m_TimeInfo[2];
	MyText m_CoinsInfo[2];
	
	Button m_Help;
	Button m_ReturnMenu;
	Button m_RestartGame;


	//----------------Initial GUI functions----------------
	void initVariables();
	void initWindow();
	void initFonts();
	void initButtons();
	void initText();

	void initTitle();
	void initLevelInfo();
	void initTimeInfo();
	void initCoinsInfo();


	//----------------Update GUI functions----------------
	void updatePlayer();
	void updateGui();
	void updateTimeInfo();
	void updateCoinsInfo();
	void updateLevel();


	//----------------Render GUI functions----------------
	void renderGui(sf::RenderTarget* target);
	void renderDisplayStates(GameState); //render above Display attributes


	//----------------"In game processing" functions----------------
	void nextLevel(bool check);
	void setLevel(int _level, bool check);
	void resetGame(); //reset all variables of game aka the second initVariables =))))

public:

	//--------Constructors and Destructors--------
	Game();
	~Game();

	//--------Accessors functions--------
	bool getEndGame();
	const bool running() const;
	void pollEvents(); //Follow my flow in Game.cpp :D

	//--------Update GUI functions--------
	void update();

	//--------Render GUI functions--------
	void render();
	
	
};

#define SCREEN_TITLE_WIDTH	(SCREEN_WIDTH - 2 * SPACE)
#define SCREEN_TITLE_HEIGHT	(OFFSET_MAZE_Y - 2 * SPACE) 
#define OFFSET_TITLE_X		(SPACE + SCREEN_TITLE_WIDTH / 2) 
#define OFFSET_TITLE_Y		(SPACE + SCREEN_TITLE_HEIGHT / 2)

#define NUMBER_OF_BOXES 3
#define NUMBER_OF_BUTTONS 3

#define SCREEN_INFO_HEIGHT (SCREEN_MAZE_Y / NUMBER_OF_BOXES)
#define SCREEN_INFO_WIDTH (SCREEN_WIDTH - SCREEN_MAZE_X - 2 * SPACE)	

#define OFFSET_LEVEL_X (OFFSET_MAZE_X + SCREEN_MAZE_X + 5 + SCREEN_INFO_WIDTH / 2)
#define OFFSET_LEVEL_Y (OFFSET_MAZE_Y + SCREEN_INFO_HEIGHT / 2)

#define OFFSET_TIME_X (OFFSET_LEVEL_X - SCREEN_INFO_WIDTH / 4)
#define OFFSET_TIME_Y (OFFSET_LEVEL_Y + SCREEN_INFO_HEIGHT / 4 * 3)
#define OFFSET_TIME_INFO_X OFFSET_TIME_X
#define OFFSET_TIME_INFO_Y (OFFSET_TIME_Y + SCREEN_INFO_HEIGHT / 2)

#define OFFSET_COINS_X (OFFSET_LEVEL_X + SCREEN_INFO_WIDTH / 4)
#define OFFSET_COINS_Y OFFSET_TIME_Y
#define OFFSET_COINS_INFO_X OFFSET_COINS_X
#define OFFSET_COINS_INFO_Y (OFFSET_COINS_Y + SCREEN_INFO_HEIGHT / 2)

#define BUTTON_HEIGHT (SCREEN_INFO_HEIGHT / 2)
#define BUTTON_WIDTH (SCREEN_INFO_WIDTH / (NUMBER_OF_BUTTONS + 1))
#define BUTTON_SPACE (BUTTON_WIDTH / (NUMBER_OF_BUTTONS + 1))

#define OFFSET_HELP_X (OFFSET_LEVEL_X - SCREEN_INFO_WIDTH / 2 + BUTTON_SPACE + BUTTON_WIDTH / 2)
#define OFFSET_HELP_Y (OFFSET_TIME_INFO_Y + SCREEN_INFO_HEIGHT / 4 * 3)

#define OFFSET_RESTART_X (OFFSET_HELP_X + BUTTON_WIDTH + BUTTON_SPACE)
#define OFFSET_RESTART_Y OFFSET_HELP_Y

#define OFFSET_RETURN_MENU_X (OFFSET_RESTART_X + BUTTON_WIDTH + BUTTON_SPACE)
#define OFFSET_RETURN_MENU_Y OFFSET_HELP_Y