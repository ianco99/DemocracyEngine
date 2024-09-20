#pragma once
#include "Shape.h"

namespace DemoEngine_Entities
{
    class Square : public Shape
    {
    private:

    public:
        Square(vec3 newPosition, vec3 newRotation, vec3 newScale);
        ~Square();


        void Draw() override;
    };
}
