#pragma once
#include "StateGame.hpp"
//#include "StateInGame.hpp"
//
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
//
