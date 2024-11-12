#pragma once
#include "Shape.h"
#include "../Animation/Animation.h"

using namespace DemoEngine_Animations;

namespace DemoEngine_Entities
{
    class EXPORT Sprite : public Entity2D
    {
    protected:
        Animation* animation;
        int currentFrame;
        int previousFrame;

        int width;
        int height;
        unsigned int textureId;

        
    public:
        Sprite(const char* textureName, int width, int height, vec4 rgba, vec3 newPosition, vec3 newScale, vec3 newRotation, bool filterModeNearest);
        ~Sprite();

        void SetUV(Frame frame);

        void AddAnimation(Animation* animation);
        void Update(DemoTimer* timer);

        void Draw() override;
    };
}
