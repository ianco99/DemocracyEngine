#pragma once
#include "Entity2D.h"

namespace DemoEngine_Entities
{
	class Shape : public Entity2D
	{
	private:

	public:
		Shape(vec3 newPosition, vec3 newRotation, vec3 newScale);
		~Shape();
		void InitShape();
	};
}
