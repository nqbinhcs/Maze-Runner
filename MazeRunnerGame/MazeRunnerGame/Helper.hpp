#pragma once
#include "Maze.hpp"
#include "PathFinder.hpp"
#include "MazeAlgorithms.hpp"
#include "Clock.hpp"

#define DELTA_TIME 0.1
#define WAITING_TIME 1


class Helper
{
public:
	bool isHelping = false;
private:
	shared_ptr<PathFinder> m_pPathFinder;
	
	vector<shared_ptr<Room>> m_Path;
	vector<shared_ptr<Room>> m_Progress;
	
	MyClock m_Clock;

	bool m_ShownPath = false;
	bool m_ShownProgress = false;
	int m_Phase;
public:
	void help(int option, shared_ptr<Room> start, shared_ptr<Room> end);
	void setPathFinder(int option);
	void updateHelpStatus(bool status);

	void showPath(sf::RenderTarget& window);
	void showProgress(sf::RenderTarget& window);
	void showInstruction(sf::RenderTarget& window);
};


