#pragma once
#include "glfw3.h"
#include "../Tools/Export.h"
#include <iostream>

namespace DemoEngine_Window
{
	class EXPORT Window
	{
	private:
		GLFWwindow* glfwWindow;
		bool isCreated = false;

		void InitWindow();
		void TerminateWindow();
		void PollEvents();
		void SwapBuffers();

	public:
		float width;
		float height;
		
		Window(float width, float height, const char* windowTitle);
		~Window();

		static Window* GetWindow();
		static Window* WindowInstance;
		
		bool ShouldClose();
		bool GetIsCreated();
		GLFWwindow* GetGLFWwindow();
		void Update();

	};
}