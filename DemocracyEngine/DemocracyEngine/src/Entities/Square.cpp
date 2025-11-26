#include "Square.h"

#include "../Render/Renderer.h"

using namespace DemoEngine_Renderer;

namespace DemoEngine_Entities
{
    Square::Square(vec3 newPosition, vec3 newRotation, vec3 newScale): Shape(newPosition, newRotation, newScale)
    {
        vertexSize = 28;
        float vertex[] = {
            // positions         // colors
            0.5f, 0.5f, 0.0f,    1.0f, 0.0f, 0.0f,1.0f, // bottom right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,1.0f, // bottom left
            -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,1.0f, // top right
            -0.5f, 0.5f, 0.0f,   0.0f, 1.0f, 1.0f,1.0f // top left
        };

        indexSize = 6;

        int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        Renderer::GetRender()->CreateShape(VBO, VAO, EBO, vertex, indices, vertexSize, indexSize);
    }


    Square::~Square()
    {
        Renderer::GetRender()->DestroyShape(VBO, VAO, EBO);
    }

    void Square::Draw()
    {
        Renderer::GetRender()->DrawEntity2D(VAO, transform->GetModelLocalMatrix(), color, indexSize);
    }
}