#include "Entity3D.h"

#include <iostream>

namespace DemoEngine_Entities
{
    Entity3D::Entity3D(vec3 newPosition, vec3 newRotation, vec3 newScale) : Entity(newPosition, newRotation, newScale)
    {
        this->material = DefaultMaterial;
    }

    Entity3D::Entity3D(Material material, vec3 newPosition, vec3 newRotation, vec3 newScale) : Entity(newPosition, newRotation, newScale)
    {
        this->material = material;
    }

    Entity3D::~Entity3D()
    {
        std::cout << "Delete Entity 3D" << '\n';
    }

    void Entity3D::setMaterial(Material material)
    {
        this->material = material;
    }
}