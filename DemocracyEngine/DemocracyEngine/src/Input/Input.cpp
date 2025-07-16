#include "Input.h"
#include <glfw3.h>

namespace DemoEngine_Window
{
    class Window;
}

namespace DemoEngine_Input
{
    Input::Input(DemoEngine_Window::Window* window)
    {
        this->window = window;
    }

    Input::~Input()
    {
    }

    void Input::Update()
    {
        static bool wasEscapePressed = false;
        bool isEscapePressed = IsKeyPressed(GLFW_KEY_ESCAPE);

        if (isEscapePressed && !wasEscapePressed)
        {
            ShowMouse = !ShowMouse;

            if (ShowMouse)
            {
                glfwSetInputMode(window->GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
            else
            {
                glfwSetInputMode(window->GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
        }

        wasEscapePressed = isEscapePressed;
    }

    bool Input::IsKeyPressed(int key)
    {
        return glfwGetKey(window->GetGLFWwindow(), key) == GLFW_PRESS;
    }

    bool Input::IsKeyReleased(int key)
    {
        return glfwGetKey(window->GetGLFWwindow(), key) == GLFW_RELEASE;
    }

    void Input::GetMouseDelta(float& deltaX, float& deltaY)
    {
        double xpos, ypos;
        glfwGetCursorPos(window->GetGLFWwindow(), &xpos, &ypos);

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        deltaX = static_cast<float>(xpos - lastX);
        deltaY = static_cast<float>(lastY - ypos);

        lastX = xpos;
        lastY = ypos;
    }
}
