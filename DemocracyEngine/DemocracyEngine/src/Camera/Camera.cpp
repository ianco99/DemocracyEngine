#include "Camera.h"
#include <glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

namespace DemoEngine_Camera
{
    Camera::Camera(vec2 aspect, float maxDistance, vec3 newPosition, vec3 newRotation, vec3 newScale, CameraMode cameraMode)
        : Entity(newPosition, newRotation, newScale),
          aspectRatio(aspect),
          maxDistance(maxDistance),
          mode(cameraMode)
    {
        pitch = newRotation.x;
        yaw = newRotation.y;

        if (cameraMode == CameraMode::ThirdPerson)
        {
            ThirdPersonCamera = true;
        }

        proyection = perspective(glm::radians(fov), aspectRatio.x / aspectRatio.y, 0.1f, maxDistance);
        view = inverse(transform->GetModelWorldMatrix());
        m_frustum.Update(proyection * view);
    }

    void Camera::Update()
    {
        if (input != nullptr)
        {
            float deltaX, deltaY;
            input->GetMouseDelta(deltaX, deltaY);

            deltaX *= mouseSensitivity;
            deltaY *= mouseSensitivity;

            yaw -= deltaX;
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

        transform->SetLocalRotation(vec3(pitch, yaw, 0.0f));

        const mat4& worldMatrix = transform->GetModelWorldMatrix();
        vec3 forward = normalize(-vec3(worldMatrix[2]));
        vec3 right = normalize(vec3(worldMatrix[0]));

        if (ThirdPersonCamera)
        {
            vec3 offset = -forward * thirdPersonDistance;
            offset.y += thirdPersonHeight;

            transform->SetLocalPosition(thirdPersonTarget + offset);
        }
        else
        {
            vec3 direction(0.0f);
            if (input->IsKeyPressed(GLFW_KEY_W)) direction += forward;
            if (input->IsKeyPressed(GLFW_KEY_S)) direction -= forward;
            if (input->IsKeyPressed(GLFW_KEY_A)) direction -= right;
            if (input->IsKeyPressed(GLFW_KEY_D)) direction += right;
            if (input->IsKeyPressed(GLFW_KEY_SPACE)) direction += vec3(0, 1, 0);
            if (input->IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) direction -= vec3(0, 1, 0);

            float speedMultiplier = input->IsKeyPressed(GLFW_KEY_Q) ? 5.0f : 1.0f;
            if (length(direction) > 0.0f)
            {
                transform->Translate(normalize(direction) * cameraSpeed * speedMultiplier);
            }
        }

        if (input && input->IsKeyPressed(GLFW_KEY_L))
        {
            ThirdPersonCamera = !ThirdPersonCamera;
            mode = ThirdPersonCamera ? CameraMode::ThirdPerson : CameraMode::FirstPerson;
        }

        proyection = perspective(glm::radians(fov), aspectRatio.x / aspectRatio.y, 0.1f, maxDistance);
        view = inverse(transform->GetModelWorldMatrix());
        m_frustum.Update(proyection * view);
    }

    vec3 Camera::GetCameraPosition() const { return transform->GetGlobalPosition(); }
    vec3 Camera::GetCameraForward() const { return normalize(-vec3(transform->GetModelWorldMatrix()[2])); }
    vec3 Camera::GetCameraRight() const { return normalize(vec3(transform->GetModelWorldMatrix()[0])); }
    mat4x4 Camera::GetCameraProyection() const { return proyection; }
    mat4x4 Camera::GetCameraView() const { return view; }

    const Frustum& Camera::GetFrustum() const
    {
        return m_frustum;
    }

    void Camera::SetCameraPosition(vec3 NewPosition)
    {
        transform->SetLocalPosition(NewPosition);
    }

    void Camera::RotateCamera(vec3 newRotation)
    {
        pitch = newRotation.x;
        yaw = newRotation.y;
        transform->SetLocalRotation(vec3(pitch, yaw, newRotation.z));
    }

    void Camera::SetCameraMode(CameraMode newMode)
    {
        mode = newMode;
        ThirdPersonCamera = (newMode == CameraMode::ThirdPerson);
    }

    void Camera::SetCameraTarget(vec3 newTarget)
    {
        thirdPersonTarget = newTarget;
    }

    void Camera::SetInput(Input* newInput)
    {
        input = newInput;
    }

    void Camera::AddBSPPlane(const glm::vec3& point, const glm::vec3& normal)
    {
        Plane p;
        p.normal = glm::normalize(normal);
        p.distance = -glm::dot(p.normal, point);
        m_bspPlanes.push_back(p);
    }
}