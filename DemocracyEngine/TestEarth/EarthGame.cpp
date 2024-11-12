#include "EarthGame.h"


EarthGame::EarthGame()
{

}

EarthGame::~EarthGame()
{
}

void EarthGame::Init()
{
	Sposition = vec3{ 1024 - 1024 / 3, 720 / 2, 0 };
	Sscale = vec3{ 200, 200, 1 };
	Srotation = vec3{ 0, 0, 0 };
	Scolor = vec4{ 1, 1, 1, 1 };

	Kposition = vec3{ 1024 / 4, 720 / 4, 0 };
	Kscale = vec3{ 100, 200, 1 };
	Krotation = vec3{ 0, 0, 0 };
	Kcolor = vec4{ 0, 0, 1, 1 };

	timer = new DemoEngine_Animations::DemoTimer();

	const char* path = "rsc/Knuckles_Sprite_Sheet.png";
	knuckles = new DemoEngine_Entities::Sprite(path, 100, 200, Kcolor, Kposition, Kscale, Krotation, true);

	const char* rockPath = "rsc/Rock.jfif";
	rock = new DemoEngine_Entities::Sprite(rockPath, Sscale.x, Sscale.y, Scolor, Sposition, Sscale, Srotation, true);

	lastPlayerPos = vec3(1024 / 2, 720 / 2, 0);

	rockIdle = new Animation();
	rockIdle->AddFrame(74, 130, 83, 57, 244, 207, 1);

	rock->AddAnimation(rockIdle);

	walkAnim = new Animation();
	walkAnim->AddFrame(339, 388, 33, 38, 646, 473, 1, 3, 9);

	rockAnim = new Animation();
	rockAnim->AddFrame(426, 342, 32, 35, 646, 473, 1, 4, 3);
	rockAnim->AddFrame(532, 342, 28, 35, 646, 473, 1, 1);

	ballAnim = new Animation();
	ballAnim->AddFrame(1, 314, 31, 28, 646, 473, 1, 6, 1);

	idleAnim = new Animation();
	idleAnim->AddFrame(2, 434, 33, 38, 646, 473, 1, 1);

	knuckles->AddAnimation(idleAnim);

}

void EarthGame::Update()
{
	vec3 translation = vec3(0,0,0);

	if (input->IsKeyPressed(GLFW_KEY_S))
	{
		translation = vec3(0, -2, 0);
		knuckles->AddAnimation(walkAnim);

	}
	else if (input->IsKeyPressed(GLFW_KEY_W))
	{
		translation = vec3(0, 2, 0);
		knuckles->AddAnimation(walkAnim);

	}
	else if (input->IsKeyPressed(GLFW_KEY_A))
	{
		translation = vec3(-2, 0, 0);
		knuckles->setRotationY(-180);

		knuckles->AddAnimation(walkAnim);

	}
	else if (input->IsKeyPressed(GLFW_KEY_D))
	{
		knuckles->setRotationY(1);
		translation = vec3(2, 0, 0);
		knuckles->AddAnimation(walkAnim);
	}
	else
	{
		knuckles->AddAnimation(idleAnim);
	}

	knuckles->Translate(translation);

	if (CollisionManager::CheckCollisionRecRec(*knuckles, *rock))
	{
		//knuckles->setPosition(lastPlayerPos);
		rock->Translate(translation);
		knuckles->AddAnimation(rockAnim);
	}
	else
	{
		lastPlayerPos = knuckles->getPosition();
	}

	if (input->IsKeyPressed(GLFW_KEY_SPACE))
	{
		knuckles->AddAnimation(ballAnim);
	}

	rock->Draw();

	knuckles->Update(timer);

	rock->Update(timer);

	rock->Draw();

	knuckles->Draw();
}

void EarthGame::DeInit()
{
	delete rock;
	delete knuckles;
	delete idleAnim;
	delete walkAnim;
	delete ballAnim;
	delete rockAnim;
	delete rockIdle;
}