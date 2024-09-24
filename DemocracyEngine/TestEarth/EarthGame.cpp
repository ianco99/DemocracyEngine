#include "EarthGame.h"


EarthGame::EarthGame()
{

}

EarthGame::~EarthGame()
{
}

void EarthGame::Init()
{
	pTposition = vec3{ 900, 720 / 4, 0 };
	pTscale = vec3(200, 100, 1);
	pTrotation = vec3(0, 0, 0);
	pTcolor = vec4{ 1,0,1,1 };


	yTposition = vec3{ 1024 / 8, 600, 0 };
	yTscale = vec3{ 200, 100, 1 };
	yTrotation = vec3{ 0, 0, 0 };
	yTcolor = vec4{ 1, 1, 0, 1 };

	yellowTriangle = new DemoEngine_Entities::Triangle(yTposition, yTrotation, yTscale);
	yellowTriangle->setColor(yTcolor);

	pinkTriangle = new DemoEngine_Entities::Triangle(pTposition, pTrotation, pTscale);
	pinkTriangle->setColor(pTcolor);
}

void EarthGame::Update()
{
	yellowTriangle->Translate(vec3(0,-1,0));
	yellowTriangle->rotateZ(2);
	yellowTriangle->Draw();
	pinkTriangle->Translate(vec3(0,1,0));
	pinkTriangle->rotateZ(-2);
	pinkTriangle->Draw();
}

void EarthGame::DeInit()
{
	delete yellowTriangle;
}