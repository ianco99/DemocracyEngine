#include "Entity.h"

namespace DemoEngine_Entities
{
	Entity::Entity(vec3 position, vec3 rotation, vec3 scale)
	{
		transform = new Transform(this, position, rotation, scale);
	}

	Entity::Entity(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Transform* parent)
	{
		transform = new Transform(this, parent);
	}

	Entity::~Entity()
	{

	}

	void Entity::Draw()
	{

	}

	void Entity::setColor(vec4 rgba)
	{
		color = rgba;
	}

	vec4 Entity::GetColor() const
	{
		return color;
	}

	void Entity::SetActive(bool isActive)
	{
		this->isActive = isActive;
	}

	bool Entity::IsActive() const
	{
		return isActive;
	}
}