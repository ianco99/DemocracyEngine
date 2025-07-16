#pragma once
#include "Entity3D.h"

namespace DemoEngine_Entities
{
    class EXPORT Cube : public Entity3D
    {
    private:
        unsigned int textureId;
        bool hasTexture = false;

    public:
        Cube(vec3 newPosition, vec3 newRotation, vec3 newScale);
        Cube(vec3 newPosition, vec3 newRotation, vec3 newScale, const char* textureName);
        ~Cube();

        void Draw() override;
    };
}