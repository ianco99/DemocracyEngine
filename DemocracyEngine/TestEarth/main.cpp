#include "BaseGame/BaseGame.h"

using namespace DemoEngine_BaseGame;

int main()
{
    BaseGame* baseGame = new BaseGame();

    baseGame->Init();

    baseGame->Update();

    delete baseGame;

    return 0;
}