#pragma once
#include "../Tools/Export.h"

#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "../Transform.h"

using namespace  glm;

namespace DemoEngine_Entities
{
    class EXPORT Entity
    {
    protected:
        vec4 color;
        
        unsigned int VBO = 0;
        unsigned int VAO = 0;
        unsigned int EBO = 0;

        int indexSize;
        int vertexSize;

        bool isActive;

    public:
        Entity(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
        Entity(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Transform* parent);
        virtual ~Entity();
        
        virtual void Draw();

        Transform* transform;
        
        void setColor(vec4 rgba);
        vec4 GetColor() const;

        void SetActive(bool isActive);
        bool IsActive() const;
    };
}