#include "StateMenu.hpp"

void StateMenu::pollEvents() {
	sf::Event temp;

	while (m_pWindow->pollEvent(temp))
	{
		switch (temp.type)
		{
		case sf::Event::Closed:
			this->m_pWindow->close();
			break;

		case sf::Event::KeyPressed:
			if (temp.key.code == sf::Keyboard::Escape)
				this->m_pWindow->close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				m_pMenu->moveUp();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				m_pMenu->moveDown();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				switch (m_pMenu->GetPressedItem())
				{
				case 0: 
					this->context_->TransitionTo(new StateModeSelect);
					return;
					break;

				case 1: //"CONTINUE" option

					if (StateInGame::isOpenSaveFile())
					{
						this->context_->TransitionTo(new StateInGame(true));
						return;
					}
					break;

				case 2: //"VISUAL DEMO" option
					this->context_->TransitionTo(new StateDemo);
					return;
					break;

				case 3: //"HELP" option
					this->context_->TransitionTo(new StateHelpInstruction);
					return;
					break;

				case 4: //"EXIT" option
					this->m_pWindow->close();
					return;
					break;
				}
			}
		}
	}


	return;
}

void StateMenu::update(){

}

void StateMenu::render() {
	m_pWindow->clear(sf::Color(128, 128, 128));
	m_pMenu->draw(*m_pWindow);
	this->m_pWindow->display();
}