#include "Game.hpp"


MyLevel level[7] = { MyLevel{3, 3} , MyLevel{ 5, 5 }, MyLevel{ 9, 9 }, MyLevel{ 15, 15 }, MyLevel{ 20, 20 }, MyLevel{ 23, 23 }, MyLevel{ 30, 30 } };
std::shared_ptr<LevelMaze> Game::levelMaze = NULL;
int Game::timeCycle = 0;

//@DESCR: Initialize variables of Game
//@PARAM: None
//@RETURN: None
void Game::initVariables()
{
	m_State = MenuState; //Obviously, we always in MenuState when entering game
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
	//Init window
	this->m_VideoMode = sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT);
	this->m_pWindow = new sf::RenderWindow(this->m_VideoMode, NAME_GAME, sf::Style::Close | sf::Style::Titlebar);
	this->m_pWindow->setFramerateLimit(60);

	//Init displays
	this->m_pMenu = std::shared_ptr<Menu>(new Menu(SCREEN_WIDTH, SCREEN_HEIGHT));
	this->m_pModeGame = std::shared_ptr<ModeGame>(new ModeGame(SCREEN_WIDTH, SCREEN_HEIGHT));
	this->m_pGameOver = std::shared_ptr<GameOver>(new GameOver(SCREEN_WIDTH, SCREEN_HEIGHT));
	this->m_pNextStage = std::shared_ptr<NextStage>(new NextStage());
	this->m_pHelpMenu = std::shared_ptr<HelpAlgorithmMenu>(new HelpAlgorithmMenu());
	this->m_pLevelComplete = std::shared_ptr<LevelComplete>(new LevelComplete());

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


//@DESCR: Initialize settings and parameters of buttons
//@PARAM: None
//@RETURN: None
void Game::initButtons()
{
	m_Help.setButton(sf::Vector2f(OFFSET_HELP_X, OFFSET_HELP_Y), sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
		sf::Color::Black, sf::Color::Transparent,
		"Help", FONT_GAME, 20, sf::Text::Style::Bold, sf::Color::White, "");

	m_RestartGame.setButton(sf::Vector2f(OFFSET_RESTART_X, OFFSET_RESTART_Y), sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
		sf::Color::Black, sf::Color::Transparent,
		"Restart", FONT_GAME, 20, sf::Text::Style::Bold, sf::Color::White, "");

	m_ReturnMenu.setButton(sf::Vector2f(OFFSET_RETURN_MENU_X, OFFSET_RETURN_MENU_Y), sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
		sf::Color::Black, sf::Color::Transparent,
		"Menu", FONT_GAME, 20, sf::Text::Style::Bold, sf::Color::White, "");
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


//@DESCR: Changing from "current" level to "current + 1" level
//@PARAM: None
//@RETURN: None
void Game::nextLevel(bool check)
{
	if (m_Level >= MAX_LEVEL - 1)
		return;
	m_Level++;
	setLevel(m_Level, check);
}


//@DESCR: Changing from "current" level to new level
//@PARAM: new level
//@RETURN: None
void Game::setLevel(int _level, bool check)
{
	m_Level = _level;
	curMaze->UpdateMaze(check);

	m_Player->setPosition(curMaze->getStartPos());
	m_Player->setSize(curMaze->getWidthRoom(), curMaze->getHeightRoom());
	m_Player->updateDirecPlayer(0);
	m_Player->setLose(false);

	m_Player->updateDirecPlayer(0);
}


//@DESCR: Constructor of Game
//@PARAM: None
//@RETURN: None
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initButtons();
	this->initText();
	//Choose easy, medium or hard.
	levelMaze = std::shared_ptr<LevelMaze>(new HardLevelMaze());
	curMaze = levelMaze->OrderLevelMaze();
	m_Player = std::shared_ptr<Player>(new Player(curMaze->getStartPos(), OFFSET_MAZE_X, OFFSET_MAZE_Y, curMaze->getWidthRoom(), curMaze->getHeightRoom()));
	setLevel(0, true); //Level 0 when entering game
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
bool Game::getEndGame()
{
	this->m_EndGame = m_Time.isOver();
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
	sf::Event temp;
	
	//if (m_pWindow->waitEvent(m_Event)) 
	{
		while (this->m_pWindow->pollEvent(temp))
		{
			switch (temp.type)
			{
			case sf::Event::Closed:
				this->m_pWindow->close();
				break;
				//------------------CLICK EVENT------------------
			case sf::Event::MouseButtonPressed:
				if (m_State == InGameState)
				{
					if (m_Help.isClickV1(m_pWindow))
					{
						m_Help.makeChosen();
					}

					if (m_ReturnMenu.isClickV1(m_pWindow))
					{
						m_ReturnMenu.makeChosen();
					}

					if (m_RestartGame.isClickV1(m_pWindow))
					{
						m_RestartGame.makeChosen();
					}

					break;
				}
				if (m_State == InHelpState) //Choosing Algorithm
				{
					if (m_pHelpMenu->isExit(m_pWindow)) //Check exit
					{
						//back to normal
						m_State = InGameState;
						m_Help.makeNormal();
						m_RestartGame.makeNormal();
						m_ReturnMenu.makeNormal();
					}
					else
						m_pHelpMenu->pollEvent(m_pWindow); //Choose Algorithms
					break;
				}
				break;

				//------------------BUTTON EVENT------------------
			case sf::Event::KeyPressed:
				if (temp.key.code == sf::Keyboard::Escape)
					this->m_pWindow->close();

				//Menu
				if (m_State == MenuState) //Check if we are in MenuState
				{
					
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					{
						m_pMenu->moveUp();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					{
						m_pMenu->moveDown();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
					{
						cout << "Enter press!\n";
						switch (m_pMenu->GetPressedItem())
						{
						case 0: //"NEW GAME" option

							//Rendering select mode and Getting the difficulty of the game
							m_pModeGame->runModeGame(*m_pWindow);

							//For getting the difficulty of the game, use method m_pModeGmae  "int m_pModeGame->GetPressedItem()"

							//Because of entering new game, so current game state is InGameState
							m_State = InGameState;

							break;

						case 1: //"CONTINUE" option
					
							break;

						case 2: //"HIGH SCORE" option
							
							break;

						case 3: //"HELP" option

							break;

						case 4: //"EXIT" option
	
							break;
						}
					}
					break;
				}

				//Difficulty Complete
				if (m_State == DifficultyCompleteState)
				{
					//Press Enter to exit
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
					{
						//Reset all Game
						resetGame();
						m_State = MenuState;
					}
					break;
				}

				//Gameover
				if (m_State == GameOverState)
				{
					//Press Enter to exit
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
					{
						//Reset all Game
						resetGame();
						m_State = MenuState;
					}
					break;
				}

				
				//In Game
				if (m_State == InGameState)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
					{
						m_State = LevelCompleteState;
					}
					break;
				}
				break;

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


	if (this->m_EndGame == false && m_State == InGameState)
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
	
	
	// -----------------------------If in MenuState , skip all these below-----------------------------
	if (m_State == MenuState) {
		renderDisplayStates(m_State);
		this->m_pWindow->display();
		return;
	}


	//-----------------------------If Difficulty complete-----------------------------
	if (m_State == DifficultyCompleteState)
	{
		renderDisplayStates(m_State);
		this->m_pWindow->display();
		return;
	}

	//-----------------------------Game Over-----------------------------
	if (getEndGame())
	{
		m_State = GameOverState;
		renderDisplayStates(m_State);
		this->m_pWindow->display();
		return;
	}


	//-----------------------------In Game + Next Stage-----------------------------
	
	/*<<<<<<<<<<<<<<<<<<<<<<<<<<<!!!HELPER TESTING HERE!!!>>>>>>>>>>>>>>>>>>>>*/
	if (m_Helper.isHelping == false)
		m_Helper.help(1, curMaze->FindRoomByPos(curMaze->getStartPos()), curMaze->FindRoomByPos(curMaze->getFinalPos()));
	m_Helper.showInstruction(*m_pWindow);
	/*<<<<<<<<<<<<<<<<<<<<<<<<<<<!!!HELPER TESTING HERE!!!>>>>>>>>>>>>>>>>>>>>*/

	//Render Gui
	this->renderGui(this->m_pWindow);

	//Render end text
	if (this->m_EndGame == true)
		this->m_pWindow->draw(this->m_EndGameText);

	
	curMaze->AddMazeRoomsToRenderer(*m_pWindow);
	curMaze->AddMazeObstaclesToRenderer(*m_pWindow);
	if (timeCycle % 50 == 0) {
		curMaze->NextMazeCycle();
	}
	timeCycle++;
	if (timeCycle == 100) {
		timeCycle = 0;
	}
	m_Player->render(*m_pWindow);
	m_Player->checkCllisionObject(curMaze);

	// Info display
	updateTimeInfo();
	updateCoinsInfo();

	m_Title.drawMyText(*m_pWindow);

	for (int i(0); i < 2; i++) {
		m_CoinsInfo[i].drawMyText(*m_pWindow);
		m_TimeInfo[i].drawMyText(*m_pWindow);
	}


	//-----------------------------Next Stage-----------------------------
	if (m_State == NextStageState || curMaze->completeLevel() == true)
	{
		delay(0.7);
		if (curMaze->isWin() == true) {
			cout << "YOU WIN\n";
			exit(0);
		}
		//Win a difficulty mode
		if (m_Level == MAX_LEVEL - 1)
		{
			m_State = DifficultyCompleteState;
		}
		else
		{
			nextLevel(true);
			m_State = InGameState;
		}
	}
	if (m_Player->getLose() == true)
	{
		delay(0.7);

		//Win a difficulty mode
		if (m_Level == MAX_LEVEL - 1)
		{
			m_State = DifficultyCompleteState;
		}
		else
		{
			nextLevel(false);
			m_State = InGameState;
		}
	}

	
	//-----------------------------Next Stage-----------------------------
	
	// Update level
	updateLevel();
	m_LevelInfo.drawMyText(*m_pWindow);

	if (m_State == LevelCompleteState || m_Player->getPosition() == curMaze->getFinalPos())
	{
		cout << "LEVEL~~~ : " << m_Level << '\n';
		//testing
		renderDisplayStates(NextStageState);
		m_State = NextStageState;
	}
	
	
	// Button display
	m_Help.drawButton(*m_pWindow);
	m_RestartGame.drawButton(*m_pWindow);
	m_ReturnMenu.drawButton(*m_pWindow);

	//-----------------------------In Help State-----------------------------
	if (m_State == InHelpState)
	{
		renderDisplayStates(m_State);
	}


	this->m_pWindow->display();


	if (m_ReturnMenu.isChosen())
	{
		resetGame();
		m_State = MenuState;
		m_ReturnMenu.makeNormal();
		m_Help.makeNormal();
		m_RestartGame.makeNormal();
		return;
	}

	if (m_Help.isChosen())
	{
		m_State = InHelpState;
		return;
	}

	if (m_RestartGame.isChosen())
	{
		return;
	}

}

//@DESCR: Render Game's particular state such as: GameOver, NextStage, LevelComplete
//@PARAM: None
//@RETURN: Non
void Game::renderDisplayStates(GameState state)
{
	if (state == MenuState)
	{
		m_pMenu->draw(*m_pWindow);
		return;
	}

	if (state == DifficultyCompleteState)
	{
		m_pLevelComplete->draw(*m_pWindow, m_Time.getRunningTimeInSec());
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

	if (state == InHelpState)
	{
		if (!m_pHelpMenu->isRun())
			m_pHelpMenu->draw(*m_pWindow);
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

void Game::resetGame()
{
	this->m_EndGame = false;
	this->m_Time.setCDTime(3603);
	this->m_Time.start();
	setLevel(0, true);
}

