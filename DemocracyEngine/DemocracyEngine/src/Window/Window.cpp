#include "Window.h"

namespace DemoEngine_Window
{
    Window* Window::WindowInstance = nullptr;

    Window::Window(float width, float height, const char* windowTitle)
    {
        WindowInstance = this;

        this->width = width;
        this->height = height;
        
        /* Initialize the library */
        if (!glfwInit())
        {
            isCreated = false;
        }
        else
        {
            /* Create a windowed mode window and its OpenGL context */
            glfwWindow = glfwCreateWindow(width, height, windowTitle, NULL, NULL);

            if (!glfwWindow)
            {
                glfwTerminate();
                isCreated = false;

                //TODO: CREAR DEBUG MANAGER PARA TENER DEBUGS DE COLORES Y CON FORMATEOS Y FONTS Y FONT SIZE Y COSO
                //besos enzito
                std::cout << "Window creation could not be completed." << std::endl;
            }
            else
            {
                isCreated = true;

                InitWindow();

                std::cout << "Window has been successfully created." << std::endl;
            }
        }
    }

    Window::~Window()
    {
        TerminateWindow();
        std::cout << "Deleted window." << std::endl;
    }

    void Window::Update()
    {
        SwapBuffers();
        PollEvents();
    }

    bool Window::ShouldClose()
    {
        return glfwWindowShouldClose(glfwWindow);
    }

    void Window::InitWindow()
    {
        /* Make the window's context current */
        glfwMakeContextCurrent(glfwWindow);
    }

    void Window::SwapBuffers()
    {
        /* Swap front and back buffers */
        glfwSwapBuffers(glfwWindow);
    }

    void Window::PollEvents()
    {
        /* Poll for and process events */
        glfwPollEvents();
    }

    bool Window::GetIsCreated()
    {
        return isCreated;
    }

    float Window::GetWidth()
    {
        return width;
    }

    float Window::GetHeight()
    {
		return height;
    }

    GLFWwindow* Window::GetGLFWwindow()
    {
        return glfwWindow;
    }

    void Window::TerminateWindow()
    {
        glfwTerminate();
    }
}
