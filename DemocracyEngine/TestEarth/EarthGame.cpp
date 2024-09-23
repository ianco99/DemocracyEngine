#include "EarthGame.h"


EarthGame::EarthGame()
{

}

EarthGame::~EarthGame()
{
}

void EarthGame::Init()
{
    position = vec3{ 1024 / 2, 720 / 2, 0 };
    scale = vec3{ 200, 200, 1 };
    rotation = vec3{ 0, 0, 0 };
    color = vec4{ 0, 1, 1, 1 };

    square = new DemoEngine_Entities::Square(position, rotation, scale);
    square->setColor(color);
}

void EarthGame::Update()
{
    square->setRotationZ(rotation.z + 1);
    square->Draw();
}

void EarthGame::DeInit()
{

}