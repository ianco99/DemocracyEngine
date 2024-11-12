#include "EarthGame.h"


EarthGame::EarthGame()
{

}

EarthGame::~EarthGame()
{
}

void EarthGame::Init()
{
	Kposition = vec3{ 1024 / 2, 720 / 2, 0 };
	Kscale = vec3{ 150, 150, 1 };
	Krotation = vec3{ 0, 0, 0 };
	Kcolor = vec4{ 1, 1, 1, 1 };

	Rposition = vec3{ 1024 / 2 + 1024 / 4, 720 / 2, 0 };
	Rscale = vec3{ 200, 200, 1 };
	Rrotation = vec3{ 0, 0, 0 };
	Rcolor = vec4{ 0, 0, 1, 1 };

	timer = new DemoEngine_Animations::DemoTimer();


	const char* path = "rsc/Knuckles_Sprite_Sheet.png";
	Knuckles = new DemoEngine_Entities::Sprite(path, 646, 473, Kcolor, Kposition, Kscale, Krotation);
	lastPlayerPos = vec3(1024 / 2, 720 / 2, 0);

	path = "rsc/Rock.png";
	rock = new DemoEngine_Entities::Sprite(path, 244, 207, Rcolor, Rposition, Rscale, Rrotation);

	rockA = new Animation();
	rockA->AddFrame(75, 207 - 75, 100, 60, 244, 207, 1);
	rockA->AddFrame(75, 207 - 75, 100, 60, 244, 207, 1);

	rock->AddAnimation(rockA);

	idleAnim = new Animation();
	idleAnim->AddFrame(-35, 473 - 40, 35, 40, 646, 473, 1, 2);

	walkAnim = new Animation();
	walkAnim->AddFrame(36, 473 - (40 * 2) - 2, 42, 40, 646, 473, 1, 7);

	spinAttackAnim = new Animation();
	spinAttackAnim->AddFrame(-31, 473 - (41 * 4), 32, 35, 646, 473, 1, 5);

	pushAnim = new Animation();
	pushAnim->AddFrame(424, 470 - (43 * 3), 36, 42, 646, 473, 1, 3);

}

void EarthGame::Update()
{
	if (input->IsKeyPressed(GLFW_KEY_S))
	{
		Knuckles->Translate(vec3(0, -speed, 0));
		if (CollisionManager::CheckCollisionRecRec(*Knuckles, *rock))
		{
			rock->Translate(vec3(0, -speed, 0));
			Knuckles->AddAnimation(pushAnim);
		}
		else
		{
			Knuckles->AddAnimation(walkAnim);
		}
	}
	else if (input->IsKeyPressed(GLFW_KEY_W))
	{
		Knuckles->Translate(vec3(0, speed, 0));
		if (CollisionManager::CheckCollisionRecRec(*Knuckles, *rock))
		{
			rock->Translate(vec3(0, speed, 0));
			Knuckles->AddAnimation(pushAnim);
		}
		else
		{
			Knuckles->AddAnimation(walkAnim);
		}

	}
	else if (input->IsKeyPressed(GLFW_KEY_A))
	{
		Knuckles->Translate(vec3(-speed, 0, 0));
		Knuckles->setRotationY(180);
		if (CollisionManager::CheckCollisionRecRec(*Knuckles, *rock))
		{
			rock->Translate(vec3(-speed, 0, 0));
			Knuckles->AddAnimation(pushAnim);
		}
		else
		{
			Knuckles->AddAnimation(walkAnim);
		}
	}
	else if (input->IsKeyPressed(GLFW_KEY_D))
	{
		Knuckles->Translate(vec3(speed, 0, 0));
		Knuckles->setRotationY(0);

		if (CollisionManager::CheckCollisionRecRec(*Knuckles, *rock))
		{
			rock->Translate(vec3(speed, 0, 0));
			Knuckles->AddAnimation(pushAnim);
		}
		else
		{
			Knuckles->AddAnimation(walkAnim);
		}
	}
	else if (input->IsKeyPressed(GLFW_KEY_SPACE))
	{
		Knuckles->AddAnimation(spinAttackAnim);
	}
	else
	{
		Knuckles->AddAnimation(idleAnim);
	}

	Knuckles->Update(timer);
	rock->Update(timer);

	Knuckles->Draw();
	rock->Draw();
}

void EarthGame::DeInit()
{
	delete Knuckles;
	delete walkAnim;
	delete idleAnim;
	delete spinAttackAnim;
	delete pushAnim;
	delete rock;
	delete rockA;
	delete timer;
}