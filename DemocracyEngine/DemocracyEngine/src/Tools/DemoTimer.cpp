#include "DemoTimer.h"
#include "glfw3.h"

namespace DemoEngine_Animations
{
	float DemoTimer::deltaTime = 0;
	double DemoTimer::lastDeltaTime = glfwGetTime();

	DemoTimer::DemoTimer()
	{
		lastDeltaTime = 0;
	}

	DemoTimer::~DemoTimer()
	{

	}

	void DemoTimer::Update(float currentTime)
	{
		deltaTime = currentTime - lastDeltaTime;
		lastDeltaTime = currentTime;
	}

	float DemoTimer::GetDeltaTime()
	{
		return deltaTime;
	}
}