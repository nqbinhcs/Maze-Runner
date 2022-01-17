#include "StateHelpInstruction.hpp"

void StateHelpInstruction::pollEvents()
{
	sf::Event event;
	while (m_pWindow->pollEvent(event))
	{
		switch (event.type) {

		case sf::Event::Closed:
			m_pWindow->close();
			break;

		case sf::Event::KeyPressed:

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				this->context_->TransitionTo(new StateMenu);
				return;
			}
			break;
		}
	}

	return;
}

void StateHelpInstruction::update()
{
}

void StateHelpInstruction::render()
{
	m_pWindow->clear(sf::Color(128, 128, 128));
	m_pInstruction->draw(*m_pWindow);
	this->m_pWindow->display();
}

