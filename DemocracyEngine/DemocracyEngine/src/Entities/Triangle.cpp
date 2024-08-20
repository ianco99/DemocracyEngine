#include "Triangle.h"

namespace DemoEngine_Entities
{
	Triangle::Triangle()
	{
		float vertex[] = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.0f,  0.5f
		};

		Renderer::GetRender()->CreateShape();
	}

	Triangle::~Triangle()
	{

	}
}