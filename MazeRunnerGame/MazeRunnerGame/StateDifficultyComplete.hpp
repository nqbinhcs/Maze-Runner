#pragma once
//#include "StateGame.hpp"
//#include "StateMenu.hpp"
//
//class StateDifficultyComplete : public StateGame {
//public:
//	sf::RenderWindow* m_pWindow;
//private:
//	shared_ptr<LevelComplete> m_pLevelComplete;
//
//public:
//	StateDifficultyComplete() {
//		this->m_pWindow = SingletonRenderWindow::getInstance();
//		this->m_pLevelComplete = std::shared_ptr<LevelComplete>(new LevelComplete());
//	}
//
//public:
//	void pollEvents() override
//	{
//		sf::Event event;
//		while (m_pWindow->pollEvent(event))
//		{
//			switch (event.type) {
//
//			case sf::Event::Closed:
//				m_pWindow->close();
//				break;
//
//			case sf::Event::KeyPressed:
//
//				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
//					this->context_->TransitionTo(new StateMenu);
//					return;
//				}
//				break;
//			}
//		}
//
//		return;
//	}
//
//	void update() override {
//	}
//
//	void render() override {
//		m_pWindow->clear(sf::Color(128, 128, 128));
//		//m_pLevelComplete->draw(*m_pWindow, m_Time.getRunningTimeInSec());
//		m_pLevelComplete->draw(*m_pWindow, 10);
//		this->m_pWindow->display();
//	}
//};