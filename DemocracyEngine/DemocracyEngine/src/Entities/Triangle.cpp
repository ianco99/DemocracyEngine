#include "Triangle.h"

namespace DemoEngine_Entities
{
	Triangle::Triangle() : Shape()
	{
		int vertexSize = 18;
		float vertex[] = {
			// positions         // colors
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
			 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
		};

		int indexSize = 3;
		int indices[] = {
		0, 1, 2
		};

		Renderer::GetRender()->CreateShape(VBO, VAO, EBO, vertex, indices, vertexSize, indexSize);
	}

	Triangle::~Triangle()
	{
		Renderer::GetRender()->DestroyShape(VBO, VAO, EBO);
	}

	void Triangle::Draw()
	{
		Renderer::GetRender()->DrawShape(VAO);
	}
}