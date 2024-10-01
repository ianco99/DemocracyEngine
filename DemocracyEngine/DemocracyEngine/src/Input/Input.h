#include "../Window/Window.h"
#include "../Tools/Export.h"

using namespace DemoEngine_Window;

namespace DemoEngine_Input
{
	class EXPORT Input
	{
	private:
		Window* window;

		int currentKey;
		int currentAction;

	public:
		Input(Window* window);
		~Input();
		
		bool IsKeyPressed(int key);
		bool IsKeyReleased(int key);
	};
}