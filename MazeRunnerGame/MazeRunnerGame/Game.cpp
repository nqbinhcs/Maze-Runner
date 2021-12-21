#include "Game.hpp"


MyLevel level[7] = { MyLevel{3, 3} , MyLevel{ 5, 5 }, MyLevel{ 9, 9 }, MyLevel{ 15, 15 }, MyLevel{ 20, 20 }, MyLevel{ 23, 23 }, MyLevel{ 30, 30 } };


//@DESCR: Initialize variables of Game
//@PARAM: None
//@RETURN: None
void Game::initVariables()
{
	//Init state of game is Menu state
	m_State = MenuState;
	this->m_EndGame = false;
	this->m_Time.setCDTime(3603);
	this->m_Time.start();
	this->m_Level = 0;

	
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
	this->m_pMenu = std::shared_ptr<Menu>(new Menu(SCREEN_WIDTH, SCREEN_HEIGHT));
	this->m_pModeGame = std::shared_ptr<ModeGame>(new ModeGame(SCREEN_WIDTH, SCREEN_HEIGHT));
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

	initTitle();
	initLevelInfo();
	initTimeInfo();
	initCoinsInfo();
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

//@DESCR: Changing from "current" level to "current + 1" level
//@PARAM: None
//@RETURN: None
void Game::nextLevel()
{
	if (m_Level >= MAX_LEVEL - 1) 
		return;
	m_Level++;
	std::cout << m_Level << '\n';
	curMaze->SetMaze(level[m_Level].x, level[m_Level].y, m_Level + 1, *m_pWindow);
	m_Player->setPosStart(curMaze->startPos);
	m_Player->setWidthPlayer(curMaze->getWidthRoom());
	m_Player->setHeightPlayer(curMaze->getHeightRoom());
	m_Player->updateDirecPlayer(0);
}

//@DESCR: Changing from "current" level to new level
//@PARAM: new level
//@RETURN: None
void Game::setLevel(int _level)
{
	m_Level = _level;
	curMaze->SetMaze(level[m_Level].x, level[m_Level].y, m_Level + 1, *m_pWindow);
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
	//this->initMap();
	curMaze = std::shared_ptr<Maze>(new Maze(MAZE_X, MAZE_Y,
		OFFSET_MAZE_X, OFFSET_MAZE_Y, SCREEN_MAZE_WIDTH,
		SCREEN_MAZE_HEIGHT, 1, false, *m_pWindow));
	m_Player = std::shared_ptr<Player>(new Player(curMaze->startPos, OFFSET_MAZE_X, OFFSET_MAZE_Y, curMaze->getWidthRoom(), curMaze->getHeightRoom()));
	//reset level to 0
	setLevel(0);
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
	sf::Event temp;
	//if (m_pWindow->waitEvent(m_Event)) 
	{
		while (this->m_pWindow->pollEvent(temp))
		{
			std::cout << "LEVEL COMPLETE!\n";
			switch (temp.type)
			{
			case sf::Event::Closed:
				this->m_pWindow->close();
				break;



			if (m_State == LevelCompleteState)
			{
				
			case sf::Event::KeyPressed:
				if (temp.key.code == sf::Keyboard::Escape)
					this->m_pWindow->close();
				//For fun
				if (temp.key.code == sf::Keyboard::Enter)
					this->m_State = LevelCompleteState;
				break;
			}
			}
			
		}
	}
	this->m_Event = temp;
}

//@DESCR: Update m_Player's changes, including position
//@PARAM: None
//@RETURN: None
void Game::updatePlayer()
{
	this->m_Player->update(m_pWindow, m_Event.key.code, curMaze);
}


//@DESCR: Update GUI's changes
//@PARAM: None
//@RETURN: None
void Game::updateGui()
{
	stringstream writer;
	//Level Info
}

//@DESCR: Update all changes
//@PARAM: None
//@RETURN: None
void Game::update()
{
	this->pollEvents();

	//Testing code - Always Nextstage


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
	m_pWindow->clear(sf::Color(128,128,128));
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

	m_Player->render(*m_pWindow);

	// Info display
	//updateLevel();
	updateTimeInfo();
	updateCoinsInfo();

	m_Title.drawMyText(m_pWindow);
	//m_LevelInfo.drawMyText(m_pWindow);

	for (int i(0); i < 2; i++) {
		m_CoinsInfo[i].drawMyText(m_pWindow);
		m_TimeInfo[i].drawMyText(m_pWindow);
	}

	//Press Enter to next maze

	// - - - - - - Begin Testing: Next maze - - - - - - 

	if (m_State == NextStageState)
	{
		delay(0.7);
		nextLevel();
		m_State = GameOverState;
	}

	// Update level
	updateLevel();
	m_LevelInfo.drawMyText(m_pWindow);

	if (m_State == LevelCompleteState || m_Player->getPosition() == curMaze->finalPos)
	{
		
		renderDisplayStates(NextStageState);
		m_State = NextStageState;
	}
	
	// - - - - - -  End Testing - - - - - -

	this->m_pWindow->display();
}

//@DESCR: Render Game's particular state such as: GameOver, NextStage, LevelComplete
//@PARAM: None
//@RETURN: Non
void Game::renderDisplayStates(GameState state)
{
	if (state == LevelCompleteState)
	{
		m_pLevelComplete->draw(*m_pWindow, 0);
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


void Game::initTitle() {
	m_Title.setBox(sf::Vector2f(OFFSET_TITLE_X, OFFSET_TITLE_Y),
		sf::Vector2f(SCREEN_TITLE_WIDTH, SCREEN_TITLE_HEIGHT),
		sf::Color::Black, sf::Color::Transparent);

	m_Title.setText("MAZE RUNNER", FONT_GAME, 90, sf::Text::Bold, sf::Color::White);
	m_Title.setCharacterSpacing(1.5);
	m_Title.alignTextCenter();
	m_Title.alignTextMiddle();
}

void Game::initLevelInfo() {
	stringstream writer("");

	writer << "LEVEL " << m_Level + 1;

	m_LevelInfo.setBox(sf::Vector2f(OFFSET_LEVEL_X, OFFSET_LEVEL_Y),
		sf::Vector2f(SCREEN_INFO_WIDTH, SCREEN_INFO_HEIGHT),
		sf::Color::Black, sf::Color::White);
	m_LevelInfo.setBoxOutlineThickness(5);

	m_LevelInfo.setText(writer.str(), FONT_GAME, 40, sf::Text::Bold, sf::Color::White);
	m_LevelInfo.setCharacterSpacing(1.5);
	m_LevelInfo.alignTextCenter();
	m_LevelInfo.alignTextMiddle();
}

void Game::initTimeInfo() {	
	// Time title
	m_TimeInfo[0].setBox(sf::Vector2f(OFFSET_TIME_X, OFFSET_TIME_Y), 
		sf::Vector2f(SCREEN_INFO_WIDTH / 2, SCREEN_INFO_HEIGHT / 2),
		sf::Color::Black, sf::Color::White);
	m_TimeInfo[0].setBoxOutlineThickness(5);

	m_TimeInfo[0].setText("TIME", FONT_GAME, 30, sf::Text::Bold, sf::Color::White);
	m_TimeInfo[0].setCharacterSpacing(1.5);
	m_TimeInfo[0].alignTextCenter();
	m_TimeInfo[0].alignTextMiddle();

	// Time info
	stringstream writer("");

	m_TimeInfo[1].setBox(sf::Vector2f(OFFSET_TIME_INFO_X, OFFSET_TIME_INFO_Y),
		sf::Vector2f(SCREEN_INFO_WIDTH / 2, SCREEN_INFO_HEIGHT / 2),
		sf::Color::Black, sf::Color::White);
	m_TimeInfo[1].setBoxOutlineThickness(5);

	writer << m_Time.getCDTime();

	m_TimeInfo[1].setText(writer.str(), FONT_GAME, 30, sf::Text::Bold, sf::Color::White);
	m_TimeInfo[1].setCharacterSpacing(1.5);
	m_TimeInfo[1].alignTextCenter();
	m_TimeInfo[1].alignTextMiddle();
}

void Game::initCoinsInfo() {
	// Coins title
	m_CoinsInfo[0].setBox(sf::Vector2f(OFFSET_COINS_X, OFFSET_COINS_Y),
		sf::Vector2f(SCREEN_INFO_WIDTH / 2, SCREEN_INFO_HEIGHT / 2),
		sf::Color::Black, sf::Color::White);
	m_CoinsInfo[0].setBoxOutlineThickness(5);

	m_CoinsInfo[0].setText("COINS", FONT_GAME, 30, sf::Text::Bold, sf::Color::White);
	m_CoinsInfo[0].setCharacterSpacing(1.5);
	m_CoinsInfo[0].alignTextCenter();
	m_CoinsInfo[0].alignTextMiddle();

	// Coins info
	stringstream writer("");
	m_CoinsInfo[1].setBox(sf::Vector2f(OFFSET_COINS_INFO_X, OFFSET_COINS_INFO_Y),
		sf::Vector2f(SCREEN_INFO_WIDTH / 2, SCREEN_INFO_HEIGHT / 2),
		sf::Color::Black, sf::Color::White);
	m_CoinsInfo[1].setBoxOutlineThickness(5);

	writer << m_Points;

	m_CoinsInfo[1].setText(writer.str(), FONT_GAME, 30, sf::Text::Bold, sf::Color::White);
	m_CoinsInfo[1].setCharacterSpacing(1.5);
	m_CoinsInfo[1].alignTextCenter();
	m_CoinsInfo[1].alignTextMiddle();
}

void Game::updateTimeInfo() {
	m_TimeInfo[1].setContent(m_Time.getCDTime());
	m_TimeInfo[1].alignTextCenter();
	m_TimeInfo[1].alignTextMiddle();
}

void Game::updateCoinsInfo() {
	stringstream writer("");
	writer << m_Points;

	m_CoinsInfo[1].setContent(writer.str());
	m_CoinsInfo[1].alignTextCenter();
	m_CoinsInfo[1].alignTextMiddle();
}

void Game::updateLevel() {
	stringstream writer("");
	
	writer << "LEVEL " << m_Level + 1;

	m_LevelInfo.setContent(writer.str());
	m_LevelInfo.alignTextCenter();
	m_LevelInfo.alignTextMiddle();
}