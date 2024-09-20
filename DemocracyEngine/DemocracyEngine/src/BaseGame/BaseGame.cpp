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
    }

    BaseGame::~BaseGame()
    {
        delete renderer;
        delete window;
    }

    bool BaseGame::Init()
    {
        return window->GetIsCreated();
    }

    //This method will be virtual
    void BaseGame::Update()
    {
        vec3 position = vec3{1024 / 2, 720 / 2, 0};
        vec3 scale = vec3{200, 200, 1};
        vec3 rotation = vec3{0, 0, 0};
        vec4 color = vec4{0, 1, 1, 1};

        //DemoEngine_Entities::Triangle* triangle = new DemoEngine_Entities::Triangle(position, rotation, scale);
        //triangle->setColor(color);
        DemoEngine_Entities::Square* square =  new DemoEngine_Entities::Square(position, rotation, scale);
        square->setColor(color);
        
        while (!window->ShouldClose())
        {
            renderer->Update();

            //triangle->setRotationZ(rotation.z + 1);
            //triangle->Draw();

            square->setRotationZ(rotation.z + 1);
            square->Draw();

            window->Update();
        }
    }
}
