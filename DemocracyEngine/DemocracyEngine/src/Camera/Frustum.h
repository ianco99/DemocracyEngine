#pragma once
#include <glm/glm.hpp>
#include <array>
#include "../Mesh/BoundingBox.h"
#include "../Scene/Plane.h"

namespace DemoEngine_Camera
{
    using namespace glm;
    using namespace DemoEngine_Geometry;

    class Frustum
    {
    public:
        std::array<Plane, 6> planes;

        void Update(const mat4& viewProjectionMatrix);
        bool IsBoxVisible(const BoundingBox& box) const;
    };
}