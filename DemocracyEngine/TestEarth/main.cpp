#include "EarthGame.h"
using namespace DemoEngine_BaseGame;

int main()
{
    EarthGame* earthGame = new EarthGame();

    earthGame->Init();
    earthGame->EngineLoop();

    delete earthGame;

    return 0;
}