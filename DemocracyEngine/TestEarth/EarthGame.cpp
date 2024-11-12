#include "EarthGame.h"


EarthGame::EarthGame()
{

}

EarthGame::~EarthGame()
{
}

void EarthGame::Init()
{
	Sposition = vec3{ 1024 / 8, 720 / 8, 0 };
	Sscale = vec3{ 100, 100, 1 };
	Srotation = vec3{ 0, 0, 0 };
	Scolor = vec4{ 1, 1, 1, 1 };

	Tposition = vec3{ 1024 / 4, 720 / 4, 0 };
	Tscale = vec3{ 100, 200, 1 };
	Trotation = vec3{ 0, 0, 0 };
	Tcolor = vec4{ 0, 0, 1, 1 };

	timer = new DemoEngine_Animations::DemoTimer();

	square = new DemoEngine_Entities::Square(Sposition, Srotation, Sscale);
	square->setColor(Scolor);

	triangle = new DemoEngine_Entities::Triangle(Tposition, Trotation, Tscale);
	triangle->setColor(Tcolor);

	//const char* path = "rsc/democracy.png";
	//image = new DemoEngine_Entities::Sprite(path, 1024, 730, Scolor, Sposition, Sscale, Srotation);

	const char* path = "rsc/Knuckles_Sprite_Sheet.png";
	image = new DemoEngine_Entities::Sprite(path, 100, 200, Scolor, Sposition, Tscale, Srotation, true);
	lastPlayerPos = vec3(1024 / 2, 720 / 2, 0);
	//const char* path = "rsc/Sonic_Mania_Sprite_Sheet.png";
	//image = new DemoEngine_Entities::Sprite(path, 1024, 730, Scolor, Sposition, Sscale, Srotation);

	idleAnim = new Animation();
	idleAnim->AddFrame(2, 434, 33, 38, 646, 473,1,1);

	walkAnim = new Animation();
	walkAnim->AddFrame(339, 388, 33, 38, 646, 473, 1, 3, 9);
	//walkAnim->AddFrame(379, 388, 33, 38, 646, 473, 1, 1);
	//walkAnim->AddFrame(459, 388, 33, 38, 646, 473, 1, 1);

	ballAnim = new Animation();
	ballAnim->AddFrame(1, 314, 31, 28, 646, 473, 1, 6, 1);

	image->AddAnimation(idleAnim);

}

void EarthGame::Update()
{
	if (input->IsKeyPressed(GLFW_KEY_S))
	{
		image->Translate(vec3(0, -1, 0));
	}
	else if (input->IsKeyPressed(GLFW_KEY_W))
	{
		image->Translate(vec3(0, 1, 0));
	}
	else if (input->IsKeyPressed(GLFW_KEY_A))
	{
		image->Translate(vec3(-1, 0, 0));
	}
	else if (input->IsKeyPressed(GLFW_KEY_D))
	{
		image->Translate(vec3(1, 0, 0));
		image->AddAnimation(walkAnim);
	}

	if (input->IsKeyPressed(GLFW_KEY_SPACE))
	{
		triangle->Translate(vec3(1, 0, 0));
		image->AddAnimation(ballAnim);
	}

	square->Draw();

	image->Update(timer);

	if (CollisionManager::CheckCollisionRecRec(*image, *square))
	{
		image->setPosition(lastPlayerPos);
	}
	else
	{
		lastPlayerPos = image->getPosition();
	}

	//triangle->Draw();

	image->Draw();
}

void EarthGame::DeInit()
{
	delete triangle;
	delete square;
	delete image;
	delete idleAnim;
}