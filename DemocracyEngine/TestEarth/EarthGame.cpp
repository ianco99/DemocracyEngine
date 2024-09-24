#include "EarthGame.h"


EarthGame::EarthGame()
{

}

EarthGame::~EarthGame()
{
}

void EarthGame::Init()
{
	Aposition = vec3{ 100, 720, 0 };
	Ascale = vec3{ 200, 200, 1 };
	Arotation = vec3{ 0, 0, 0 };
	Acolor = vec4{ 1, 1, 0, 1 };

	Bposition = vec3{ 1024-100, 0, 0 };
	Bscale = vec3{ 200, 200, 1 };
	Brotation = vec3{ 0, 0, 0 };
	Bcolor = vec4{ 1, 0, 1, 1 };

	Atriangle = new DemoEngine_Entities::Triangle(Aposition, Arotation, Ascale);
	Atriangle->setColor(Acolor);

	Btriangle = new DemoEngine_Entities::Triangle(Bposition, Brotation, Bscale);
	Btriangle->setColor(Bcolor);
}

void EarthGame::Update()
{
	Atriangle->rotateZ(-1);
	Atriangle->Translate(vec3(0,-1,0));
	Atriangle->Draw();

	Btriangle->rotateZ(1);
	Btriangle->Translate(vec3(0, 1, 0));
	Btriangle->Draw();
}

void EarthGame::DeInit()
{
	delete Atriangle;
	delete Btriangle;
}