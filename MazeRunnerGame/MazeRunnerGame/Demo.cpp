#include "Demo.hpp"

//@DESCR: Initialize variables of StateDemo
//@PARAM: None
//@RETURN: None
void StateDemo::initVariables()
{
}


//@DESCR: Initialize parameter of StateDemo's screen
//@PARAM: None
//@RETURN: None
void StateDemo::initWindow()
{
	//Init window
	this->m_VideoMode = sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT);
	this->m_pWindow = new sf::RenderWindow(this->m_VideoMode, NAME_GAME, sf::Style::Close | sf::Style::Titlebar);
	this->m_pWindow->setFramerateLimit(60);

	//Init displays
	this->m_pChooseMenu = std::shared_ptr<HelpAlgorithmMenu>(new HelpAlgorithmMenu());

}


//@DESCR: Initialize settings and parameters of buttons
//@PARAM: None
//@RETURN: None
void StateDemo::initButtons()
{
	m_ChooseAlgo.setButton(sf::Vector2f(DEMO_OFFSET_CHOOSE_ALGO_X, DEMO_OFFSET_CHOOSE_ALGO_Y), sf::Vector2f(DEMO_BUTTON_WIDTH, DEMO_BUTTON_HEIGHT),
		sf::Color::Transparent, sf::Color::Transparent, "Choose Algorithm",
		FONT_GAME, 20, sf::Text::Style::Bold, sf::Color::White, "Images/button.png");

	m_Find.setButton(sf::Vector2f(DEMO_OFFSET_FIND_X, DEMO_OFFSET_FIND_Y), sf::Vector2f(DEMO_BUTTON_WIDTH, DEMO_BUTTON_HEIGHT),
		sf::Color::Black, sf::Color::Transparent, "Find",
		FONT_GAME, 20, sf::Text::Style::Bold, sf::Color::White, "");

	m_Generate.setButton(sf::Vector2f(DEMO_OFFSET_GENERATE_X, DEMO_OFFSET_GENERATE_Y), sf::Vector2f(DEMO_BUTTON_WIDTH, DEMO_BUTTON_HEIGHT),
		sf::Color::Black, sf::Color::Transparent, "Restart",
		FONT_GAME, 20, sf::Text::Style::Bold, sf::Color::White, "");

	m_ReturnMenu.setButton(sf::Vector2f(DEMO_OFFSET_RETURN_MENU_X, DEMO_OFFSET_RETURN_MENU_Y), sf::Vector2f(DEMO_BUTTON_WIDTH, DEMO_BUTTON_HEIGHT),
		sf::Color::Black, sf::Color::Transparent, "Menu",
		FONT_GAME, 20, sf::Text::Style::Bold, sf::Color::White, "");
}


//@DESCR: Initialize settings and parameters of text
//@PARAM: None
//@RETURN: None
void StateDemo::initText()
{
	initTitle();
	initAlgorithmInfo();
}

//@DESCR: Constructor of StateDemo
//@PARAM: None
//@RETURN: None
StateDemo::StateDemo()
{
	this->initVariables();
	this->initWindow();
	this->initButtons();
	this->initText();

	curMaze = std::shared_ptr<LevelMaze>(new DemoMaze())->OrderLevelMaze();
	m_Player = std::shared_ptr<Player>(new Player(curMaze->getStartPos(), OFFSET_MAZE_X, OFFSET_MAZE_Y, curMaze->getWidthRoom(), curMaze->getHeightRoom()));
	m_Chest = curMaze->mazeChest;
}


//@DESCR: Destructor of StateDemo
//@PARAM: None
//@RETURN: None
StateDemo::~StateDemo()
{
	delete this->m_pWindow;
}

//@DESCR: Check whether the StateDemo is running
//@PARAM: None
//@RETURN: the state of the game: FALSE - ended | TRUE - running
const bool StateDemo::running() const
{
	return this->m_pWindow->isOpen() /*&& this->m_EndGame == false*/;
}

//@DESCR: Get events from user
//@PARAM: None
//@RETURN: None
void StateDemo::pollEvents()
{
	sf::Event temp;

	while (this->m_pWindow->pollEvent(temp))
	{
		if (temp.type != sf::Event::MouseButtonPressed) {
			m_ChooseAlgo.makeNormal();
			m_Find.makeNormal();
			m_Generate.makeNormal();
			m_ReturnMenu.makeNormal();
		}
		switch (temp.type)
		{
		case sf::Event::Closed:
			this->m_pWindow->close();
			break;
			//------------------CLICK EVENT------------------
		case sf::Event::MouseButtonReleased:
			cout << "NO" << endl;
			if (m_Player->isChosenByMouse) {
				cout << "Give up choosing player!\n";
				m_Player->isChosenByMouse = false;
			}
			if (m_Chest->isChosenByMouse) {
				cout << "Give up choosing chest!\n";
				m_Chest->isChosenByMouse = false;
			}
			break;
		case sf::Event::MouseButtonPressed:
			cout << "YES" << endl;
			if (m_Player->checkMouseOver(*m_pWindow)) {
				m_Player->isChosenByMouse = true;
				break;
			}

			if (m_Chest->checkMouseOver(*m_pWindow)) {
				m_Chest->isChosenByMouse = true;
				break;
			}

			if (m_State == InDemoState)
			{
				if (m_ChooseAlgo.isClickV1(m_pWindow)) {
					m_ChooseAlgo.makeChosen();
				}

				if (m_Find.isClickV1(m_pWindow)) {
					m_Find.makeChosen();
					m_Demoer.start(0, curMaze->FindRoomByPos(curMaze->getStartPos()), curMaze->FindRoomByPos(curMaze->getFinalPos()));
				}

				if (m_ReturnMenu.isClickV1(m_pWindow)) {
					m_ReturnMenu.makeChosen();
				}

				if (m_Generate.isClickV1(m_pWindow)) {
					m_Generate.makeChosen();
				}

				break;
			}

			if (m_State == InChoosingState) //Choosing Algorithm
			{
				if (m_pChooseMenu->isExit(m_pWindow)) //Check exit
				{
					//back to normal
					m_State = InDemoState;
					m_ChooseAlgo.makeNormal();
					m_Find.makeNormal();
					m_Generate.makeNormal();
					m_ReturnMenu.makeNormal();
				}
				else
					m_pChooseMenu->pollEvent(m_pWindow); //Choose Algorithms
				break;
			}
			break;
		}

	}

	this->m_Event = temp;
}

//@DESCR: Update all changes
//@PARAM: None
//@RETURN: None
void StateDemo::update()
{
	this->pollEvents();

	if (m_Demoer.isShowing) {
		if (m_Demoer.isFinished == false)
			return;
	}

	if (this->m_EndGame == false && m_State == InDemoState) {
		if ((m_Chest->isChosenByMouse || m_Player->isChosenByMouse)) {
			m_Demoer.end();
			sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_pWindow);
			sf::Vector2i mousePositionOnMaze;

			mousePositionOnMaze.x = (mousePosition.x - OFFSET_MAZE_X) / (int)m_Player->getSize().x;
			mousePositionOnMaze.y = (mousePosition.y - OFFSET_MAZE_Y) / (int)m_Player->getSize().y;
			//cout << "Mouse's initial position on maze: " << mousePositionOnMaze.x << " " << mousePositionOnMaze.y << endl;
			// Adjust value
			mousePositionOnMaze.x = (mousePositionOnMaze.x < 0 ? 0 : mousePositionOnMaze.x);
			mousePositionOnMaze.y = (mousePositionOnMaze.y < 0 ? 0 : mousePositionOnMaze.y);
			mousePositionOnMaze.x = (mousePositionOnMaze.x >= curMaze->getNumRoomX() ? curMaze->getNumRoomX() - 1 : mousePositionOnMaze.x);
			mousePositionOnMaze.y = (mousePositionOnMaze.y >= curMaze->getNumRoomY() ? curMaze->getNumRoomY() - 1 : mousePositionOnMaze.y);

			//cout << "Mouse's position on maze: " << mousePositionOnMaze.x << " " << mousePositionOnMaze.y << endl;

			MazeCoordinate newPosition(mousePositionOnMaze.x, mousePositionOnMaze.y);

			if (m_Player->isChosenByMouse) {
				m_Player->setPosition(newPosition);
				curMaze->setStartPos(newPosition);
			}
			else if (m_Chest->isChosenByMouse) {
				m_Chest->setPosition(newPosition);
				curMaze->setFinalPos(newPosition);
			}
		}
	}
}

//@DESCR: Render StateDemo's state
//@PARAM: None
//@RETURN: None
void StateDemo::render()
{
	m_pWindow->clear(sf::Color(128, 128, 128));

	//-----------------------------In StateDemo-----------------------------
	if (m_Demoer.isShowing)
		m_Demoer.showInstruction(*m_pWindow);
	curMaze->AddMazeRoomsToRenderer(*m_pWindow);
	curMaze->AddMazeObstaclesToRenderer(*m_pWindow);

	m_Player->render(*m_pWindow);
	m_Player->checkCllisionObject(curMaze);

	// Info display
	updateAlgorithmInfo();

	m_Title.drawMyText(*m_pWindow);

	for (int i(0); i < 2; i++) {
		m_Algorithm[i].drawMyText(*m_pWindow);
	}

	// Button display
	m_ChooseAlgo.drawButton(*m_pWindow);
	m_Find.drawButton(*m_pWindow);
	m_Generate.drawButton(*m_pWindow);
	m_ReturnMenu.drawButton(*m_pWindow);

	//-----------------------------In Help State-----------------------------
	if (m_State == InChoosingState)
	{
		renderDisplayStates(m_State);
	}

	this->m_pWindow->display();


	if (m_ReturnMenu.isChosen())
	{

	}

	if (m_Find.isChosen())
	{

	}

	if (m_ChooseAlgo.isChosen())
	{
		m_State = InChoosingState;
		return;
	}

	if (m_Generate.isChosen())
	{
		resetGame();
		return;
	}

}

//@DESCR: Render StateDemo's particular state such as: GameOver, NextStage, LevelComplete
//@PARAM: None
//@RETURN: Non
void StateDemo::renderDisplayStates(DemoState state)
{
	if (state == InChoosingState)
	{
		if (!m_pChooseMenu->isRun())
			m_pChooseMenu->draw(*m_pWindow);
		return;
	}
}


void StateDemo::initTitle() {
	m_Title.setBox(sf::Vector2f(DEMO_OFFSET_TITLE_X, DEMO_OFFSET_TITLE_Y),
		sf::Vector2f(DEMO_TITLE_WIDTH, DEMO_TITLE_HEIGHT),
		sf::Color::Black, sf::Color::Transparent);

	m_Title.setText("MAZE RUNNER", FONT_GAME, 90, sf::Text::Bold, sf::Color::White);
	m_Title.setCharacterSpacing(1.5);
	m_Title.alignTextCenter();
	m_Title.alignTextMiddle();
}

void StateDemo::initAlgorithmInfo() {
	// Algorithm title
	m_Algorithm[0].setBox(sf::Vector2f(DEMO_OFFSET_ALGO_X, DEMO_OFFSET_ALGO_Y),
		sf::Vector2f(DEMO_INFO_WIDTH, DEMO_INFO_HEIGHT / 2),
		sf::Color::Black, sf::Color::White);
	m_Algorithm[0].setBoxOutlineThickness(5);

	m_Algorithm[0].setText("ALGORITHM", FONT_GAME, 30, sf::Text::Bold, sf::Color::White);
	m_Algorithm[0].setCharacterSpacing(1.5);
	m_Algorithm[0].alignTextCenter();
	m_Algorithm[0].alignTextMiddle();

	// Coins info
	stringstream writer("");
	m_Algorithm[1].setBox(sf::Vector2f(DEMO_OFFSET_ALGO_NAME_X, DEMO_OFFSET_ALGO_NAME_Y),
		sf::Vector2f(DEMO_INFO_WIDTH, DEMO_INFO_HEIGHT / 2),
		sf::Color::Black, sf::Color::White);
	m_Algorithm[1].setBoxOutlineThickness(5);

	writer << "BFS";

	m_Algorithm[1].setText(writer.str(), FONT_GAME, 30, sf::Text::Bold, sf::Color::White);
	m_Algorithm[1].setCharacterSpacing(1.5);
	m_Algorithm[1].alignTextCenter();
	m_Algorithm[1].alignTextMiddle();
}

void StateDemo::updateAlgorithmInfo() {
	m_Algorithm[1].setContent("A-STAR");
	m_Algorithm[1].alignTextCenter();
	m_Algorithm[1].alignTextMiddle();
}

void StateDemo::resetGame()
{
	curMaze->UpdateMaze(false);

	m_Player->setPosition(curMaze->getStartPos());
	m_Player->setSize(curMaze->getWidthRoom(), curMaze->getHeightRoom());
	m_Player->updateDirecPlayer(0);
	m_Player->setLose(false);

	m_Player->updateDirecPlayer(0);

}
