#include "glfw3.h"
#include "Window.h"
#include "Renderer.h"

using namespace DemoEngine_Window;
using namespace DemoEngine_Renderer;

int main(void)
{
    Window* window = new Window(1024, 720, "Democracy Engine");
    Renderer* renderer = new Renderer();
    
    //ESTO ES BASE GAME
    if (!window->GetIsCreated())
        return -1;
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window->GetGLFWwindow()))  //BASE GAME
    {
        renderer->RenderFrame();

        window->SwapBuffers();

        window->PollEvents();
    }

    delete renderer;
    delete window;

    return 0;
}