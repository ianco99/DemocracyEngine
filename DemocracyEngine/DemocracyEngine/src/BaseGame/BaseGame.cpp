#include "BaseGame.h"

#include "../Entities/Triangle.h"

using namespace DemoEngine_Window;
using namespace DemoEngine_Renderer;

namespace DemoEngine_BaseGame
{

	BaseGame::BaseGame()
	{
		window = new Window(1024, 720, "Democracy Engine");
		renderer = new Renderer();
	}

	BaseGame::~BaseGame()
	{
		delete renderer;
		delete window;
	}

	bool BaseGame::Init()
	{
		return window->GetIsCreated();
	}

	void BaseGame::Update()
	{
		DemoEngine_Entities::Triangle* triangle =  new DemoEngine_Entities::Triangle();
		/* Loop until the user closes the window */
		while (!window->ShouldClose())
		{
			renderer->Update();
			triangle->Draw();
			window->Update();
		}
	}

}