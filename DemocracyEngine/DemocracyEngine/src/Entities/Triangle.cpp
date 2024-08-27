#include "Triangle.h"

namespace DemoEngine_Entities
{
	Triangle::Triangle() : Shape()
	{
		float vertex[] = {
			-0.5f, -0.5f, 0,
			 0.5f, -0.5f, 0,
			 0.0f,  0.5f, 0
		};

		Renderer::GetRender()->CreateShape(VBO , vertex);
	}

	Triangle::~Triangle()
	{

	}
}