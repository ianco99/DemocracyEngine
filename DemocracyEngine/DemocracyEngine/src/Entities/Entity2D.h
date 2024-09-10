#pragma once
#include "Entity.h"

namespace DemoEngine_Entities
{
    class Entity2D : public  Entity
    {
    protected:
        unsigned int VBO = 0;
        unsigned int VAO = 0;
        unsigned int EBO = 0;

    public:
        Entity2D();
        ~Entity2D();
    };
}
