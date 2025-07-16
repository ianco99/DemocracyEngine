#include "Cube.h"

namespace DemoEngine_Entities
{
    Cube::Cube(vec3 newPosition, vec3 newRotation, vec3 newScale): Entity3D(newPosition, newRotation, newScale)
    {
        vertexSize = 24 * 7;
        float vertex[] = {
            // Cara frontal
            -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, // bottom left
            0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, // bottom right
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, // top right
            -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, // top left

            // Cara trasera
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, // bottom left
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, // bottom right
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, // top right
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, // top left

            // Cara superior
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, // bottom left
            -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, // bottom right
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, // top right
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, // top left

            // Cara inferior
            -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, // bottom left
            0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, // bottom right
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, // top right
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, // top left

            // Cara derecha
            0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, // bottom left
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, // bottom right
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, // top right
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, // top left

            // Cara izquierda
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, // bottom left
            -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, // bottom right
            -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, // top right
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f // top left
        };

        indexSize = 36;
        int indices[] = {
            // Cara frontal
            0, 1, 2,
            2, 3, 0,

            // Cara trasera
            4, 5, 6,
            6, 7, 4,

            // Cara superior
            8, 9, 10,
            10, 11, 8,

            // Cara inferior
            12, 13, 14,
            14, 15, 12,

            // Cara derecha
            16, 17, 18,
            18, 19, 16,

            // Cara izquierda
            20, 21, 22,
            22, 23, 20
        };

        Renderer::GetRender()->CreateShape(VBO, VAO, EBO, vertex, indices, vertexSize, indexSize);

        hasTexture = false;
    }

    Cube::Cube(vec3 newPosition, vec3 newRotation, vec3 newScale, const char* textureName): Entity3D(
        newPosition, newRotation, newScale)
    {
        vertexSize = 24 * 12;
        float vertex[] = {
            //position-normal-color-uv
            //xyz-xyz-rgba-uv

            // Cara frontal
            -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 0.0f, // bottom left
            0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 0.0f, // bottom right
            0.5f, 0.5f, 0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 1.0f, // top right
            -0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f, // top left

            // Cara trasera
            -0.5f, -0.5f, -0.5f,     0.0f, 0.0f, -1.0f,     1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 0.0f, // bottom left
            0.5f, -0.5f, -0.5f,      0.0f, 0.0f, -1.0f,     1.0f, 1.0f, 1.0f, 1.0f,     1.0f, 0.0f, // bottom right
            0.5f, 0.5f, -0.5f,       0.0f, 0.0f, -1.0f,     1.0f, 1.0f, 1.0f, 1.0f,     1.0f, 1.0f, // top right
            -0.5f, 0.5f, -0.5f,      0.0f, 0.0f, -1.0f,     1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 1.0f, // top left

            // Cara superior
            0.5f, 0.5f, 0.5f,    0.0f, 1.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,      0.0f, 0.0f, // bottom left
            -0.5f, 0.5f, 0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f,     1.0f, 0.0f, // bottom right
            -0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f,     1.0f, 1.0f, // top right
            0.5f, 0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 1.0f, // top left

            // Cara inferior
            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // bottom left
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // bottom right
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // top right
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // top left

            // Cara derecha
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // bottom left
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // bottom right
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // top right
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // top left

            // Cara izquierda
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // bottom left
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // bottom right
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // top right
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f // top left
        };

        indexSize = 36;
        int indices[] = {
            // Cara frontal
            0, 1, 2,
            2, 3, 0,

            // Cara trasera
            4, 5, 6,
            6, 7, 4,

            // Cara superior
            8, 9, 10,
            10, 11, 8,

            // Cara inferior
            12, 13, 14,
            14, 15, 12,

            // Cara derecha
            16, 17, 18,
            18, 19, 16,

            // Cara izquierda
            20, 21, 22,
            22, 23, 20
        };

        Renderer::GetRender()->CreateSprite(VBO, VAO, EBO, vertex, indices, vertexSize, indexSize);
        Renderer::GetRender()->BindTexture(textureName, textureId);

        hasTexture = true;
    }

    Cube::~Cube()
    {
        Renderer::GetRender()->DestroyShape(VBO, VAO, EBO);
    }

    void Cube::Draw()
    {
        if (hasTexture)
        {
            Renderer::GetRender()->DrawEntity3D(VAO, indexSize, color, model, textureId, material);
        }
        else
        {
            Renderer::GetRender()->DrawEntity2D(VAO, model, color, indexSize);
        }
    }
}