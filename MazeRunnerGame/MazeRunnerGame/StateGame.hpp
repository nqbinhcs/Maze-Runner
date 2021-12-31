#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <time.h>

#include<iostream>
#include<ctime>
#include<vector>
#include<sstream>

#include "Clock.hpp"
#include "Player.hpp"
#include "DefinedVariables.hpp"
#include "Maze.hpp"
#include "GameOver.hpp"
#include "NextStage.hpp"
#include "LevelComplete.hpp"
#include "Menu.hpp"
#include "ModeGame.hpp"
#include "Button.hpp"
#include "Helper.hpp"
#include "HelpAlgorithmMenu.hpp"
#include "MazeFactory.hpp"
#include "Instruction.hpp"

using namespace std;

class SingletonRenderWindow
{
public:
	static sf::RenderWindow* window;
public:
	static sf::RenderWindow* getInstance() {
		if (window == nullptr)
		{
			window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), NAME_GAME, sf::Style::Close | sf::Style::Titlebar);
			window->setFramerateLimit(300);
		}
		return window;
	}
};

class ContextGame;


class StateGame {
    
protected:
    ContextGame* context_;

public:
    virtual ~StateGame() {
    }

    void set_context(ContextGame* context) {
        this->context_ = context;
    }

    virtual void pollEvents() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
};


//MENU

class StateMenu : public StateGame {
public:
    sf::RenderWindow* m_pWindow;
private:
    shared_ptr<Menu> m_pMenu;

public:
    StateMenu() {
        this->m_pWindow = SingletonRenderWindow::getInstance();
        this->m_pMenu = std::shared_ptr<Menu>(new Menu(SCREEN_WIDTH, SCREEN_HEIGHT));
    }

public:
    void pollEvents() override;

    void update() override;

    void render() override;
};


//IN GAME
enum GameState { InGameState, InHelpState, NextStageState, LevelCompleteState };

struct MyLevel {
	int x, y;
};

class StateInGame : public StateGame {
private:
	static std::shared_ptr<LevelMaze> levelMaze;
	static int timeCycle;
public:
	sf::RenderWindow* m_pWindow;
	sf::Event m_Event;
private:
	//----------------Game State atrributes----------------
	GameState m_State;
	Helper m_Helper;
	bool m_EndGame;

	//----------------Display attributes----------------
	shared_ptr<NextStage> m_pNextStage;
	shared_ptr<HelpAlgorithmMenu> m_pHelpMenu;


	//----------------"In Game processing"  atrributes----------------
	shared_ptr<Maze> curMaze;
	shared_ptr<Player> m_Player;
	int m_Points;

	//----------------Stat attributes----------------
	MyClock m_Time; //total times
	int m_Level; //current levels


	//----------------GUI atrributes----------------
	sf::Font m_Font;
	sf::Text m_GuiText;
	sf::Text m_EndGameText;

	MyText m_Title;
	MyText m_LevelInfo;
	MyText m_TimeInfo[2];
	MyText m_CoinsInfo[2];

	Button m_Help;
	Button m_ReturnMenu;
	Button m_RestartGame;

public:
	StateInGame();

public:
	//----------------Initial GUI functions----------------
	void initVariables();
	void initWindow();
	void initFonts();
	void initButtons();
	void initText();

	void initTitle();
	void initLevelInfo();
	void initTimeInfo();
	void initCoinsInfo();


	//----------------Update GUI functions----------------
	void updatePlayer();
	void updateGui();
	void updateTimeInfo();
	void updateCoinsInfo();
	void updateLevel();


	//----------------Render GUI functions----------------
	void renderGui(sf::RenderTarget* target);
	void renderDisplayStates(GameState); //render above Display attributes


	//----------------"In game processing" functions----------------
	void nextLevel(bool check);
	void setLevel(int _level, bool check);
	void resetGame(); //reset all variables of game aka the second initVariables =))))
	bool getEndGame();


public:
	void pollEvents() override;
	void update() override;
	void render() override;

};


//SELECT
class StateModeSelect : public StateGame {
public:
	sf::RenderWindow* m_pWindow;
private:
	shared_ptr<ModeGame> m_pModeGame;

public:
	StateModeSelect() {
		this->m_pWindow = SingletonRenderWindow::getInstance();
		this->m_pModeGame = std::shared_ptr<ModeGame>(new ModeGame(SCREEN_WIDTH, SCREEN_HEIGHT));
	}

public:
	void pollEvents() override;

	void update() override;

	void render() override;
};


//DIFFICULTY COMPLETE
class StateDifficultyComplete : public StateGame {
public:
	sf::RenderWindow* m_pWindow;
private:
	shared_ptr<LevelComplete> m_pLevelComplete;

public:
	StateDifficultyComplete() {
		this->m_pWindow = SingletonRenderWindow::getInstance();
		this->m_pLevelComplete = std::shared_ptr<LevelComplete>(new LevelComplete());
	}

public:
	void pollEvents() override;
	void update() override;
	void render() override;
};


//GAMEOVER
class StateOverGame : public StateGame {
public:
	sf::RenderWindow* m_pWindow;
private:
	shared_ptr<GameOver> m_pGameOver;

public:
	StateOverGame() {
		this->m_pWindow = SingletonRenderWindow::getInstance();
		this->m_pGameOver = std::shared_ptr<GameOver>(new GameOver(SCREEN_WIDTH, SCREEN_HEIGHT));
	}

public:
	void pollEvents() override;
	void update() override;
	void render() override;
};


//VisualDemo
class StateDemo : public StateGame {
public:
	sf::RenderWindow* m_pWindow;

public:
	StateDemo() {
		this->m_pWindow = SingletonRenderWindow::getInstance();
	}

public:
	void pollEvents() override;
	void update() override;
	void render() override;
};


//Instruction
class StateHelpInstruction : public StateGame {
public:
	sf::RenderWindow* m_pWindow;
private:
	shared_ptr<Instruction> m_pInstruction;

public:
	StateHelpInstruction() {
		this->m_pWindow = SingletonRenderWindow::getInstance();
		this->m_pInstruction = std::shared_ptr<Instruction>(new Instruction(SCREEN_WIDTH, SCREEN_HEIGHT));

	}

public:
	void pollEvents() override;
	void update() override;
	void render() override;
};


//Continue
class StateContinue : public StateGame {
public:
	sf::RenderWindow* m_pWindow;

public:
	StateContinue() {
		this->m_pWindow = SingletonRenderWindow::getInstance();
	}

public:
	void pollEvents() override;
	void update() override;
	void render() override;
};



class ContextGame {
   
private:
    StateGame* state_;

public:
    static StateMenu* stateMenu_;
    static StateInGame* stateInGame_;
    static StateModeSelect* stateModeSelect_;
	static StateDemo* stateDemo_;
	static StateDifficultyComplete* stateDifficultyComplete_;
	static StateOverGame* stateOverGame_;
	static StateHelpInstruction* stateHelpInstruction_;
	static StateContinue* stateContinue_;

public: //Utilities

	static StateMenu* getStateMenu() { return stateMenu_; } //getter
	static StateInGame* getStateInGame() { return stateInGame_; }
	static StateModeSelect* getStateModeSelect() { return stateModeSelect_; }
	static StateDemo* getStateDemo() { return stateDemo_; };
	static StateDifficultyComplete* getStateDifficultyComplete() { return stateDifficultyComplete_; }
	static StateOverGame* getStateOverGame() { return stateOverGame_;}
	static StateHelpInstruction* getStateHelpInstruction() { return stateHelpInstruction_; };
	static StateContinue* getStateContinue() { return stateContinue_; };

	static void makeDelete() //delete
	{
		if (stateMenu_) delete stateMenu_;
		if (stateInGame_) delete stateInGame_;
		if (stateModeSelect_) delete stateModeSelect_;
		if (stateDemo_) delete stateDemo_;
		if (stateDifficultyComplete_) delete stateDifficultyComplete_;
		if (stateOverGame_) delete stateOverGame_;
		if (stateHelpInstruction_) delete stateHelpInstruction_;
		if (stateContinue_) delete stateContinue_;
	}

public:
    ContextGame(StateGame* state) : state_(nullptr) {
        this->TransitionTo(state);
    }
    ~ContextGame() {
        
    }

    
    void TransitionTo(StateGame* state) {
        std::cout << "Context: Transition to " << typeid(*state).name() << ".\n";
        //if (this->state_ != nullptr)
        //    delete this->state_;
        this->state_ = state;
        this->state_->set_context(this);
    }
    
    void pollEvents() {
        this->state_->pollEvents();
    }
    void update() {
        this->state_->update();
    }
    void render() {
        this->state_->render();
    }

};

