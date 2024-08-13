#include "glfw3.h"
#include "Window.h"

using namespace DemoEngine_Window;

int main(void)
{
    //GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    Window window = Window(1024, 720, "Democracy Engine");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window.GetGLFWwindow()))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window.GetGLFWwindow());

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}