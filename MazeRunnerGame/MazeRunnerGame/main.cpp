//#include "Game.hpp"
#include "StateGame.hpp"
//#include "StateMenu.hpp"
//#include "StateModeSelect.hpp"
//#include "StateInGame.hpp"


sf::RenderWindow* SingletonRenderWindow::window = nullptr;
int StateModeSelect::pressedItem = 0;
//
//int main()
//{
//	srand(time(0));
//
//	ContextGame* context = new ContextGame(new StateMenu);
//	while (SingletonRenderWindow::getInstance()->isOpen())
//	{
//		context->pollEvents();
//		context->update();
//		context->render();
//
//	}
//
//	//clear memory
//	
//
//}

#include "Demo.hpp"
//VGIT
//using namespace sf;

int main()
{
	srand(time(0));

	//Khởi tạo game
	StateDemo demo;
	Clock clock;
	float timer = 0, delay = 0.1;

	while (demo.running())
	{
		//game.m_pWindow->draw(b);
		//game.m_pWindow->display();
		demo.update();
		demo.render();//*/
	}

	return 0;
}