#pragma once
#include "../Tools/Export.h"

#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

using namespace  glm;

namespace DemoEngine_Entities
{
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

        vec4 color;
        
        unsigned int VBO = 0;
        unsigned int VAO = 0;
        unsigned int EBO = 0;

        int indexSize;
        int vertexSize;

    public:
        Entity(glm::vec3 newPosition, glm::vec3 newRotation, glm::vec3 newScale);
        virtual ~Entity();
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

        void setColor(vec4 rgba);
        vec4 getColor();
    };
}