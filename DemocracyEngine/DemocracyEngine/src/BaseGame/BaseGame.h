#pragma once
#include <iostream>
#include "Renderer.h"
#include "Window.h"

using namespace DemoEngine_Window;
using namespace DemoEngine_Renderer;

namespace DemoEngine_BaseGame
{
	class BaseGame
	{
	private:
		Window* window;
		Renderer* renderer;

	public:
		BaseGame();
		~BaseGame();

		bool Init();
		void Update();

	};
}