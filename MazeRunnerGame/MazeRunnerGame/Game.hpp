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

using namespace sf;

enum GameState { MenuState, InGameState, LevelCompleteState, GameOverState, NextStageState, DifficultyCompleteState};

struct MyLevel {
	int x, y;
};


class Game
{
public:
	sf::RenderWindow* m_pWindow;
private:
	sf::VideoMode m_VideoMode;
	bool m_EndGame;
	sf::Event m_Event;

	//Game State
	GameState m_State;

	//Display

	shared_ptr<Menu> m_pMenu;
	shared_ptr<ModeGame> m_pModeGame;
	shared_ptr<GameOver> m_pGameOver;
	shared_ptr<NextStage> m_pNextStage;
	shared_ptr<LevelComplete> m_pLevelComplete;

	//In Game
	shared_ptr<Maze> curMaze;

	shared_ptr<Player> m_Player;
	int m_Points;

	//Gui
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

	//static
	MyClock m_Time; //total times
	int m_Level; //current levels

	//GUI functions
	void initVariables();
	void initWindow();
	void initFonts();
	void initButtons();
	void initText();
	void initMap();

	//Processing functions
	void nextLevel();
	void setLevel(int _level);

public:
	//Constructors and Destructors
	Game();
	~Game();

	//Accessors
	bool getEndGame();


	//Game processing
	const bool running() const;
	void pollEvents();

	void updatePlayer();
	//void updateCollision();
	void updateGui();
	void update();

	void renderGui(sf::RenderTarget* target);
	void render();

	void renderDisplayStates(GameState);

	//Modifiers
	void initTitle();
	void initLevelInfo();
	void initTimeInfo();
	void initCoinsInfo();

	void updateTimeInfo();
	void updateCoinsInfo();
	void updateLevel();

	//Functions
	void resetGame();

	
};

#define SCREEN_TITLE_WIDTH	(SCREEN_WIDTH - 2 * SPACE)
#define SCREEN_TITLE_HEIGHT	(OFFSET_MAZE_Y - 2 * SPACE) 
#define OFFSET_TITLE_X		SPACE
#define OFFSET_TITLE_Y		SPACE

#define NUMBER_OF_BOXES 3
#define NUMBER_OF_BUTTONS 3

#define SCREEN_INFO_HEIGHT (SCREEN_MAZE_HEIGHT / NUMBER_OF_BOXES)
#define SCREEN_INFO_WIDTH (SCREEN_WIDTH - SCREEN_MAZE_WIDTH - 2 * SPACE)	

#define OFFSET_LEVEL_X (OFFSET_MAZE_X + SCREEN_MAZE_WIDTH + 5)
#define OFFSET_LEVEL_Y OFFSET_MAZE_Y

#define OFFSET_TIME_X OFFSET_LEVEL_X
#define OFFSET_TIME_Y (OFFSET_LEVEL_Y + SCREEN_INFO_HEIGHT)
#define OFFSET_TIME_INFO_X OFFSET_TIME_X
#define OFFSET_TIME_INFO_Y (OFFSET_TIME_Y + SCREEN_INFO_HEIGHT / 2)

#define OFFSET_COINS_X (OFFSET_LEVEL_X + SCREEN_INFO_WIDTH / 2)
#define OFFSET_COINS_Y OFFSET_TIME_Y
#define OFFSET_COINS_INFO_X OFFSET_COINS_X
#define OFFSET_COINS_INFO_Y (OFFSET_COINS_Y + SCREEN_INFO_HEIGHT / 2)

#define BUTTON_HEIGHT (SCREEN_INFO_HEIGHT / 2)
#define BUTTON_WIDTH (SCREEN_INFO_WIDTH / (NUMBER_OF_BUTTONS + 1))
#define BUTTON_SPACE (BUTTON_WIDTH / (NUMBER_OF_BUTTONS + 1))

#define OFFSET_HELP_X (OFFSET_LEVEL_X + BUTTON_SPACE)
#define OFFSET_HELP_Y (OFFSET_TIME_Y + SCREEN_INFO_HEIGHT + BUTTON_HEIGHT / 2)

#define OFFSET_RESTART_X (OFFSET_HELP_X + BUTTON_WIDTH + BUTTON_SPACE)
#define OFFSET_RESTART_Y OFFSET_HELP_Y

#define OFFSET_RETURN_MENU_X (OFFSET_RESTART_X + BUTTON_WIDTH + BUTTON_SPACE)
#define OFFSET_RETURN_MENU_Y OFFSET_HELP_Y