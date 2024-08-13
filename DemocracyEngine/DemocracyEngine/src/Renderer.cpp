#include <iostream>
#include "Renderer.h"
#include "glfw3.h"

namespace DemoEngine_Renderer
{
	Renderer::Renderer()
	{
		std::cout << "Renderer successfully created." << std::endl;
	}

	Renderer::~Renderer()
	{
		std::cout << "Deleted renderer." << std::endl;
	}

	void Renderer::RenderFrame()
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
	}
}