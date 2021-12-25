#include "Helper.hpp"

void Helper::help(int option, shared_ptr<Room> start, shared_ptr<Room> end)
{
	this->setPathFinder(option);
	
	m_Path.clear();
	m_Progress.clear();
	m_Path = m_pPathFinder->findPath(start, end, 0);
	m_Progress = m_pPathFinder->findPath(start, end, 1);

	m_Phase = 0;
	m_ShownPath = false;
	m_ShownProgress = false;
	this->m_Clock.start();

	updateHelpStatus(true);
}

void Helper::setPathFinder(int option)
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

void Helper::updateHelpStatus(bool status)
{
	this->isHelping = status;
}

void Helper::showPath(sf::RenderTarget& window)
{
	uint32_t time = this->m_Clock.getRunningTimeInSec();
	int nRoom = m_Path.size();
	int nDisplayedRoom = (time * 1.0 / DELTA_TIME);

	if (this->m_ShownPath || nDisplayedRoom > nRoom)
	{
		nDisplayedRoom = nRoom;
		this->m_ShownPath = true;
	}

	for (int i(0); i < nDisplayedRoom; i++)
	{
		sf::RectangleShape roomBackground;
		roomBackground.setFillColor(sf::Color(255, 165, 0));
		roomBackground.setSize(sf::Vector2f(m_Path[i]->getWidthRoom(), m_Path[i]->getHeightRoom()));
		roomBackground.setPosition(m_Path[i]->getPosition());

		window.draw(roomBackground);
	}
}

void Helper::showProgress(sf::RenderTarget& window)
{
	uint32_t time = this->m_Clock.getRunningTimeInSec();
	int nRoom = m_Progress.size();
	int nDisplayedRoom = time * 1.0 / DELTA_TIME;

	if (this->m_ShownProgress || nDisplayedRoom > nRoom)
	{
		nDisplayedRoom = nRoom;
		this->m_ShownProgress = true;
	}

	for (int i(0); i < nDisplayedRoom; i++)
	{
		sf::Uint8 green = (nDisplayedRoom > nRoom ? 255 : 255 * nDisplayedRoom / nRoom);
		sf::RectangleShape roomBackground;
		roomBackground.setFillColor(sf::Color(0, green, 255));
		roomBackground.setSize(sf::Vector2f(m_Progress[i]->getWidthRoom(), m_Progress[i]->getHeightRoom()));
		roomBackground.setPosition(m_Progress[i]->getPosition());

		window.draw(roomBackground);
	}
}

void Helper::showInstruction(sf::RenderTarget& window)
{
	switch (m_Phase) 
	{
	case 0:
		this->showProgress(window);
		if (m_ShownProgress)
		{
			m_Phase++;
			m_Clock.start();
		}
		break;
	case 1:
		this->showProgress(window);
		this->showPath(window);
		if (m_ShownPath)
		{
			m_Phase++;
			m_Clock.start();
		}
		break;
	}
}