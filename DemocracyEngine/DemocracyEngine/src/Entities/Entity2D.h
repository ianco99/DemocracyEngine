#pragma once
#include "Entity.h"

namespace DemoEngine_Entities
{
    class EXPORT Entity2D : public Entity
    {
    protected:
        vec4 color;
        
        unsigned int VBO = 0;
        unsigned int VAO = 0;
        unsigned int EBO = 0;

        int indexSize;
        int vertexSize;

    public:
        Entity2D(vec3 newPosition, vec3 newRotation, vec3 newScale);
        ~Entity2D();
        
        void setColor(vec4 rgba);
        vec4 getColor();
    };
}
