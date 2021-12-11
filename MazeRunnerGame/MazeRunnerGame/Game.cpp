#include "Game.hpp"

//@DESCR: Initialize variables of Game
//@PARAM: None
//@RETURN: None
void Game::initVariables()
{
	this->m_EndGame = false;
	this->m_Points = 0;
}

//@DESCR: Initialize parameter of Game's screen
//@PARAM: None
//@RETURN: None
void Game::initWindow()
{
	this->m_VideoMode = sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT);
	this->m_pWindow = new sf::RenderWindow(this->m_VideoMode, NAME_GAME, sf::Style::Close | sf::Style::Titlebar);
	this->m_pWindow->setFramerateLimit(60);

	// Turn off key repetition
	//this->m_pWindow->setKeyRepeatEnabled(0);
}

//@DESCR: Initialze settings of fonts
//@PARAM: None
//@RETURN: None
void Game::initFonts()
{
	/*if (!this->m_Font.loadFromFile("Fonts/PixellettersFull.ttf"))
	{
		std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD PixellettersFull.ttf" << "\n";
	}*/
}

//@DESCR: Initialize settings and parameters of text
//@PARAM: None
//@RETURN: None
void Game::initText()
{
	//Gui text init
	this->m_GuiText.setFont(this->m_Font);
	this->m_GuiText.setFillColor(sf::Color::White);
	this->m_GuiText.setCharacterSize(32);

	//End game text
	this->m_EndGameText.setFont(this->m_Font);
	this->m_EndGameText.setFillColor(sf::Color::Red);
	this->m_EndGameText.setCharacterSize(60);
	this->m_EndGameText.setPosition(sf::Vector2f(20, 100));
	this->m_EndGameText.setString("YOU ARE DEAD, EXIT THE GAME!");
}

//@DESCR: Initialize settings of m_Map
//@PARAM: None
//@RETURN: None
void Game::initMap() {
	this->m_Map.creatGameMap();
	this->m_Map.setdisplayMap();
	//Set location of m_Player
	this->m_Player.setLocaStart(this->m_Map.getColStart(), this->m_Map.getRowStart());
}

//@DESCR: Constructor of Game
//@PARAM: None
//@RETURN: None
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
	this->initMap();
}

//@DESCR: Destructor of Game
//@PARAM: None
//@RETURN: None
Game::~Game()
{
	delete this->m_pWindow;
}

//@DESCR: Check whether the Game is ended
//@PARAM: None
//@RETURN: the state of the game: FALSE - running | TRUE - ended
const bool& Game::getEndGame() const
{
	return this->m_EndGame;
}

//@DESCR: Check whether the Game is running
//@PARAM: None
//@RETURN: the state of the game: FALSE - ended | TRUE - running
const bool Game::running() const
{
	return this->m_pWindow->isOpen() /*&& this->m_EndGame == false*/;
}

//@DESCR: Get events from user
//@PARAM: None
//@RETURN: None
void Game::pollEvents()
{
	if (m_pWindow->waitEvent(m_Event)) {
		while (this->m_pWindow->pollEvent(this->m_Event))
		{
			switch (this->m_Event.type)
			{
			case sf::Event::Closed:
				this->m_pWindow->close();
				break;
			case sf::Event::KeyPressed:
				if (this->m_Event.key.code == sf::Keyboard::Escape)
					this->m_pWindow->close();
				break;
			}
		}
	}
}

//@DESCR: Update m_Player's changes, including position
//@PARAM: None
//@RETURN: None
void Game::updatePlayer()
{
	this->m_Player.update(m_pWindow, m_Event.key.code);
}


//@DESCR: Update GUI's changes
//@PARAM: None
//@RETURN: None
void Game::updateGui()
{

}

//@DESCR: Update all changes
//@PARAM: None
//@RETURN: None
void Game::update()
{
	this->pollEvents();

	if (this->m_EndGame == false)
	{
		if (m_Event.type == sf::Event::KeyPressed)
			this->updatePlayer();
		this->updateGui();
	}
}

//@DESCR: Render GUi
//@PARAM: m_pWindow to render GUi on
//@RETURN: None
void Game::renderGui(sf::RenderTarget* target)
{
	target->draw(this->m_GuiText);
}

//@DESCR: Render Game's state
//@PARAM: None
//@RETURN: None
void Game::render()
{
	this->m_pWindow->clear();

	this->m_Map.drawMap(this->m_pWindow, this->m_Player);
	
	//Render m_Player's state
	this->m_Player.render(this->m_pWindow);
	
	//Render Gui
	this->renderGui(this->m_pWindow);

	//Render end text
	if (this->m_EndGame == true)
		this->m_pWindow->draw(this->m_EndGameText);

	this->m_pWindow->display();
}
