//#include "Game.hpp"
#include "StateGame.hpp"
#include "StateMenu.hpp"
#include "StateModeSelect.hpp"
#include "StateInGame.hpp"


sf::RenderWindow* SingletonRenderWindow::window = nullptr;

StateMenu* ContextGame::stateMenu_ = new StateMenu;
StateInGame* ContextGame::stateInGame_ = new StateInGame;
StateModeSelect* ContextGame::stateModeSelect_ = new StateModeSelect;
StateDemo* ContextGame::stateDemo_ = new StateDemo;
StateDifficultyComplete* ContextGame::stateDifficultyComplete_ = new StateDifficultyComplete;
StateOverGame* ContextGame::stateOverGame_ = new StateOverGame;
StateHelpInstruction* ContextGame::stateHelpInstruction_ = new StateHelpInstruction;
StateContinue* ContextGame::stateContinue_ = new StateContinue;

int main()
{
	srand(time(0));

	ContextGame* context = new ContextGame(new StateMenu);
	while (SingletonRenderWindow::getInstance()->isOpen())
	{
		context->pollEvents();
		context->update();
		context->render();

	}

	//clear memory
	ContextGame::makeDelete();
	

}