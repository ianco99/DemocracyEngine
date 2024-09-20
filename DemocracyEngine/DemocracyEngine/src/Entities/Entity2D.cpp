#include "Entity2D.h"

namespace DemoEngine_Entities
{
	Entity2D::Entity2D(vec3 newPosition, vec3 newRotation, vec3 newScale): Entity(newPosition, newRotation, newScale)
	{
	}

	Entity2D::~Entity2D()
	{

	}

	void Entity2D::setColor(vec4 rgba)
	{
		color = rgba;
	}

	vec4 Entity2D::getColor()
	{
		return color;
	}
}
