#include "Camera.h"
#include <glfw3.h>
#include "glm/glm.hpp"
#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>


using namespace glm;

Camera::Camera(vec2 aspect, float maxDistance, vec3 newPosition, vec3 newRotation, vec3 newScale, CameraMode cameraMode)
    : Entity(newPosition, newRotation, newScale), aspectRatio(aspect), maxDistance(maxDistance)
{
    proyection = perspective(glm::radians(fov), aspect.x / aspect.y, 0.1f, maxDistance);

    cameraFront = vec3(0.0f, 0.0f, -1.0f);
    cameraUp = vec3(0.0f, 1.0f, 0.0f);

    view = lookAt(LocalPosition, LocalPosition + cameraFront, cameraUp);

    if (cameraMode == CameraMode::ThirdPerson)
    {
        ThirdPersonCamera = true;
    }
}

void Camera::Update()
{
    if (input != nullptr)
    {
        float deltaX, deltaY;
        input->GetMouseDelta(deltaX, deltaY);

        deltaX *= mouseSensitivity;
        deltaY *= mouseSensitivity;

        yaw += deltaX;
        pitch += deltaY;

        pitch = clamp(pitch, -89.0f, 89.0f);
        
        if (input->IsKeyPressed(GLFW_KEY_Z))
        {
            fov -= zoomSpeed;
            if (fov < 1.0f) fov = 1.0f;
        }
        if (input->IsKeyPressed(GLFW_KEY_X))
        {
            fov += zoomSpeed;
            if (fov > 45.0f) fov = 45.0f;
        }
    }

    vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = normalize(front);

    if (ThirdPersonCamera)
    {
        vec3 offset = -cameraFront * thirdPersonDistance;
        offset.y += thirdPersonHeight;

        LocalPosition = thirdPersonTarget + offset;
    }
    else
    {
        vec3 direction(0.0f);
        if (input->IsKeyPressed(GLFW_KEY_W)) direction += cameraFront;
        if (input->IsKeyPressed(GLFW_KEY_S)) direction -= cameraFront;
        if (input->IsKeyPressed(GLFW_KEY_A)) direction -= normalize(cross(cameraFront, cameraUp));
        if (input->IsKeyPressed(GLFW_KEY_D)) direction += normalize(cross(cameraFront, cameraUp));
        if (input->IsKeyPressed(GLFW_KEY_SPACE)) direction += cameraUp;
        if (input->IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) direction -= cameraUp;

        float speedMultiplier = input->IsKeyPressed(GLFW_KEY_Q) ? 5.0f : 1.0f;
        if (length(direction) > 0.0f) LocalPosition += normalize(direction) * cameraSpeed * speedMultiplier;
    }

    if (input->IsKeyPressed(GLFW_KEY_L))
    {
        ThirdPersonCamera = !ThirdPersonCamera;
        CameraMode newState = ThirdPersonCamera ? CameraMode::FirstPerson : CameraMode::ThirdPerson;
        SetCameraMode(newState);
    }

    proyection = perspective(glm::radians(fov), aspectRatio.x / aspectRatio.y, 0.1f, maxDistance);
    view = lookAt(LocalPosition, LocalPosition + cameraFront, cameraUp);
}

vec3 Camera::GetCameraPosition() const { return LocalPosition; }
vec3 Camera::GetCameraFoward() const { return cameraFront; }
vec3 Camera::GetCameraRight() const { return normalize(cross(cameraFront, vec3(0.0f, 1.0f, 0.0f))); }
mat4x4 Camera::GetCameraProyection() const { return proyection; }
mat4x4 Camera::GetCameraView() const { return view; }

void Camera::SetCameraPosition(vec3 NewPosition)
{
    NewPosition.z = -NewPosition.z;
    LocalPosition = NewPosition;
}

void Camera::TranslateCamera(vec3 dir)
{
    dir.z = -dir.z;
    LocalPosition += dir;
}

void Camera::RotateCamera(vec3 newRotation)
{
    LocalRotation = newRotation;

    float yawRad = radians(LocalRotation.y);
    float pitchRad = radians(LocalRotation.x);
    float roll = radians(LocalRotation.z);

    vec3 front;
    front.x = cos(yawRad) * cos(pitchRad);
    front.y = sin(pitchRad);
    front.z = sin(yawRad) * cos(pitchRad);
    cameraFront = glm::normalize(front);

    vec3 right = glm::normalize(glm::cross(cameraFront, vec3(0.0f, 1.0f, 0.0f)));
    cameraUp = glm::normalize(glm::rotate(mat4(1.0f), roll, cameraFront) * vec4(0.0f, 1.0f, 0.0f, 1.0f));
}

void Camera::SetCameraMode(CameraMode newMode)
{
    mode = newMode;
}

void Camera::SetCameraTarget(vec3 newTarget)
{
    thirdPersonTarget = newTarget;
}

void Camera::SetInput(Input* newInput)
{
    input = newInput;
}