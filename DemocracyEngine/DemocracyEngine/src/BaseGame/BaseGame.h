#pragma once
#include <iostream>
#include "../src/Tools/Export.h"
#include "../Render/Renderer.h"
#include "../Window/Window.h"

using namespace DemoEngine_Window;
using namespace DemoEngine_Renderer;

namespace DemoEngine_BaseGame
{
	class EXPORT BaseGame
	{
	private:
		Window* window;
		Renderer* renderer;

	public:
		BaseGame();
		~BaseGame();

		virtual void Init();
		virtual void Update();
		virtual void DeInit();
		//possible virtual Draw method in which all draw methods must be called
		void EngineLoop();
	};
}