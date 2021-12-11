
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

using namespace sf;
class Game
{
public:
	sf::RenderWindow* m_pWindow;
private:
	sf::VideoMode m_VideoMode;
	bool m_EndGame;
	sf::Event m_Event;

	Player m_Player;
	TileMap m_Map;
	int m_Points;

	sf::Font m_Font;
	sf::Text m_GuiText;
	sf::Text m_EndGameText;

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

	/*void spawnSwagBalls();
	const int randBallType() const;*/
	void updatePlayer();
	//void updateCollision();
	void updateGui();
	void update();

	void renderGui(sf::RenderTarget* target);
	void render();
};