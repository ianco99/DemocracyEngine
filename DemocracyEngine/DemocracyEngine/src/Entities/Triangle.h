#pragma once
#include "Shape.h"

namespace DemoEngine_Entities
{
	class Triangle : public Shape
	{
	private:

	public:
		Triangle(vec3 newPosition, vec3 newRotation, vec3 newScale);
		~Triangle();


		void Draw() override;
	};
}
