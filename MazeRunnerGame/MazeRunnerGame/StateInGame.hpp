#pragma once
#include "StateGame.hpp"

//enum GameState { InGameState, InHelpState, NextStageState, LevelCompleteState };
//
//struct MyLevel {
//	int x, y;
//};
//
//class StateInGame : public StateGame {
//private:
//	static std::shared_ptr<LevelMaze> levelMaze;
//	static int timeCycle;
//public:
//	sf::RenderWindow* m_pWindow;
//	sf::Event m_Event;
//private:
//	//----------------Game State atrributes----------------
//	GameState m_State;
//	Helper m_Helper;
//	bool m_EndGame;
//
//	//----------------Display attributes----------------
//	shared_ptr<NextStage> m_pNextStage;
//	shared_ptr<HelpAlgorithmMenu> m_pHelpMenu;
//
//
//	//----------------"In Game processing"  atrributes----------------
//	shared_ptr<Maze> curMaze;
//	shared_ptr<Player> m_Player;
//	int m_Points;
//
//	//----------------Stat attributes----------------
//	MyClock m_Time; //total times
//	int m_Level; //current levels
//
//
//	//----------------GUI atrributes----------------
//	sf::Font m_Font;
//	sf::Text m_GuiText;
//	sf::Text m_EndGameText;
//
//	MyText m_Title;
//	MyText m_LevelInfo;
//	MyText m_TimeInfo[2];
//	MyText m_CoinsInfo[2];
//
//	Button m_Help;
//	Button m_ReturnMenu;
//	Button m_RestartGame;
//
//public:
//	StateInGame();
//
//public:
//	//----------------Initial GUI functions----------------
//	void initVariables();
//	void initWindow();
//	void initFonts();
//	void initButtons();
//	void initText();
//
//	void initTitle();
//	void initLevelInfo();
//	void initTimeInfo();
//	void initCoinsInfo();
//
//
//	//----------------Update GUI functions----------------
//	void updatePlayer();
//	void updateGui();
//	void updateTimeInfo();
//	void updateCoinsInfo();
//	void updateLevel();
//
//
//	//----------------Render GUI functions----------------
//	void renderGui(sf::RenderTarget* target);
//	void renderDisplayStates(GameState); //render above Display attributes
//
//
//	//----------------"In game processing" functions----------------
//	void nextLevel(bool check);
//	void setLevel(int _level, bool check);
//	void resetGame(); //reset all variables of game aka the second initVariables =))))
//	bool getEndGame();
//
//
//public:
//	void pollEvents() override;
//	void update() override;
//	void render() override;
//
//};

#define SCREEN_TITLE_WIDTH	(SCREEN_WIDTH - 2 * SPACE)
#define SCREEN_TITLE_HEIGHT	(OFFSET_MAZE_Y - 2 * SPACE) 
#define OFFSET_TITLE_X		(SPACE + SCREEN_TITLE_WIDTH / 2) 
#define OFFSET_TITLE_Y		(SPACE + SCREEN_TITLE_HEIGHT / 2)

#define NUMBER_OF_BOXES 3
#define NUMBER_OF_BUTTONS 3

#define SCREEN_INFO_HEIGHT (SCREEN_MAZE_Y / NUMBER_OF_BOXES)
#define SCREEN_INFO_WIDTH (SCREEN_WIDTH - SCREEN_MAZE_X - 2 * SPACE)	

#define OFFSET_LEVEL_X (OFFSET_MAZE_X + SCREEN_MAZE_X + 5 + SCREEN_INFO_WIDTH / 2)
#define OFFSET_LEVEL_Y (OFFSET_MAZE_Y + SCREEN_INFO_HEIGHT / 2)

#define OFFSET_TIME_X (OFFSET_LEVEL_X - SCREEN_INFO_WIDTH / 4)
#define OFFSET_TIME_Y (OFFSET_LEVEL_Y + SCREEN_INFO_HEIGHT / 4 * 3)
#define OFFSET_TIME_INFO_X OFFSET_TIME_X
#define OFFSET_TIME_INFO_Y (OFFSET_TIME_Y + SCREEN_INFO_HEIGHT / 2)

#define OFFSET_COINS_X (OFFSET_LEVEL_X + SCREEN_INFO_WIDTH / 4)
#define OFFSET_COINS_Y OFFSET_TIME_Y
#define OFFSET_COINS_INFO_X OFFSET_COINS_X
#define OFFSET_COINS_INFO_Y (OFFSET_COINS_Y + SCREEN_INFO_HEIGHT / 2)

#define BUTTON_HEIGHT (SCREEN_INFO_HEIGHT / 2)
#define BUTTON_WIDTH (SCREEN_INFO_WIDTH / (NUMBER_OF_BUTTONS + 1))
#define BUTTON_SPACE (BUTTON_WIDTH / (NUMBER_OF_BUTTONS + 1))

#define OFFSET_HELP_X (OFFSET_LEVEL_X - SCREEN_INFO_WIDTH / 2 + BUTTON_SPACE + BUTTON_WIDTH / 2)
#define OFFSET_HELP_Y (OFFSET_TIME_INFO_Y + SCREEN_INFO_HEIGHT / 4 * 3)

#define OFFSET_RESTART_X (OFFSET_HELP_X + BUTTON_WIDTH + BUTTON_SPACE)
#define OFFSET_RESTART_Y OFFSET_HELP_Y

#define OFFSET_RETURN_MENU_X (OFFSET_RESTART_X + BUTTON_WIDTH + BUTTON_SPACE)
#define OFFSET_RETURN_MENU_Y OFFSET_HELP_Y
