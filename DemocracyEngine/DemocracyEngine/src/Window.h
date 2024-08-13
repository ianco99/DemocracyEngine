#pragma once

namespace DemoEngine_Window
{
	class Window
	{
	private:
		GLFWwindow* glfwWindow;
		bool isCreated = false;

		void InitWindow();
		void TerminateWindow();

	public:
		Window(float width, float height, const char* windowTitle);
		~Window();
		

		bool GetIsCreated();
		GLFWwindow* GetGLFWwindow();
		void SwapBuffers();
		void PollEvents();

	};
}