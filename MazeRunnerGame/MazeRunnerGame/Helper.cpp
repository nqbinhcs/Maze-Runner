#include "Helper.hpp"

void Helper::help(int option, shared_ptr<Room> start, shared_ptr<Room> end)
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
	/*if (m_Path.size() == 0) return;
	string arrowImg[] = {"Images/LeftArrow.png", "Images/RightArrow.png", "Images/UpArrow.png", "Images/DownArrow.png"};
	sf::Texture arrowTexture[4];
	sf::Sprite arrow[4];
	
	for (int i(0); i < 4; i++) {
		arrowTexture[i].loadFromFile(arrowImg[i]);

		sf::Vector2f scale = sf::Vector2f(0.5f * m_Path[0]->getWidthRoom() / arrowTexture[i].getSize().x, 
			0.5f * m_Path[0]->getHeightRoom() / arrowTexture[i].getSize().y);
		arrow[i].setTexture(arrowTexture[i]);
		arrow[i].setScale(scale);
	}
	*/

	int red(255), green(80), blue(0);
	sf::Color color[21];
	
	for (int i(0); i < 21; i++)
	{
		color[i] = sf::Color(red, green + 4 * i, blue + 5 * i);
	}

	uint32_t time = this->m_Clock.getRunningTimeInSec();
	int nRoom = m_Path.size();
	//int nDisplayedRoom = (time * 1.0 / DELTA_TIME);

	if (this->m_ShownPath || (curRoom2 + 1 == nRoom && m_PathShower[nRoom - 2] == 20))
	{
		this->m_ShownPath = true;
	}

	for (int i(0); i < curRoom2 + 1; i++)
	{
		if (i == nRoom - 1 || i == 0) continue;
		
		m_PathShower[i] = (m_PathShower[i] == 20? 20 : m_PathShower[i] + 1);
		/*sf::Sprite* pArrow = arrow;
		if (m_Path[i]->roomPos.getX() > m_Path[i + 1]->roomPos.getX())
			pArrow = &arrow[0];
		else if (m_Path[i]->roomPos.getX() < m_Path[i + 1]->roomPos.getX())
			pArrow = &arrow[1];
		else if (m_Path[i]->roomPos.getY() > m_Path[i + 1]->roomPos.getY())
			pArrow = &arrow[2];
		else if (m_Path[i]->roomPos.getY() < m_Path[i + 1]->roomPos.getY())
			pArrow = &arrow[3];

		pArrow->setPosition(sf::Vector2f(m_Path[i]->getPosition().x + m_Path[i]->getWidthRoom() * 0.5f,
			m_Path[i]->getPosition().y + m_Path[i]->getHeightRoom() * 0.5f));
		
		window.draw(*pArrow);	
		//*/
		
		sf::RectangleShape roomBackground;
		roomBackground.setFillColor(color[m_PathShower[i]]);
		roomBackground.setSize(sf::Vector2f(m_Path[i]->getWidthRoom(), m_Path[i]->getHeightRoom()));
		roomBackground.setPosition(m_Path[i]->getPosition());

		window.draw(roomBackground);

		
	}

	curRoom2 = (curRoom2 == nRoom - 1 ? nRoom - 1 : curRoom2 + 1);
}

void Helper::showProgress(sf::RenderTarget& window)
{
	uint32_t time = this->m_Clock.getRunningTimeInSec();
	int nRoom = m_Progress.size();
	//int nDisplayedRoom = time * 1.0 / DELTA_TIME;

	if (this->m_ShownProgress || curRoom1 + 1 == nRoom)
	{
		this->m_ShownProgress = true;
	}

	for (int i(0); i < curRoom1 + 1; i++)
	{
		sf::Uint8 green = (i == curRoom1 ? 0 : 255 );
		sf::RectangleShape roomBackground;
		roomBackground.setFillColor(sf::Color(0, green, 255));
		roomBackground.setSize(sf::Vector2f(m_Progress[i]->getWidthRoom(), m_Progress[i]->getHeightRoom()));
		roomBackground.setPosition(m_Progress[i]->getPosition());

		window.draw(roomBackground);
	}

	curRoom1 = min(nRoom - 1, curRoom1 + 1);
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