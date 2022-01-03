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
	this->m_pWindow = SingletonRenderWindow::getInstance();

	//Init displays
	this->m_pChooseMenu = std::shared_ptr<HelpAlgorithmMenu>(new HelpAlgorithmMenu());

	if (!textureBackground.loadFromFile(IMG_BEHINDMAZE))
	{
		std::cout << "Load file failed" << std::endl;
	}
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);

}


//@DESCR: Initialize settings and parameters of buttons
//@PARAM: None
//@RETURN: None
void StateDemo::initButtons()
{

	float scSize = 1.15;

	m_ChooseAlgo.setButton(sf::Vector2f(DEMO_OFFSET_CHOOSE_ALGO_X, DEMO_OFFSET_CHOOSE_ALGO_Y), sf::Vector2f(DEMO_BUTTON_WIDTH, DEMO_BUTTON_HEIGHT),
		sf::Color::Transparent, sf::Color::Transparent, "",
		FONT_GAME, 20, sf::Text::Style::Bold, sf::Color::White, "Images/DDemoChooseAlgo.png");
	m_ChooseAlgo.setScaleSprite(sf::Vector2f(m_ChooseAlgo.getScaleSprite().x * scSize, m_ChooseAlgo.getScaleSprite().y * scSize));

	m_Find.setButton(sf::Vector2f(DEMO_OFFSET_FIND_X, DEMO_OFFSET_FIND_Y), sf::Vector2f(DEMO_BUTTON_WIDTH, DEMO_BUTTON_HEIGHT),
		sf::Color::Transparent, sf::Color::Transparent, "",
		FONT_GAME, 20, sf::Text::Style::Bold, sf::Color::White, "Images/DDemoFind.png");
	m_Find.setScaleSprite(sf::Vector2f(m_Find.getScaleSprite().x * scSize, m_Find.getScaleSprite().y * scSize));

	m_Generate.setButton(sf::Vector2f(DEMO_OFFSET_GENERATE_X, DEMO_OFFSET_GENERATE_Y), sf::Vector2f(DEMO_BUTTON_WIDTH, DEMO_BUTTON_HEIGHT),
		sf::Color::Transparent, sf::Color::Transparent, "",
		FONT_GAME, 20, sf::Text::Style::Bold, sf::Color::White, "Images/DDemoGenerate.png");
	m_Generate.setScaleSprite(sf::Vector2f(m_Generate.getScaleSprite().x * scSize, m_Generate.getScaleSprite().y * scSize));

	m_ReturnMenu.setButton(sf::Vector2f(DEMO_OFFSET_RETURN_MENU_X, DEMO_OFFSET_RETURN_MENU_Y), sf::Vector2f(DEMO_BUTTON_WIDTH, DEMO_BUTTON_HEIGHT),
		sf::Color::Transparent, sf::Color::Transparent, "",
		FONT_GAME, 20, sf::Text::Style::Bold, sf::Color::White, "Images/DDemoMenu.png");
	m_ReturnMenu.setScaleSprite(sf::Vector2f(m_ReturnMenu.getScaleSprite().x * scSize, m_ReturnMenu.getScaleSprite().y * scSize));
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
			//cout << "Mouse is released" << endl;
			if (m_Player->isChosenByMouse) {
				//cout << "Give up choosing player!\n";
				m_Player->isChosenByMouse = false;
			}
			if (m_Chest->isChosenByMouse) {
				//cout << "Give up choosing chest!\n";
				m_Chest->isChosenByMouse = false;
			}
			break;
		case sf::Event::MouseButtonPressed:
			//cout << "Mouse is pressed" << endl;
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
				{
					bool isConfirm =  m_pChooseMenu->pollEvent(m_pWindow); //Choose Algorithms
					if (isConfirm)
					{
						m_State = InDemoState;
						m_ChooseAlgo.makeNormal();
						m_Find.makeNormal();
						m_Generate.makeNormal();
						m_ReturnMenu.makeNormal();
					}
				}
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
	m_pWindow->draw(spriteBackground);

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
	if (m_Demoer.isShowing == false || m_Demoer.isFinished == true) {
		bool endShowingPath = false;

		if (m_State == InChoosingState)
		{
			renderDisplayStates(m_State);
		}

		if (m_Find.isChosen())
		{
			m_Demoer.start(m_pChooseMenu->getOptionAlgo(), curMaze->FindRoomByPos(curMaze->getStartPos()), curMaze->FindRoomByPos(curMaze->getFinalPos()));
		}

		if (m_ChooseAlgo.isChosen())
		{
			m_State = InChoosingState;
		}

		if (m_Generate.isChosen())
		{
			m_Demoer.end();
			MazeCoordinate startPos = m_Player->getPosition();
			MazeCoordinate finalPos = m_Chest->getPosition();

			curMaze = std::shared_ptr<LevelMaze>(new DemoMaze())->OrderLevelMaze();
			curMaze->setStartPos(startPos);
			curMaze->setFinalPos(finalPos);
			m_Chest = curMaze->mazeChest;
		}
	}

	this->m_pWindow->display();

	if (m_ReturnMenu.isChosen())
	{
		this->context_->TransitionTo(new StateMenu);
		return;
	}
}

//@DESCR: Render StateDemo's particular state such as: GameOver, NextStage, LevelComplete
//@PARAM: None
//@RETURN: None
void StateDemo::renderDisplayStates(StatesInDemo state)
{
	if (state == InChoosingState)
	{
		m_pChooseMenu->draw(*m_pWindow);
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
	string algoName[]{ "BFS", "DFS", "A-STAR" };

	m_Algorithm[1].setContent(algoName[m_pChooseMenu->getOptionAlgo()]);
	m_Algorithm[1].alignTextCenter();
	m_Algorithm[1].alignTextMiddle();
}

