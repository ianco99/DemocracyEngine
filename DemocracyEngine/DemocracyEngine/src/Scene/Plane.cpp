#include "Plane.h"
#include <glm/detail/func_geometric.inl>

Plane::Plane(glm::vec3 inNormal, glm::vec3 inPoint)
{
    this->normal = glm::normalize(inNormal);
    this->distance = -glm::dot(this->normal, inPoint);
}

Plane::Plane(glm::vec3 inNormal, float d)
{
    this->distance = d;
    this->normal = inNormal;
}

Plane::Plane(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
    this->normal = glm::normalize(glm::cross(b - a, c - a));
    this->distance = -glm::dot(this->normal, a);
}

Plane Plane::zero()
{ return {glm::vec3(0), 0}; }

void Plane::setNormalAndPosition(glm::vec3 inNormal, glm::vec3 inPoint)
{
    this->normal = glm::normalize(inNormal);
    this->distance = -glm::dot(this->normal, inPoint);
}

void Plane::set3Points(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
    this->normal = glm::normalize(glm::cross(b - a, c - a));
    this->distance = -glm::dot(this->normal, a);
}

void Plane::translate(glm::vec3 translation)
{
    distance += glm::dot(normal, translation);
}

Plane Plane::Translate(Plane plane, glm::vec3 translation)
{
    plane.translate(translation);
    return plane;
}

glm::vec3 Plane::closestPointOnPlane(glm::vec3 point) const
{
    float pointToPlaneDistance = getSignedDistanceToPoint(point);
    return point - (normal * pointToPlaneDistance);
}

float Plane::getSignedDistanceToPoint(glm::vec3 point) const
{
    return glm::dot(normal, point) + distance;
}

bool Plane::getSide(glm::vec3 point) const
{
    return getSignedDistanceToPoint(point) > 0.0F;
}

bool Plane::sameSide(glm::vec3 inPt0, glm::vec3 inPt1) const
{
    float d0 = getSignedDistanceToPoint(inPt0);
    float d1 = getSignedDistanceToPoint(inPt1);
    return (d0 > 0.0f && d1 > 0.0f) ||
        (d0 <= 0.0f && d1 <= 0.0f);
}
void Plane::flip()
{
    this->normal = -normal;
    this->distance = -distance;
}