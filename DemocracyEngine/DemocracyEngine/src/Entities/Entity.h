#pragma once
#include "../Render/Renderer.h"

using namespace DemoEngine_Renderer;

namespace DemoEngine_Entities
{
    //make abstract class
    class Entity
    {
    private:

    public:
        Entity();
        ~Entity();
        virtual void Draw();
    };
}
