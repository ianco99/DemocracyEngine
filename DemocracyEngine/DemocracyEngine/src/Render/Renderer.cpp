#include "Renderer.h"
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

    void Renderer::CreateShape(unsigned int& VBO, float vertex[])
    {
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
        glEnableVertexAttribArray(0);
    }

    void Renderer::DrawShape()
    {
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    Renderer* Renderer::GetRender()
    {
        return RendererInstance;
    }
}
