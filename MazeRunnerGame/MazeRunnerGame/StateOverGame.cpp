#include "StateOverGame.hpp"

void StateOverGame::pollEvents()
{
	sf::Event event;
	while (m_pWindow->pollEvent(event))
	{
		switch (event.type) {

		case sf::Event::Closed:
			m_pWindow->close();
			break;

		case sf::Event::KeyPressed:

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
				this->context_->TransitionTo(ContextGame::getStateMenu());
				return;
			}
			break;
		}
	}

	return;
}

void StateOverGame::update()
{
}

void StateOverGame::render()
{
	m_pWindow->clear(sf::Color(128, 128, 128));
	m_pGameOver->draw(*m_pWindow);
	this->m_pWindow->display();
}

