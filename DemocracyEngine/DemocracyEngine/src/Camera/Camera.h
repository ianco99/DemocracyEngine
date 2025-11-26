#pragma once
#include "Frustum.h"
#include "../Tools/Export.h"
#include "../Input/Input.h"
#include "../Entities/Entity.h"

using namespace glm;
using namespace DemoEngine_Entities;
using namespace DemoEngine_Input;

namespace DemoEngine_Camera
{
    enum class CameraMode { FirstPerson, ThirdPerson };

    class EXPORT Camera : public Entity
    {
    private:
        Input* input = nullptr;

        mat4x4 proyection;
        mat4x4 view;
        Frustum m_frustum;
        std::vector<Plane> m_bspPlanes;

        CameraMode mode;

        vec3 thirdPersonTarget = vec3(0.0f);
        bool ThirdPersonCamera = false;
        float thirdPersonDistance = 500.0f;
        float thirdPersonHeight = 150.0f;

        float yaw;
        float pitch;
        float mouseSensitivity = 0.1f;
        float cameraSpeed = 15.0f;

        float fov = 45.0f;
        vec2 aspectRatio;
        float maxDistance;

        float zoomSpeed = 1.5f;

    public:
        Camera(vec2 aspect, float maxDistance, vec3 newPosition, vec3 newRotation, vec3 newScale, CameraMode cameraMode);

        void Update();

        vec3 GetCameraPosition() const;
        vec3 GetCameraForward() const;
        vec3 GetCameraRight() const;
        mat4x4 GetCameraProyection() const;
        mat4x4 GetCameraView() const;
        const Frustum& GetFrustum() const;

        void SetCameraPosition(vec3 NewPosition);
        void RotateCamera(vec3 newRotation);

        void SetCameraMode(CameraMode newMode);
        void SetCameraTarget(vec3 newTarget);

        void SetInput(Input* newInput);
        const std::vector<Plane>& GetBSPPlanes() const { return m_bspPlanes; }
        void AddBSPPlane(const glm::vec3& point, const glm::vec3& normal);
    };
}