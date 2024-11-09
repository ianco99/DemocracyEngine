#include "Timer.h"

namespace DemoEngine_Animations
{
	float Timer::deltaTime = 0;
	double Timer::lastDeltaTime = glfwGetTime();

	Timer::Timer()
	{
		lastDeltaTime = 0;
	}

	Timer::~Timer()
	{

	}

	void Timer::Update(float currentTime)
	{
		deltaTime = currentTime - lastDeltaTime;
		lastDeltaTime = currentTime;
	}

	float Timer::GetDeltaTime()
	{
		return deltaTime;
	}
}