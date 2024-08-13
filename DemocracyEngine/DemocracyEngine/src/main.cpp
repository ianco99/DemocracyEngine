#include "glfw3.h"
#include "Window.h"

using namespace DemoEngine_Window;

int main(void)
{
    //ESTO ES BASE GAME
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    Window window = Window(1024, 720, "Democracy Engine");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window.GetGLFWwindow()))  //BASE GAME
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        window.SwapBuffers();

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}