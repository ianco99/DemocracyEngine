#pragma once
#include "../Render/Renderer.h"

using namespace DemoEngine_Renderer;

namespace DemoEngine_Entities
{
    //make abstract class
    class Entity
    {
    protected:
        mat4x4 model;
        mat4 position;
        mat4 scale;
        mat4 rotation;

        vec3 newPosition;
        vec3 newScale;
        vec3 newRotation;

    public:
        Entity(glm::vec3 newPosition, glm::vec3 newRotation, glm::vec3 newScale);
        ~Entity();
        virtual void Draw();

        void setPosition(glm::vec3 newPosition);
        glm::vec3 getPosition();

        glm::vec3 getScale();
        void setScale(glm::vec3 newScale);

        void setRotationX(float newRotationX);
        void setRotationY(float newRotationY);
        void setRotationZ(float newRotationZ);

        void UpdateTMatrix();
    };
}
