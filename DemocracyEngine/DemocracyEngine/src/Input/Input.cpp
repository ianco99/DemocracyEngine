#include "Input.h"

namespace DemoEngine_Input
{
	Input::Input(Window* window)
	{
		this->window = window;
	}

	Input::~Input()
	{
	}

	bool Input::IsKeyPressed(int key)
	{
		return glfwGetKey(window->GetGLFWwindow(), key) == GLFW_PRESS;
	}

	bool Input::IsKeyReleased(int key)
	{
		return glfwGetKey(window->GetGLFWwindow(), key) == GLFW_RELEASE;
	}
}
