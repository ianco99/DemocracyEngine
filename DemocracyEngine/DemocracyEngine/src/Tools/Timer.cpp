#include "Timer.h"

float Timer::deltaTime = 0;
double Timer::lastDeltaTime = glfwGetTime();

Timer::Timer()
{

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