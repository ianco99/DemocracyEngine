#include "BoundingBox.h"
#include <limits>
#include <glm/glm.hpp>
#include <algorithm>

namespace DemoEngine_Geometry
{
    BoundingBox::BoundingBox()
        : min(std::numeric_limits<float>::max()),
          max(std::numeric_limits<float>::lowest())
    {}

    BoundingBox::BoundingBox(const glm::vec3& min, const glm::vec3& max)
        : min(min), max(max)
    {}

    bool BoundingBox::IsValid() const
    {
        return (min.x <= max.x) && (min.y <= max.y) && (min.z <= max.z);
    }

    void BoundingBox::Expand(const glm::vec3& point)
    {
        min.x = std::min(min.x, point.x);
        min.y = std::min(min.y, point.y);
        min.z = std::min(min.z, point.z);

        max.x = std::max(max.x, point.x);
        max.y = std::max(max.y, point.y);
        max.z = std::max(max.z, point.z);
    }

    void BoundingBox::Expand(const BoundingBox& other)
    {
        if (!other.IsValid()) return;
        Expand(other.min);
        Expand(other.max);
    }

    BoundingBox BoundingBox::Transform(const glm::mat4& matrix) const
    {
        if (!IsValid()) return BoundingBox();

        glm::vec3 newMin(std::numeric_limits<float>::max());
        glm::vec3 newMax(std::numeric_limits<float>::lowest());

        for (int x = 0; x <= 1; ++x)
        for (int y = 0; y <= 1; ++y)
        for (int z = 0; z <= 1; ++z)
        {
            glm::vec3 corner(
                x ? max.x : min.x,
                y ? max.y : min.y,
                z ? max.z : min.z
            );
            glm::vec4 transformed = matrix * glm::vec4(corner, 1.0f);
            newMin = glm::min(newMin, glm::vec3(transformed));
            newMax = glm::max(newMax, glm::vec3(transformed));
        }

        return BoundingBox(newMin, newMax);
    }

    BoundingBox BoundingBox::FromVertices(const std::vector<glm::vec3>& vertices)
    {
        BoundingBox box;
        for (const glm::vec3& v : vertices)
            box.Expand(v);
        return box;
    }

    BoundingBox BoundingBox::MergeTransformed(const std::vector<BoundingBox>& boxes, const std::vector<glm::mat4>& transforms)
    {
        BoundingBox merged;
        size_t count = std::min(boxes.size(), transforms.size());
        for (size_t i = 0; i < count; ++i)
        {
            BoundingBox transformedBox = boxes[i].Transform(transforms[i]);
            merged.Expand(transformedBox);
        }
        return merged;
    }

    void BoundingBox::GetCorners(glm::vec3 outCorners[8]) const
    {
        outCorners[0] = glm::vec3(min.x, min.y, min.z);
        outCorners[1] = glm::vec3(max.x, min.y, min.z);
        outCorners[2] = glm::vec3(min.x, max.y, min.z);
        outCorners[3] = glm::vec3(max.x, max.y, min.z);
        outCorners[4] = glm::vec3(min.x, min.y, max.z);
        outCorners[5] = glm::vec3(max.x, min.y, max.z);
        outCorners[6] = glm::vec3(min.x, max.y, max.z);
        outCorners[7] = glm::vec3(max.x, max.y, max.z);
    }
}