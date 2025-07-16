#include "BaseGame.h"

#include "../Entities/Square.h"
#include "../Tools/DemoTimer.h"

using namespace DemoEngine_Window;
using namespace DemoEngine_Renderer;
using namespace DemoEngine_Animations;

namespace DemoEngine_BaseGame
{
    BaseGame::BaseGame()
    {
        vec2 windowXY;
        windowXY.x = 1024;
        windowXY.y = 720;

        MainCamera = new Camera(windowXY, 20000.0f, {0,0,0}, {0,-90,0}, {1,1,1}, CameraMode::FirstPerson);
        MainCamera->setPosition(vec3{0,0,0});
        lightManager = new LightManager();
		
        window = new Window(windowXY.x, windowXY.y, "Democracy Engine");
        renderer = new Renderer(windowXY, MainCamera, lightManager);
        input = new Input(window);
        MainCamera->SetInput(input);

		
        Init();
    }

    BaseGame::~BaseGame()
    {
        delete renderer;
        delete window;
        delete input;
        delete lightManager;
    }

    void BaseGame::EngineLoop()
    {

        while (!window->ShouldClose())
        {
            DemoTimer::Update(glfwGetTime());
            MainCamera->Update();
            renderer->Update();
            input->Update();
			
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