#include "BaseGame.h"

#include "../Entities/Triangle.h"
#include "../Entities/Square.h"
#include "../Tools/DemoTimer.h"

using namespace DemoEngine_Window;
using namespace DemoEngine_Renderer;
using namespace DemoEngine_Animations;

namespace DemoEngine_BaseGame
{
    BaseGame::BaseGame()
    {
        window = new Window(1024, 720, "Democracy Engine");
        renderer = new Renderer();
        input = new Input(window);

        Init();
    }

    BaseGame::~BaseGame()
    {
        delete renderer;
        delete window;
        delete input;
    }

    void BaseGame::EngineLoop()
    {
        
        while (!window->ShouldClose())
        {
            DemoTimer::Update(glfwGetTime());
            renderer->Update();

            Update();

            window->Update();
        }
        DeInit();
    }

    void BaseGame::Init()
    {
        
    }

    void BaseGame::Update()
    {

    }

    void BaseGame::DeInit()
    {

    }
}
