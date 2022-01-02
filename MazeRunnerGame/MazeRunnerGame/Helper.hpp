#pragma once
#include "Maze.hpp"
#include "PathFinder.hpp"
#include "MazeAlgorithms.hpp"
#include "Clock.hpp"

#define PATH_START_COLOR 255,80,0
#define PATH_END_COLOR 255,160,100
#define PROGRESS_START_COLOR 0,5,255
#define PROGRESS_END_COLOR 0,255,255

#define NUMBER_COLOR 20

class MazeBot
{
public:
	bool isShowing = false;
	bool isFinished = false;
private:
	shared_ptr<PathFinder> m_pPathFinder;

	vector<shared_ptr<Room>> m_Path;
	vector<int> m_PathShower;

	vector<shared_ptr<Room>> m_Progress;
	vector<int> m_ProgressShower;

	MyClock m_Clock;

	int curRoom1 = 0;
	int curRoom2 = 0;
public:
	void start(int option, shared_ptr<Room> start, shared_ptr<Room> end);
	void end();

	void setPathFinder(int option);

	void showPath(sf::RenderTarget& window);
	void showProgress(sf::RenderTarget& window);
	void showInstruction(sf::RenderTarget& window);
	void showPathOnly(sf::RenderTarget& window);
};