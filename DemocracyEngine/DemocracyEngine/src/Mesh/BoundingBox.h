#pragma once
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <vector>

namespace DemoEngine_Geometry
{
    class BoundingBox
    {
    public:
        glm::vec3 min;
        glm::vec3 max;

        BoundingBox();
        BoundingBox(const glm::vec3& min, const glm::vec3& max);

        bool IsValid() const;

        void Expand(const glm::vec3& point);
        void Expand(const BoundingBox& other);

        BoundingBox Transform(const glm::mat4& matrix) const;

        static BoundingBox FromVertices(const std::vector<glm::vec3>& vertices);
        static BoundingBox MergeTransformed(const std::vector<BoundingBox>& boxes, const std::vector<glm::mat4>& transforms);

        void GetCorners(glm::vec3 outCorners[8]) const;
    };
}