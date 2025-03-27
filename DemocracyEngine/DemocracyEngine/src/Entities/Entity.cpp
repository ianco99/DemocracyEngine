#include "Entity.h"

namespace DemoEngine_Entities
{
	Entity::Entity(vec3 newPosition, vec3 newRotation, vec3 newScale)
	{
		this->LocalPosition = newPosition;
		this->LocalRotation = newRotation;
		this->LocalScale = newScale;

		model = mat4(1);
		position = mat4(1);
		scale = mat4(1);
		rotation = mat4(1);

		setPosition(newPosition);

		setRotationX(0);
		setRotationY(0);
		setRotationZ(0);
		setScale({ 1,1,1 });

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
		LocalPosition = newPosition;
		UpdateTMatrix();
	}

	void Entity::Translate(glm::vec3 dir)
	{
		LocalPosition += dir;
		UpdateTMatrix();
	}

	vec3 Entity::getPosition()
	{
		return { position[3][0], position[3][1], position[3][2] };
	}

	void Entity::setScale(vec3 newScale)
	{
		LocalScale = newScale;
		UpdateTMatrix();
	}

	vec3 Entity::getScale()
	{
		return { scale[0][0], scale[1][1], scale[2][2] };
	}

	void Entity::Scale(glm::vec3 increment)
	{
		LocalScale += increment;
		UpdateTMatrix();
	}

	void Entity::setRotationX(float newRotationX)
	{
		LocalRotation.x = newRotationX;
		UpdateTMatrix();
	}

	void Entity::setRotationY(float newRotationY)
	{
		LocalRotation.y = newRotationY;
		UpdateTMatrix();
	}

	void Entity::setRotationZ(float newRotationZ)
	{
		LocalRotation.z = newRotationZ;
		UpdateTMatrix();
	}

	vec3 Entity::GetRotation()
	{
		return LocalRotation;
	}

	void Entity::rotateX(float incrementRotation)
	{
		LocalRotation.x += incrementRotation;
		UpdateTMatrix();
	}

	void Entity::rotateY(float incrementRotation)
	{
		LocalRotation.y += incrementRotation;
		UpdateTMatrix();
	}

	void Entity::rotateZ(float incrementRotation)
	{
		LocalRotation.z += incrementRotation;
		UpdateTMatrix();
	}

	void Entity::UpdateTMatrix()
	{
		position = mat4(1.0);
		vec3 newPositionSet = { LocalPosition.x, LocalPosition.y, -LocalPosition.z };
		position = translate(position, newPositionSet);

		mat4 rotationX = glm::rotate(mat4(1.0), radians(LocalRotation.x), vec3(1, 0, 0));
		mat4 rotationY = glm::rotate(mat4(1.0), radians(LocalRotation.y), vec3(0, 1, 0));
		mat4 rotationZ = glm::rotate(mat4(1.0), radians(LocalRotation.z), vec3(0, 0, 1));

		rotation = rotationY * rotationX * rotationZ;


		scale = mat4(1.0f);
		scale = glm::scale(scale, vec3(LocalScale.x, LocalScale.y, LocalScale.z));

		model = position * rotation * scale;
	}
}