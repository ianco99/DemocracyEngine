#include "Camera.h"

namespace DemoEngine_Camera
{
	Camera::Camera(float fov, float near, float far, float height, float width, float up, float right, float forward, glm::vec3 newPosition, glm::vec3 newRotation, glm::vec3 newScale) : Entity(newPosition, newRotation, newScale)
	{
		this->fov = fov;
		this->near = near;
		this->far = far;
		this->height = height;
		this->width = width;
		this->up = up;
		this->right = right;
		this->forward = forward;
	}

	Camera::Camera(glm::vec3 newPosition, glm::vec3 newRotation, glm::vec3 newScale) : Entity(newPosition, newRotation, newScale)
	{

	}

	Camera::~Camera()
	{

	}

	void Camera::Draw()
	{
		std::cout << "Cannot draw camera." << std::endl;
	}
}