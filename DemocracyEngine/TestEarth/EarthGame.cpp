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
	Sscale = vec3{ 300, 400, 1 };
	Srotation = vec3{ 0, 0, 0 };
	Scolor = vec4{ 1, 1, 1, 0 };

	Tposition = vec3{ 1024 / 4, 720 / 4, 0 };
	Tscale = vec3{ 200, 100, 1 };
	Trotation = vec3{ 0, 0, 0 };
	Tcolor = vec4{ 0, 0, 1, 1 };

	//square = new DemoEngine_Entities::Square(Sposition, Srotation, Sscale);
	//square->setColor(Scolor);

	triangle = new DemoEngine_Entities::Triangle(Tposition, Trotation, Tscale);
	triangle->setColor(Tcolor);

	//const char* path = "rsc/democracy.png";
	//image = new DemoEngine_Entities::Sprite(path, 1024, 730, Scolor, Sposition, Sscale, Srotation);

	//const char* path = "rsc/demoDie.png";
	//image = new DemoEngine_Entities::Sprite(path, 639, 588, Scolor, Sposition, Sscale, Srotation);

	const char* path = "rsc/Sonic_Mania_Sprite_Sheet.png";
	image = new DemoEngine_Entities::Sprite(path, 1024, 730, Scolor, Sposition, Sscale, Srotation);

	anim = new Animation();
	anim->AddFrame(390, 98, 98 / 3, 43, 830, 465, 2.5f, 3);
	image->AddAnimation(anim);

	timer = new DemoEngine_Animations::DemoTimer();
}

void EarthGame::Update()
{
	if (input->IsKeyPressed(GLFW_KEY_E))
		square->rotateZ(1);

	if(input->IsKeyReleased(GLFW_KEY_A))
		triangle->Translate(vec3(1, 0, 0));

	//square->Draw();

	image->Update(timer);

	triangle->Draw();

	image->Draw();
}

void EarthGame::DeInit()
{
	delete triangle;
	//delete square;
	delete image;
	delete anim;
}