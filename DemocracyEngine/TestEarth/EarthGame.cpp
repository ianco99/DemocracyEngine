#include "EarthGame.h"


EarthGame::EarthGame()
{

}

EarthGame::~EarthGame()
{
}

void EarthGame::Init()
{
	Sposition = vec3{ 1024 / 2, 720 / 2, 0 };
	Sscale = vec3{ 200, 200, 1 };
	Srotation = vec3{ 0, 0, 0 };
	Scolor = vec4{ 0, 0, 0, 1 };

	Tposition = vec3{ 1024 / 4, 720 / 4, 0 };
	Tscale = vec3{ 200, 100, 1 };
	Trotation = vec3{ 0, 0, 0 };
	Tcolor = vec4{ 0, 0, 1, 1 };

	square = new DemoEngine_Entities::Square(Sposition, Srotation, Sscale);
	square->setColor(Scolor);

	triangle = new DemoEngine_Entities::Triangle(Tposition, Trotation, Tscale);
	triangle->setColor(Tcolor);

	const char* path = "rsc/democracy.png";
	image = new DemoEngine_Entities::Sprite(path, 1024,730, Scolor, Sposition, Sscale, Srotation);

	timer = new DemoEngine_Animations::DemoTimer();
}

void EarthGame::Update()
{
	if (input->IsKeyPressed(GLFW_KEY_E))
		square->rotateZ(1);

	if(input->IsKeyReleased(GLFW_KEY_A))
		triangle->Translate(vec3(1, 0, 0));

	square->Draw();

	image->Update(timer);

	triangle->Draw();

	image->Draw();
}

void EarthGame::DeInit()
{
	delete triangle;
	delete square;
	delete image;
}