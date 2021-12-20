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
#include "TileMap.h"
#include "Maze.hpp"
#include "GameOver.hpp"
#include "NextStage.hpp"
#include "LevelComplete.hpp"
#include "Menu.hpp"
#include "ModeGame.hpp"

using namespace sf;

enum GameState { MenuState, InGameState, LevelCompleteState, GameOverState, NextStageState, ChallengeCompleteState};

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
	MyText m_TimeInfo;
	MyText m_CoinsInfo;
	//TextBox m_GamePause;
	//TextBox m_GameExit;

	//static
	MyClock m_Time; //total times
	int m_Level; //current levels

	//GUI functions
	void initVariables();
	void initWindow();
	void initFonts();
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
	const bool& getEndGame() const;


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
	//Functions
	
};
