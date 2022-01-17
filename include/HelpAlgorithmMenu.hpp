#pragma once
#include "Display.hpp"
#include "Button.hpp"
#include <string>

class HelpAlgorithmMenu :public Display
{
private:
	std::vector<Button> algos;
	Button run; //For running algorithm
	int choose;
	bool runAlgo;

public:
	HelpAlgorithmMenu();
	virtual ~HelpAlgorithmMenu();

public:
	int getOptionAlgo(); //0: Astar, 1: BFS, 2: DFS
	bool isRun();
	bool isExit(sf::RenderWindow* window);

public:
	bool pollEvent(sf::RenderWindow* window);
	virtual void draw(sf::RenderWindow& window);
};
