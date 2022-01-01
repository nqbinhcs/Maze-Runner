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

enum DemoState { InDemoState, InChoosingState };

class StateDemo
{
public:
	sf::RenderWindow* m_pWindow;
private:
	sf::VideoMode m_VideoMode;
	bool m_EndGame;
	sf::Event m_Event;

	//----------------StateDemo State atrributes----------------
	DemoState m_State;
	MazeBot m_Demoer;

	//----------------Display attributes----------------
	//@DESCR: Proven some displays for user such as: Menu screen, GameOver screen, ....
	shared_ptr<HelpAlgorithmMenu> m_pChooseMenu;


	//----------------"In StateDemo processing"  atrributes----------------
	shared_ptr<Maze> curMaze;
	shared_ptr<Player> m_Player;
	shared_ptr<MazeChest> m_Chest;

	//----------------GUI atrributes---------------
	MyText m_Title;
	MyText m_Algorithm[2];

	Button m_ChooseAlgo;
	Button m_Find;
	Button m_ReturnMenu;
	Button m_Generate;

	//----------------Initial GUI functions----------------
	void initVariables();
	void initWindow();
	void initButtons();
	void initText();

	void initTitle();
	void initAlgorithmInfo();


	//----------------Update GUI functions----------------
	void updateAlgorithmInfo();

	//----------------"In game processing" functions----------------
	void resetGame(); //reset all variables of game aka the second initVariables =))))
public:

	//--------Constructors and Destructors--------
	StateDemo();
	~StateDemo();

	//--------Accessors functions--------
	const bool running() const;
	void pollEvents(); //Follow my flow in StateDemo.cpp :D

	//--------Update GUI functions--------
	void update();

	//--------Render GUI functions--------
	void render();
	void renderDisplayStates(DemoState state);
};

#define DEMO_TITLE_WIDTH	(SCREEN_WIDTH - 2 * SPACE)
#define DEMO_TITLE_HEIGHT	(OFFSET_MAZE_Y - 2 * SPACE) 
#define DEMO_OFFSET_TITLE_X		(SPACE + DEMO_TITLE_WIDTH / 2) 
#define DEMO_OFFSET_TITLE_Y		(SPACE + DEMO_TITLE_HEIGHT / 2)

#define DEMO_NUMBER_OF_BOXES 5
#define DEMO_NUMBER_OF_BUTTONS 4

#define DEMO_INFO_HEIGHT (SCREEN_MAZE_Y / DEMO_NUMBER_OF_BOXES)
#define DEMO_INFO_WIDTH (SCREEN_WIDTH - SCREEN_MAZE_X - 2 * SPACE)

#define DEMO_OFFSET_ALGO_X (OFFSET_MAZE_X + SCREEN_MAZE_X + 5 + DEMO_INFO_WIDTH / 2)
#define DEMO_OFFSET_ALGO_Y (OFFSET_MAZE_Y + DEMO_INFO_HEIGHT / 4)
#define DEMO_OFFSET_ALGO_NAME_X DEMO_OFFSET_ALGO_X
#define DEMO_OFFSET_ALGO_NAME_Y (DEMO_OFFSET_ALGO_Y + DEMO_INFO_HEIGHT / 2)

#define DEMO_BUTTON_HEIGHT (DEMO_INFO_HEIGHT / 2)
#define DEMO_BUTTON_WIDTH (DEMO_INFO_WIDTH / 3 * 2)

#define	DEMO_OFFSET_CHOOSE_ALGO_X DEMO_OFFSET_ALGO_X
#define DEMO_OFFSET_CHOOSE_ALGO_Y (DEMO_OFFSET_ALGO_NAME_Y + DEMO_INFO_HEIGHT / 4 * 3)

#define DEMO_OFFSET_FIND_X DEMO_OFFSET_ALGO_X
#define DEMO_OFFSET_FIND_Y (DEMO_OFFSET_CHOOSE_ALGO_Y + DEMO_INFO_HEIGHT)

#define DEMO_OFFSET_GENERATE_X DEMO_OFFSET_FIND_X
#define DEMO_OFFSET_GENERATE_Y (DEMO_OFFSET_FIND_Y + DEMO_INFO_HEIGHT)

#define DEMO_OFFSET_RETURN_MENU_X DEMO_OFFSET_GENERATE_X
#define DEMO_OFFSET_RETURN_MENU_Y (DEMO_OFFSET_GENERATE_Y + DEMO_INFO_HEIGHT)
