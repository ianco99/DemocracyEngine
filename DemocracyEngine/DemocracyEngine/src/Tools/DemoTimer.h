#include "../Tools/Export.h"

namespace DemoEngine_Animations
{
	class EXPORT DemoTimer
	{
	private:
		static float deltaTime;
		static double lastDeltaTime;

	public:
		DemoTimer();
		~DemoTimer();
		static void Update(float currentTime);
		static float GetDeltaTime();
	};
}