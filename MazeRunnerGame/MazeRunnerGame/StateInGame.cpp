#include "StateInGame.hpp"

MyLevel level[7] = { MyLevel{3, 3} , MyLevel{ 5, 5 }, MyLevel{ 9, 9 }, MyLevel{ 15, 15 }, MyLevel{ 20, 20 }, MyLevel{ 23, 23 }, MyLevel{ 30, 30 } };
std::shared_ptr<LevelMaze> StateInGame::levelMaze = NULL;
int StateInGame::timeCycle = 0;

//@DESCR: Initialize variables of Game
//@PARAM: None
//@RETURN: None
void StateInGame::initVariables()
{
	m_State = InGameState; //Obviously, we always in MenuState when entering game
	this->m_EndGame = false;
	this->m_Time.setCDTime(3603);
	this->m_Time.start();
	this->m_Level = 0;


}

void StateInGame::initWindow()
{
	this->m_pWindow = SingletonRenderWindow::getInstance();
	this->m_pNextStage = std::shared_ptr<NextStage>(new NextStage());
	this->m_pHelpMenu = std::shared_ptr<HelpAlgorithmMenu>(new HelpAlgorithmMenu());
	
}


//@DESCR: Initialze settings of fonts
//@PARAM: None
//@RETURN: None
void StateInGame::initFonts()
{
	if (!this->m_Font.loadFromFile("Fonts/TitleFont.ttf"))
	{
		std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD TitleFont.ttf" << "\n";
	}
}


//@DESCR: Initialize settings and parameters of buttons
//@PARAM: None
//@RETURN: None
void StateInGame::initButtons()
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
void StateInGame::initText()
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
void StateInGame::nextLevel(bool check)
{
	if (m_Level >= MAX_LEVEL - 1)
		return;
	m_Level++;
	setLevel(m_Level, check);
}


//@DESCR: Changing from "current" level to new level
//@PARAM: new level
//@RETURN: None
void StateInGame::setLevel(int _level, bool check)
{

	m_Level = _level;
	curMaze->UpdateMaze(check);

	m_Player->setPosition(curMaze->getStartPos());
	m_Player->setSize(curMaze->getWidthRoom(), curMaze->getHeightRoom());
	m_Player->updateDirecPlayer(1);
	m_Player->setLose(false);
	m_Player->resetTimes(check);

	//m_Player->updateDirecPlayer(1);
}


//@DESCR: Constructor of Game
//@PARAM: None
//@RETURN: None
StateInGame::StateInGame(bool isContinue)
{
	initWindow();
	initVariables();
	initFonts();
	initButtons();
	initText();

	if (isContinue)
	{
		std::cout << "LOAD\n";
		load();
	}
	else
	{
		if (StateModeSelect::pressedItem == 0)
			levelMaze = std::shared_ptr<LevelMaze>(new EasyLevelMaze());

		if (StateModeSelect::pressedItem == 1)
			levelMaze = std::shared_ptr<LevelMaze>(new MediumLevelMaze());

		if (StateModeSelect::pressedItem == 2)
			levelMaze = std::shared_ptr<LevelMaze>(new HardLevelMaze());


		curMaze = levelMaze->OrderLevelMaze();
		m_Player = std::shared_ptr<Player>(new Player(curMaze->getStartPos(), OFFSET_MAZE_X, OFFSET_MAZE_Y, curMaze->getWidthRoom(), curMaze->getHeightRoom()));
	}
}


//@DESCR: Check whether the Game is ended
//@PARAM: None
//@RETURN: the state of the game: FALSE - running | TRUE - ended
bool StateInGame::getEndGame()
{
	this->m_EndGame = m_Time.isOver();
	return this->m_EndGame;
}



//@DESCR: Update m_Player's changes, including position
//@PARAM: None
//@RETURN: None
void StateInGame::updatePlayer()
{
	this->m_Player->update(m_pWindow, m_Event.key.code, curMaze);
}


//@DESCR: Update GUI's changes
//@PARAM: None
//@RETURN: None
void StateInGame::updateGui()
{
	stringstream writer;
	//Level Info
}


//@DESCR: Render GUi
//@PARAM: m_pWindow to render GUi on
//@RETURN: None
void StateInGame::renderGui(sf::RenderTarget* target)
{
	target->draw(this->m_GuiText);
}


//@DESCR: Render Game's particular state such as: GameOver, NextStage, LevelComplete
//@PARAM: None
//@RETURN: Non
void StateInGame::renderDisplayStates(GameState state)
{

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


void StateInGame::initTitle() {
	m_Title.setBox(sf::Vector2f(OFFSET_TITLE_X, OFFSET_TITLE_Y),
		sf::Vector2f(SCREEN_TITLE_WIDTH, SCREEN_TITLE_HEIGHT),
		sf::Color::Black, sf::Color::Transparent);

	m_Title.setText("MAZE RUNNER", FONT_GAME, 90, sf::Text::Bold, sf::Color::White);
	m_Title.setCharacterSpacing(1.5);
	m_Title.alignTextCenter();
	m_Title.alignTextMiddle();
}

void StateInGame::initLevelInfo() {
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

void StateInGame::initTimeInfo() {
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

void StateInGame::initCoinsInfo() {
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

void StateInGame::updateTimeInfo() {
	m_TimeInfo[1].setContent(m_Time.getCDTime());
	m_TimeInfo[1].alignTextCenter();
	m_TimeInfo[1].alignTextMiddle();
}

void StateInGame::updateCoinsInfo() {
	stringstream writer("");
	writer << m_Points;

	m_CoinsInfo[1].setContent(writer.str());
	m_CoinsInfo[1].alignTextCenter();
	m_CoinsInfo[1].alignTextMiddle();
}

void StateInGame::updateLevel() {
	stringstream writer("");

	writer << "LEVEL " << m_Level + 1;

	m_LevelInfo.setContent(writer.str());
	m_LevelInfo.alignTextCenter();
	m_LevelInfo.alignTextMiddle();
}

void StateInGame::resetGame()
{
	this->m_EndGame = false;
	this->m_Time.setCDTime(3603);
	this->m_Time.start();
	setLevel(0, true);
}


void StateInGame::pollEvents()
{
	
		sf::Event temp;
		while (this->m_pWindow->pollEvent(temp))
		{

			switch (temp.type)
			{
			case sf::Event::Closed:
				this->m_pWindow->close();
				break;

				//------------------CLICK EVENT------------------
			case sf::Event::MouseButtonPressed:
				if (m_State == GameState::InGameState)
				{
					if (m_Help.isClickV1(m_pWindow))
					{
						//
						//run
						//
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

				if (m_State == GameState::InHelpState) //Choosing Algorithm
				{
					if (m_pHelpMenu->isExit(m_pWindow)) //Check exit
					{
						//back to normal
						m_State = GameState::InGameState;
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

				//In Game
				if (m_State == InGameState)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
					{
						m_State = GameState::LevelCompleteState;
					}
					break;
				}


				//In Help State
				if (m_State == InHelpState)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					{
						m_State = GameState::InGameState;
					}
					break;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					resetGame();
					//m_State = GameState::MenuState;
					break;
				}
				break;

			}
		}//
		this->m_Event = temp;

		if (m_ReturnMenu.isChosen())
		{
			resetGame();
			m_ReturnMenu.makeNormal();
			save();
			context_->TransitionTo(new StateMenu);
			return;
		}

		if (m_Help.isChosen())
		{
			m_State = GameState::InHelpState;
			return;
		}

		if (m_RestartGame.isChosen())
		{
			return;
		}

		return;
	
}

void StateInGame::update()
{
	if (this->m_EndGame == false && m_State == InGameState)
	{
		if (m_Event.type == sf::Event::KeyPressed)
			this->updatePlayer();
		this->updateGui();
	}
}

void StateInGame::render()
{

	m_pWindow->clear(sf::Color(128, 128, 128));

	//-----------------------------In Game + Next Stage-----------------------------

	/*<<<<<<<<<<<<<<<<<<<<<<<<<<<!!!HELPER TESTING HERE!!!>>>>>>>>>>>>>>>>>>>>*/
	/*if (m_Helper.isHelping == false)
		m_Helper.help(2, curMaze->FindRoomByPos(curMaze->getStartPos()), curMaze->FindRoomByPos(curMaze->getFinalPos()));
	m_Helper.showInstruction(*m_pWindow);*/
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
		//Save after 100 timcyles
		//this->save();
		save();
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
	if (m_Player->loseLevel()) { //GameOver
		this->context_->TransitionTo(new StateOverGame);
		return;
	}
	if (m_State == NextStageState || curMaze->completeLevel() == true)
	{
		delay(0.7);

		//Win a difficulty mode
		if (curMaze->isWin() == true) {
			std::cout << "YOU WIN\n";
			this->context_->TransitionTo(new StateDifficultyComplete);
			return;
		}
		
		nextLevel(true);
		m_State = InGameState;
	}


	if (m_Player->getLose() == true) //Restart
	{
		delay(0.7);

		//Win a difficulty mode
		if (m_Level == MAX_LEVEL - 1)
		{
			//m_State = DifficultyCompleteState;
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

	if (m_State == LevelCompleteState)
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

}
