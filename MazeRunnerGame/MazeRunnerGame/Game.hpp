
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

#include "Player.hpp"
#include "DefinedVariables.hpp"
#include "TileMap.h"
#include "Maze.hpp"
#include "GameOver.hpp"
#include "NextStage.hpp"
#include "LevelComplete.hpp"

using namespace sf;

enum GameState { MenuState, InGameState, LevelCompleteState, GameOverState, NextStageState};

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
	shared_ptr<GameOver> m_pGameOver;
	shared_ptr<NextStage> m_pNextStage;
	shared_ptr<LevelComplete> m_pLevelComplete;

	//In Game
	shared_ptr<Maze> curMaze;
	Player m_Player;
	int m_Points;

	//Gui
	sf::Font m_Font;
	sf::Text m_GuiText;
	sf::Text m_EndGameText;

	//stat
	int m_Time; //total times

	void initVariables();
	void initWindow();
	void initFonts();
	void initText();
	void initMap();

public:
	//Constructors and Destructors
	Game();
	~Game();

	//Accessors
	const bool& getEndGame() const;

	//Modifiers

	//Functions
	const bool running() const;
	void pollEvents();

	void updatePlayer();
	//void updateCollision();
	void updateGui();
	void update();

	void renderGui(sf::RenderTarget* target);
	void render();

	void renderDisplayStates(GameState);
};