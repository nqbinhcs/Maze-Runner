#include "Helper.hpp"

void MazeBot::start(int option, shared_ptr<Room> start, shared_ptr<Room> end)
{
	this->setPathFinder(option);

	m_Path.clear();
	m_Progress.clear();
	m_PathShower.clear();
	m_ProgressShower.clear();
	m_Path = m_pPathFinder->findPath(start, end, 0);
	m_Progress = m_pPathFinder->findPath(start, end, 1);
	m_PathShower.assign(m_Path.size(), 0);
	m_ProgressShower.assign(m_Progress.size(), 0);
	curRoom1 = curRoom2 = 0;

	this->m_Clock.start();

	isShowing = true;
	isFinished = false;
}

void MazeBot::end()
{
	isShowing = false;
	isFinished = false;
}

void MazeBot::setPathFinder(int option)
{
	switch (option)
	{
	case iBFS:
		m_pPathFinder = make_shared<BFS>();
		break;
	case iDFS:
		m_pPathFinder = make_shared<DFS>();
		break;
	case iAStar:
		m_pPathFinder = make_shared<AStar>();
	}
}

void MazeBot::showPath(sf::RenderTarget& window)
{
	//std::cout << "Path showing \n";
	sf::Color color[NUMBER_COLOR + 1];

	color[0] = sf::Color(PATH_START_COLOR);
	color[NUMBER_COLOR] = sf::Color(PATH_END_COLOR);

	int red = ((int)color[NUMBER_COLOR].r - (int)color[0].r) / NUMBER_COLOR;
	int green = ((int)color[NUMBER_COLOR].g - (int)color[0].g) / NUMBER_COLOR;
	int blue = ((int)color[NUMBER_COLOR].b - (int)color[0].b) / NUMBER_COLOR;

	for (int i(1); i < NUMBER_COLOR; i++)
	{
		color[i] = sf::Color(
			(int)color[0].r + red * i,
			(int)color[0].g + green * i,
			(int)color[0].b + blue * i);
	}

	int nRoom = m_Path.size();

	for (int i(0); i < curRoom2 + 1; i++)
	{
		sf::RectangleShape roomBackground;

		m_PathShower[i] = (m_PathShower[i] == NUMBER_COLOR ? NUMBER_COLOR : m_PathShower[i] + 1);
		roomBackground.setFillColor(color[m_PathShower[i]]);
		roomBackground.setSize(sf::Vector2f(m_Path[i]->getWidthRoom(), m_Path[i]->getHeightRoom()));
		roomBackground.setPosition(m_Path[i]->getPositionInScreen());

		window.draw(roomBackground);
	}

	curRoom2 = (curRoom2 == nRoom - 1 ? nRoom - 1 : curRoom2 + 1);
}

void MazeBot::showProgress(sf::RenderTarget& window)
{
	//std::cout << "Progress showing\n";
	sf::Color color[NUMBER_COLOR + 1];

	color[0] = sf::Color(PROGRESS_START_COLOR);
	color[NUMBER_COLOR] = sf::Color(PROGRESS_END_COLOR);

	int red = ((int)color[NUMBER_COLOR].r - (int)color[0].r) / NUMBER_COLOR;
	int green = ((int)color[NUMBER_COLOR].g - (int)color[0].g) / NUMBER_COLOR;
	int blue = ((int)color[NUMBER_COLOR].b - (int)color[0].b) / NUMBER_COLOR;

	for (int i(1); i < NUMBER_COLOR; i++)
	{
		color[i] = sf::Color(
			(int)color[0].r + red * i,
			(int)color[0].g + green * i,
			(int)color[0].b + blue * i);
	}

	int nRoom = m_Progress.size();

	for (int i(0); i < curRoom1 + 1; i++)
	{
		sf::RectangleShape roomBackground;

		m_ProgressShower[i] = (m_ProgressShower[i] == NUMBER_COLOR ? NUMBER_COLOR : m_ProgressShower[i] + 1);
		roomBackground.setFillColor(color[m_ProgressShower[i]]);
		roomBackground.setSize(sf::Vector2f(m_Progress[i]->getWidthRoom(), m_Progress[i]->getHeightRoom()));
		roomBackground.setPosition(m_Progress[i]->getPositionInScreen());

		window.draw(roomBackground);
	}

	curRoom1 = (nRoom - 1 < curRoom1 + 1 ? nRoom - 1 : curRoom1 + 1);
}

void MazeBot::showInstruction(sf::RenderTarget& window)
{
	showProgress(window);
	if (m_ProgressShower.back() == NUMBER_COLOR)
		showPath(window);
	if (m_ProgressShower.back() == NUMBER_COLOR &&
		m_PathShower.back() == NUMBER_COLOR)
		isFinished = true;
}