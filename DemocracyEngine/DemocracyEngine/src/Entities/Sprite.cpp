#include "Sprite.h"

namespace DemoEngine_Entities
{
    Sprite::Sprite(const char* textureName, int width, int height, vec4 rgba, vec3 newPosition,
                   vec3 newScale, vec3 newRotation) : Entity2D(newPosition, newRotation, newScale)
    {
        this->width = width;
        this->height = height;

        vertexSize = 36;
        float vertex[] = {
            // positions		    // colors					// texture coords
            0.5f, 0.5f, 0.0f,       1.0f, 1.0f, 1.0f, 1.0f,     1.0f, 1.0f,   // top right
            0.5f, -0.5f, 0.0f,      1.0f, 1.0f, 1.0f, 1.0f,	    1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f, 1.0f,	    0.0f, 0.0f,   // bottom left
            -0.5f, 0.5f, 0.0f,      1.0f, 1.0f, 1.0f, 1.0f,	    0.0f, 1.0f    // top left 
       };

        indexSize = 6;
        int indices[] = 
        {
            0, 1, 3,
            1, 2, 3
        };

        Renderer::GetRender()->CreateSprite(VBO, VAO, EBO, vertex, indices, vertexSize, indexSize);
        Renderer::GetRender()->BindTexture(textureName, textureId);
    }

    Sprite::~Sprite()
    {
    }

    void Sprite::Draw()
    {
        Renderer::GetRender()->DrawTexture(VAO, indexSize, color, model, textureId);
    }
}
