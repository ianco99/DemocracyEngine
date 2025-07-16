#pragma once
#include "Entity.h"
#include "../Render/Material.h"
#include "../Render/Renderer.h"

using namespace DemoEngine_Renderer;

namespace DemoEngine_Entities
{
    class EXPORT Entity3D : public Entity
    {
    protected:
        Material material;

    public:
        Entity3D(vec3 newPosition, vec3 newRotation, vec3 newScale);
        Entity3D(Material material, vec3 newPosition, vec3 newRotation, vec3 newScale);
        ~Entity3D();
        void setMaterial(Material material);
    };
}