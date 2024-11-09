#include <glfw3.h>

namespace DemoEngine_Animations
{
	class Timer
	{
	private:
		static float deltaTime;
		static double lastDeltaTime;

	public:
		Timer();
		~Timer();
		static void Update(float currentTime);
		static float GetDeltaTime();
	};
}