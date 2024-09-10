#include "Triangle.h"

namespace DemoEngine_Entities
{
	Triangle::Triangle() : Shape()
	{
		int vertexSize = 9;
		float vertex[] = {
			//position              color
			 0.0f,  0.5f, 0.0f,		//0.0f, 0.0f, 1.0f  //top
			-0.5f, -0.5f, 0.0f,		//1.0f, 0.0f, 0.0f, //botton right
			 0.5f, -0.5f, 0.0f,		//0.0f, 1.0f, 0.0f, //botton left
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