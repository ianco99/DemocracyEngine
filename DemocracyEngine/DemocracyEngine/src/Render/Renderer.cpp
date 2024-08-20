#include "Renderer.h"
#include "glew.h"
#include "glfw3.h"
#include <iostream>

namespace DemoEngine_Renderer
{
	Renderer::Renderer()
	{
		GLenum result = glewInit();

		if (result == GLEW_OK)
		{
			std::cout << "Renderer successfully created." << std::endl;
		}
		else
		{
			std::cout << "[RENDERER] Glew initialization error" << std::endl;
		}
	}

	Renderer::~Renderer()
	{
		std::cout << "Deleted renderer." << std::endl;
	}

	void Renderer::RenderFrame()
	{
		unsigned int VBO;

		float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
		};

		glGenBuffers(1, &VBO);

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
	}
}