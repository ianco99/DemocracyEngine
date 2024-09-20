#include "Entity.h"

namespace DemoEngine_Entities
{
	Entity::Entity(vec3 newPosition, vec3 newRotation, vec3 newScale)
	{
		model = mat4(1);
		position = mat4(1);
		scale = mat4(1);
		rotation = mat4(1);

		setPosition(newPosition);

		setRotationX(0);
		setRotationY(0);
		setRotationZ(0);
		setScale({1,1,1});

		setRotationX(newRotation.x);
		setRotationY(newRotation.y);
		setRotationZ(newRotation.z);
		setScale(newScale);

		UpdateTMatrix();
	}

	Entity::~Entity()
	{

	}

	void Entity::Draw()
	{

	}

	
	void Entity::setPosition(vec3 newPosition)
	{
		position = mat4(1.0);
		vec3 newPositionSet = { newPosition.x, newPosition.y, newPosition.z };
		position = translate(position, newPositionSet);
		UpdateTMatrix();
	}

	vec3 Entity::getPosition()
	{
		return { position[3][0], position[3][1], position[3][2] };
	}

	void Entity::setScale(vec3 newScale)
	{
		scale = mat4(1.0f);
		scale = glm::scale(scale, vec3(newScale.x, newScale.y, 1));
		UpdateTMatrix();
	}

	vec3 Entity::getScale()
	{
		return { scale[0][0], scale[1][1], scale[2][2] };
	}

	void Entity::setRotationX(float newRotationX)
	{
		rotation = glm::rotate(rotation, radians(newRotationX), vec3(1, 0, 0));
		UpdateTMatrix();
	}

	void Entity::setRotationY(float newRotationY)
	{
		rotation = glm::rotate(rotation, radians(newRotationY), vec3(0, 1, 0));
		UpdateTMatrix();
	}

	void Entity::setRotationZ(float newRotationZ)
	{
		rotation = glm::rotate(rotation, radians(newRotationZ), vec3(0, 0, 1));
		UpdateTMatrix();
	}

	void Entity::UpdateTMatrix()
	{
		model = position * rotation * scale;
	}
}