#include "Frustum.h"

namespace DemoEngine_Camera
{
    void Frustum::Update(const mat4& vp)
    {
        // Left
        planes[0] = { vec3(vp[0][3] + vp[0][0], vp[1][3] + vp[1][0], vp[2][3] + vp[2][0]), vp[3][3] + vp[3][0] };
        // Right
        planes[1] = { vec3(vp[0][3] - vp[0][0], vp[1][3] - vp[1][0], vp[2][3] - vp[2][0]), vp[3][3] - vp[3][0] };
        // Bottom
        planes[2] = { vec3(vp[0][3] + vp[0][1], vp[1][3] + vp[1][1], vp[2][3] + vp[2][1]), vp[3][3] + vp[3][1] };
        // Top
        planes[3] = { vec3(vp[0][3] - vp[0][1], vp[1][3] - vp[1][1], vp[2][3] - vp[2][1]), vp[3][3] - vp[3][1] };
        // Near
        planes[4] = { vec3(vp[0][3] + vp[0][2], vp[1][3] + vp[1][2], vp[2][3] + vp[2][2]), vp[3][3] + vp[3][2] };
        // Far
        planes[5] = { vec3(vp[0][3] - vp[0][2], vp[1][3] - vp[1][2], vp[2][3] - vp[2][2]), vp[3][3] - vp[3][2] };

        for (Plane& plane : planes)
        {
            float len = glm::length(plane.normal);
            plane.normal /= len;
            plane.distance /= len;
        }
    }

    bool Frustum::IsBoxVisible(const BoundingBox& box) const
    {
        for (const Plane& plane : planes)
        {
            glm::vec3 pVertex = box.min;
            if (plane.normal.x >= 0) pVertex.x = box.max.x;
            if (plane.normal.y >= 0) pVertex.y = box.max.y;
            if (plane.normal.z >= 0) pVertex.z = box.max.z;

            if (plane.getSignedDistanceToPoint(pVertex) < 0)
                return false;
        }
        return true;
    }
}