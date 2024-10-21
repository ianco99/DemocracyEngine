#pragma once
#include "Shape.h"

namespace DemoEngine_Entities
{
    class EXPORT Sprite : public Entity2D
    {
    protected:
        int width;
        int height;
        unsigned int textureId;
        
    public:
        Sprite(const char* textureName, int width, int height, vec4 rgba, vec3 newPosition, vec3 newScale, vec3 newRotation);
        ~Sprite();

        void Draw() override;
    };
}
