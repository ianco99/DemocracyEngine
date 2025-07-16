#pragma once
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

	protected:
		Input* input;

	public:
		BaseGame();
		~BaseGame();

		virtual void Init();
		virtual void Update();
		virtual void DeInit();

		void EngineLoop();

		Camera* MainCamera;
		LightManager* lightManager;
	};
}