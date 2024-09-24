#pragma once
#include "../Render/Renderer.h"

using namespace DemoEngine_Renderer;

namespace DemoEngine_Entities
{
    //make abstract class
    class EXPORT Entity
    {
    protected:
        mat4x4 model;
        mat4 position;
        mat4 scale;
        mat4 rotation;

        vec3 LocalPosition;
        vec3 LocalScale;
        vec3 LocalRotation;

    public:
        Entity(glm::vec3 newPosition, glm::vec3 newRotation, glm::vec3 newScale);
        ~Entity();
        virtual void Draw();

        void setPosition(glm::vec3 newPosition);
        void Translate(glm::vec3 dir);
        glm::vec3 getPosition();

        glm::vec3 getScale();
        void Scale(glm::vec3 increment);
        void setScale(glm::vec3 newScale);

        void setRotationX(float newRotationX);
        void setRotationY(float newRotationY);
        void setRotationZ(float newRotationZ);

        vec3 GetRotation();

        void rotateX(float incrementRotation);
        void rotateY(float incrementRotation);
        void rotateZ(float incrementRotation);

        void UpdateTMatrix();
    };
}
