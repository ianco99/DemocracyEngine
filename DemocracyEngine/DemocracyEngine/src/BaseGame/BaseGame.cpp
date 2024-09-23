#include "BaseGame.h"

#include "../Entities/Triangle.h"
#include "../Entities/Square.h"

using namespace DemoEngine_Window;
using namespace DemoEngine_Renderer;

namespace DemoEngine_BaseGame
{
    BaseGame::BaseGame()
    {
        window = new Window(1024, 720, "Democracy Engine");
        renderer = new Renderer();

        Init();
    }

    BaseGame::~BaseGame()
    {
        delete renderer;
        delete window;
    }

    void BaseGame::EngineLoop()
    {
        
        while (!window->ShouldClose())
        {
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
