
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
//#include "SwagBall.h"

using namespace sf;
class Game
{
public:
	sf::RenderWindow* window;
private:
	sf::VideoMode videoMode;
	bool endGame;
	sf::Event sfmlEvent;

	Player player;
	TileMap map;
	int points;

	sf::Font font;
	sf::Text guiText;
	sf::Text endGameText;

	/*std::vector<SwagBall> swagBalls;
	float spawnTimerMax;
	float spawnTimer;
	int maxSwagBalls;*/

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