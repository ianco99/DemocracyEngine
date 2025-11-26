#pragma once
#include "glew.h"
#include <glm/vec3.hpp>
#include "../Tools/Export.h"

class EXPORT  Plane
{
public:
    glm::vec3 normal;
    float distance;
    Plane flipped() const { return {-normal, -distance}; }

    Plane() : normal(0.0f), distance(0.0f) {}

    Plane(glm::vec3 inNormal, glm::vec3 inPoint);


    Plane(glm::vec3 inNormal, float d);


    Plane(glm::vec3 a, glm::vec3 b, glm::vec3 c);

    bool operator==(const Plane& right) const
    {
        return this->normal == right.normal && this->distance == right.distance;
    }

    bool operator!=(const Plane& right) const
    {
        return !(*this == right);
    }


    static Plane zero();
    
    void setNormalAndPosition(glm::vec3 inNormal, glm::vec3 inPoint);
    
    void set3Points(glm::vec3 a, glm::vec3 b, glm::vec3 c);
    
    void flip();

    void translate(glm::vec3 translation);
    
    static Plane Translate(Plane plane, glm::vec3 translation);
    
    glm::vec3 closestPointOnPlane(glm::vec3 point) const;

    float getSignedDistanceToPoint(glm::vec3 point) const;

    bool getSide(glm::vec3 point) const;
    
    bool sameSide(glm::vec3 inPt0, glm::vec3 inPt1) const;
};