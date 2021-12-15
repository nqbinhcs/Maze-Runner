#include "Game.hpp"

//@DESCR: Initialize variables of Game
//@PARAM: None
//@RETURN: None
void Game::initVariables()
{
	this->m_EndGame = false;
	this->m_Time = 0;
}

//@DESCR: Initialize parameter of Game's screen
//@PARAM: None
//@RETURN: None
void Game::initWindow()
{
	this->m_VideoMode = sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT);
	this->m_pWindow = new sf::RenderWindow(this->m_VideoMode, NAME_GAME, sf::Style::Close | sf::Style::Titlebar);
	this->m_pWindow->setFramerateLimit(60);


	//init display
	this->m_pGameOver = std::shared_ptr<GameOver>(new GameOver());
	this->m_pNextStage = std::shared_ptr<NextStage>(new NextStage());
	this->m_pLevelComplete = std::shared_ptr<LevelComplete>(new LevelComplete());

	// Turn off key repetition
	//this->m_pWindow->setKeyRepeatEnabled(0);
}

//@DESCR: Initialze settings of fonts
//@PARAM: None
//@RETURN: None
void Game::initFonts()
{
	if (!this->m_Font.loadFromFile("Fonts/TitleFont.ttf"))
	{
		std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD TitleFont.ttf" << "\n";
	}
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

#define SCREEN_TITLE_WIDTH	(SCREEN_WIDTH - 2 * SPACE)
#define SCREEN_TITLE_HEIGHT	(OFFSET_MAZE_Y - 2 * SPACE) 
#define OFFSET_TITLE_X		SPACE
#define OFFSET_TITLE_Y		SPACE

#define NUMBER_OF_BOXES 3
#define SCREEN_INFO_HEIGHT (SCREEN_MAZE_HEIGHT / NUMBER_OF_BOXES)
#define SCREEN_INFO_WIDTH (SCREEN_WIDTH - SCREEN_MAZE_WIDTH - 2 * SPACE)	

#define OFFSET_LEVEL_X (OFFSET_MAZE_X + SCREEN_MAZE_WIDTH + 5)
#define OFFSET_LEVEL_Y OFFSET_MAZE_Y

#define OFFSET_TIME_X OFFSET_LEVEL_X
#define OFFSET_TIME_Y (OFFSET_LEVEL_Y + SCREEN_INFO_HEIGHT)

#define OFFSET_COINS_X OFFSET_LEVEL_X
#define OFFSET_COINS_Y (OFFSET_TIME_Y + SCREEN_INFO_HEIGHT)

#define OFFSET_PAUSE_X OFFSET_LEVEL_X
#define OFFSET_PAUSE_Y (OFFSET_COINS_Y + SCREEN_INFO_HEIGHT)

#define OFFSET_EXIT_X OFFSET_LEVEL_X
#define OFFSET_EXIT_Y (OFFSET_PAUSE_Y + SCREEN_INFO_HEIGHT)

void Game::initTextBox()
{
	sf::FloatRect textBound;
	stringstream writer;
	
	// Init Game Title
	m_Title.m_Rect.setPosition(sf::Vector2f(OFFSET_TITLE_X, OFFSET_TITLE_Y));
	m_Title.m_Rect.setSize(sf::Vector2f(SCREEN_TITLE_WIDTH, SCREEN_TITLE_HEIGHT));
	m_Title.m_Rect.setFillColor(sf::Color::Black);
	//m_Title.m_Rect.setOutlineColor(Color(sf::Color::White));
	//m_Title.m_Rect.setOutlineThickness(3);

	m_Title.m_Text.setFont(this->m_Font);
	m_Title.m_Text.setLetterSpacing(1.5);
	m_Title.m_Text.setStyle(sf::Text::Bold);
	m_Title.m_Text.setFillColor(sf::Color::White);
	m_Title.m_Text.setCharacterSize(90);
	m_Title.m_Text.setString("MAZE RUNNER");
	textBound = m_Title.m_Text.getLocalBounds();
	m_Title.m_Text.setOrigin(sf::Vector2f(textBound.left + textBound.width / 2.f, textBound.top + textBound.height / 2.f));
	m_Title.m_Text.setPosition(sf::Vector2f(SCREEN_TITLE_WIDTH / 2.f, SCREEN_TITLE_HEIGHT / 2.f));
	

	// Init Level Info
	m_LevelInfo.m_Rect.setPosition(sf::Vector2f(OFFSET_LEVEL_X, OFFSET_LEVEL_Y));
	m_LevelInfo.m_Rect.setSize(sf::Vector2f(SCREEN_INFO_WIDTH, SCREEN_INFO_HEIGHT));
	m_LevelInfo.m_Rect.setFillColor(sf::Color::Black);
	m_LevelInfo.m_Rect.setOutlineColor(Color(sf::Color::White));
	m_LevelInfo.m_Rect.setOutlineThickness(5);

	writer.str(std::string());
	writer << "LEVEL " << 1;

	m_LevelInfo.m_Text.setFont(this->m_Font);
	m_LevelInfo.m_Text.setLetterSpacing(1.5);
	m_LevelInfo.m_Text.setFillColor(sf::Color::White);
	m_LevelInfo.m_Text.setCharacterSize(40);
	m_LevelInfo.m_Text.setString(writer.str());
	textBound = m_LevelInfo.m_Text.getLocalBounds();
	m_LevelInfo.m_Text.setOrigin(sf::Vector2f(textBound.left + textBound.width / 2.f, textBound.top + textBound.height / 2.f));
	m_LevelInfo.m_Text.setPosition(sf::Vector2f(OFFSET_LEVEL_X + SCREEN_INFO_WIDTH / 2.f, 
												OFFSET_LEVEL_Y + SCREEN_INFO_HEIGHT / 2.f));

	// Init Time Info
	m_TimeInfo.m_Rect.setPosition(sf::Vector2f(OFFSET_TIME_X, OFFSET_TIME_Y));
	m_TimeInfo.m_Rect.setSize(sf::Vector2f(SCREEN_INFO_WIDTH, SCREEN_INFO_HEIGHT));
	m_TimeInfo.m_Rect.setOutlineColor(Color(sf::Color::White));
	m_TimeInfo.m_Rect.setOutlineThickness(5);
	m_TimeInfo.m_Rect.setFillColor(sf::Color::Black);

	writer.str(std::string());
	std::time_t t = std::time(0);
	std::tm* now = std::localtime(&t);
	writer << "TIME " << now->tm_hour << "." << now->tm_min << "." << now->tm_sec;

	m_TimeInfo.m_Text.setFont(this->m_Font);
	m_TimeInfo.m_Text.setLetterSpacing(1.5);
	m_TimeInfo.m_Text.setFillColor(sf::Color::White);
	m_TimeInfo.m_Text.setCharacterSize(30);
	m_TimeInfo.m_Text.setString(writer.str());
	textBound = m_TimeInfo.m_Text.getLocalBounds();
	m_TimeInfo.m_Text.setOrigin(sf::Vector2f(textBound.left + textBound.width / 2.f, textBound.top + textBound.height / 2.f));
	m_TimeInfo.m_Text.setPosition(sf::Vector2f(OFFSET_TIME_X + SCREEN_INFO_WIDTH / 2.f,
		OFFSET_TIME_Y + SCREEN_INFO_HEIGHT / 2.f));

	// Init Coins Info
	m_CoinsInfo.m_Rect.setPosition(sf::Vector2f(OFFSET_COINS_X, OFFSET_COINS_Y));
	m_CoinsInfo.m_Rect.setSize(sf::Vector2f(SCREEN_INFO_WIDTH, SCREEN_INFO_HEIGHT));
	m_CoinsInfo.m_Rect.setOutlineColor(Color(sf::Color::White));
	m_CoinsInfo.m_Rect.setOutlineThickness(5);
	m_CoinsInfo.m_Rect.setFillColor(sf::Color::Black);

	writer.str(std::string());
	writer << "COINS " << 100;

	m_CoinsInfo.m_Text.setFont(this->m_Font);
	m_CoinsInfo.m_Text.setLetterSpacing(1.5);
	m_CoinsInfo.m_Text.setFillColor(sf::Color::White);
	m_CoinsInfo.m_Text.setCharacterSize(30);
	m_CoinsInfo.m_Text.setString(writer.str());
	textBound = m_CoinsInfo.m_Text.getLocalBounds();
	m_CoinsInfo.m_Text.setOrigin(sf::Vector2f(textBound.left + textBound.width / 2.f, textBound.top + textBound.height / 2.f));
	m_CoinsInfo.m_Text.setPosition(sf::Vector2f(OFFSET_COINS_X + SCREEN_INFO_WIDTH / 2.f,
		OFFSET_COINS_Y + SCREEN_INFO_HEIGHT / 2.f));

}

//@DESCR: Initialize settings of m_Map
//@PARAM: None
//@RETURN: None
void Game::initMap() {
	//this->m_Map.creatGameMap();
	//this->m_Map.setdisplayMap();
	//Set location of m_Player
	//this->m_Player.setLocaStart(this->m_Map.getColStart(), this->m_Map.getRowStart());
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
	this->initTextBox();
	//this->initMap();
	curMaze = std::shared_ptr<Maze>(new Maze(MAZE_X, MAZE_Y,
		OFFSET_MAZE_X, OFFSET_MAZE_Y, SCREEN_MAZE_WIDTH,
		SCREEN_MAZE_HEIGHT, 1, false, *m_pWindow));
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
//**************************************NEED HELP**************************************
//@BUG: waitEvent can't catch CLOSE event
void Game::pollEvents()
{
	//if (m_pWindow->waitEvent(m_Event)) 
	{
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
	m_pWindow->clear(sf::Color(0,0,0));
	//this->m_pWindow->clear();

	//this->m_Map.drawMap(this->m_pWindow, this->m_Player);
	
	//Render m_Player's state
	//this->m_Player.render(this->m_pWindow);
	
	//Render Gui
	this->renderGui(this->m_pWindow);

	//Render end text
	if (this->m_EndGame == true)
		this->m_pWindow->draw(this->m_EndGameText);
	
	
	//Use it, command:
	//Game.cpp: 173, 176, 73, (58 to 61), 
	//Game.hpp: 32

	//Render Maze
	sf::RectangleShape mazeBound;
	mazeBound.setPosition(sf::Vector2f(OFFSET_MAZE_X, OFFSET_MAZE_Y));
	mazeBound.setSize(sf::Vector2f(SCREEN_MAZE_WIDTH, SCREEN_MAZE_HEIGHT));
	mazeBound.setOutlineColor(Color(sf::Color::White));
	mazeBound.setOutlineThickness(5);

	this->m_pWindow->draw(mazeBound);

	curMaze->AddMazeRoomsToRenderer(*m_pWindow);

	//Render State Screen -- For testing purposes, you should uncomment individual line to see clearly
	//renderDisplayStates(GameOverState);
	//renderDisplayStates(NextStageState);
	//renderDisplayStates(LevelCompleteState);

	this->m_pWindow->draw(this->m_Title.m_Rect);
	this->m_pWindow->draw(this->m_Title.m_Text);

	this->m_pWindow->draw(this->m_LevelInfo.m_Rect);
	this->m_pWindow->draw(this->m_LevelInfo.m_Text);

	this->m_pWindow->draw(this->m_TimeInfo.m_Rect);
	this->m_pWindow->draw(this->m_TimeInfo.m_Text);

	this->m_pWindow->draw(this->m_CoinsInfo.m_Rect);
	this->m_pWindow->draw(this->m_CoinsInfo.m_Text);

	this->m_pWindow->display();
}

//@DESCR: Render Game's particular state such as: GameOver, NextStage, LevelComplete
//@PARAM: None
//@RETURN: Non
void Game::renderDisplayStates(GameState state)
{
	if (state == LevelCompleteState)
	{
		m_pLevelComplete->draw(*m_pWindow, m_Time);
		return;
	}

	if (state == GameOverState)
	{
		m_pGameOver->draw(*m_pWindow);
		return;
	}

	if (state == NextStageState)
	{
		m_pNextStage->draw(*m_pWindow);
		return;
	}
}

