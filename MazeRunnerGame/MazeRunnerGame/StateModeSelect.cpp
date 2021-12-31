#include "StateModeSelect.hpp"
#include "StateInGame.hpp"

void StateModeSelect::pollEvents()
{
	sf::Event event;
	while (m_pWindow->pollEvent(event))
	{
		switch (event.type) {

		case sf::Event::Closed:
			m_pWindow->close();
			break;

		case sf::Event::KeyPressed:

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				m_pModeGame->moveUp();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				m_pModeGame->moveDown(); // 
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				return;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
				//m_pModeGame->GetPressedItem() //0, 1, 2
				this->context_->TransitionTo(new StateInGame());
				return;
			}
			break;
		}
	}

	return;
}

void StateModeSelect::update(){
}

void StateModeSelect::render() {
	m_pWindow->clear(sf::Color(128, 128, 128));
	m_pModeGame->draw(*m_pWindow);
	this->m_pWindow->display();
}