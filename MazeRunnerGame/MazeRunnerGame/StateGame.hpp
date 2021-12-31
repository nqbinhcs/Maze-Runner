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
			window->setFramerateLimit(60);
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

//class StateMenu : public StateGame {
//public:
//    sf::RenderWindow* m_pWindow;
//private:
//    shared_ptr<Menu> m_pMenu;
//
//public:
//    StateMenu() {
//        this->m_pWindow = SingletonRenderWindow::getInstance();
//        this->m_pMenu = std::shared_ptr<Menu>(new Menu(SCREEN_WIDTH, SCREEN_HEIGHT));
//    }
//
//public:
//    void pollEvents() override;
//
//    void update() override;
//
//    void render() override;
//};


//IN GAME


//SELECT
//class StateModeSelect : public StateGame {
//public:
//	sf::RenderWindow* m_pWindow;
//private:
//	shared_ptr<ModeGame> m_pModeGame;
//
//public:
//	StateModeSelect() {
//		this->m_pWindow = SingletonRenderWindow::getInstance();
//		this->m_pModeGame = std::shared_ptr<ModeGame>(new ModeGame(SCREEN_WIDTH, SCREEN_HEIGHT));
//	}
//
//public:
//	void pollEvents() override;
//
//	void update() override;
//
//	void render() override;
//};



class ContextGame {
   
private:
    StateGame* state_;

public:
    //static StateMenu* stateMenu_;
    //static StateInGame* stateInGame_;
    //static StateModeSelect* stateModeSelect_;

public:
    ContextGame(StateGame* state) : state_(nullptr) {
        this->TransitionTo(state);
    }
    ~ContextGame() {
        delete state_;
    }

    
    void TransitionTo(StateGame* state) {
        std::cout << "Context: Transition to " << typeid(*state).name() << ".\n";
        if (this->state_ != nullptr)
            delete this->state_;
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

