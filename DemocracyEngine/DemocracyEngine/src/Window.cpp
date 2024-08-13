#include <iostream>
#include "glfw3.h"
#include "Window.h"

namespace DemoEngine_Window
{
	Window::Window(float width, float height, const char* windowTitle)
	{
		/* Create a windowed mode window and its OpenGL context */
		glfwWindow = glfwCreateWindow(width, height, windowTitle, NULL, NULL);

		if (!glfwWindow)
		{
			glfwTerminate();
			isCreated = false;

			//TODO: CREAR DEBUG MANAGER PARA TENER DEBUGS DE COLORES Y CON FORMATEOS Y FONTS Y FONT SIZE Y COSO
			//besos enzito
			std::cout << "Window creation could not be completed.";
		}
		else
		{
			isCreated = true;

			InitWindow();

			std::cout << "Window has been successfully created.";
		}
	}

	Window::~Window()
	{

	}

	void Window::InitWindow()
	{
		/* Make the window's context current */
		glfwMakeContextCurrent(glfwWindow);
	}

	bool Window::GetIsCreated()
	{
		return isCreated;
	}

	GLFWwindow* Window::GetGLFWwindow()
	{
		return glfwWindow;
	}
}