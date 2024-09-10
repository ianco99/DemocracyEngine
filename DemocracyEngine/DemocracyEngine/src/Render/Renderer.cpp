#include "Renderer.h"
#include "Shader.h"
#include "glew.h"
#include "glfw3.h"
#include <iostream>

namespace DemoEngine_Renderer
{
    Renderer* Renderer::RendererInstance = nullptr;

    Renderer::Renderer()
    {
        RendererInstance = this;

        GLenum result = glewInit();

        if (result == GLEW_OK)
        {
            std::cout << "Renderer successfully created." << std::endl;
        }
        else
        {
            std::cout << "[RENDERER] Glew initialization error" << std::endl;
        }

        const char* vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";
        const char* fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
            "}\n\0";

       
        Shader* a = new Shader();
        shader = a->CreateShader(vertexShaderSource, fragmentShaderSource);
        delete a;
    }

    Renderer::~Renderer()
    {
        std::cout << "Deleted renderer." << std::endl;
    }

    void Renderer::Update()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::CreateShape(unsigned int& VBO, unsigned int& VAO, unsigned int& EBO, float* positions, int* indexs, int positionsSize, int indexSize)
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positionsSize, positions, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indexSize, indexs, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        std::cout << "Create new Shape." << std::endl;
    }

    void Renderer::DestroyShape(unsigned int& VBO, unsigned int& VAO, unsigned int& EBO)
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        std::cout << "Delete Shape." << std::endl;
    }

    void Renderer::DrawShape(unsigned int& VAO)
    {
        glUseProgram(shader);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    }

    Renderer* Renderer::GetRender()
    {
        return RendererInstance;
    }
}
