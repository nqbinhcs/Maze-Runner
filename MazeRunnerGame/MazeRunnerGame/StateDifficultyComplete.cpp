#include "StateDifficultyComplete.hpp"

void StateDifficultyComplete::pollEvents()
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
				this->context_->TransitionTo(new StateMenu);
				return;
			}
			break;
		}
	}

	return;
}

void StateDifficultyComplete::update(){
}

void StateDifficultyComplete::render() {
	m_pWindow->clear(sf::Color(128, 128, 128));
	//m_pLevelComplete->draw(*m_pWindow, m_Time.getRunningTimeInSec());
	m_pLevelComplete->draw(*m_pWindow, 10);
	this->m_pWindow->display();
}
