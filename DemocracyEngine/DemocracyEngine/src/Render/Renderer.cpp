#include "Renderer.h"
#include "glew.h"
#include "glfw3.h"
#include <iostream>

namespace DemoEngine_Renderer
{
	Renderer* Renderer::RendererInstance = nullptr;

	Renderer::Renderer()
	{
		RendererInstance = this;

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

	void Renderer::Update()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);



	}

	void Renderer::RenderFrame()
	{
		/* Render here */

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
	}

	void Renderer::CreateShape(unsigned int&VBO, float vertex[])
	{
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
	}

	void Renderer::DrawShape()
	{
		glDrawArrays();

	}

	Renderer* Renderer::GetRender()
	{
		return RendererInstance;
	}
}