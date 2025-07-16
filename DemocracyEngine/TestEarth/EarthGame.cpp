#include "EarthGame.h"


EarthGame::EarthGame()
{

}

EarthGame::~EarthGame()
{
}

void EarthGame::Init()
{
	Kposition = vec3{ 0,0, 10 };
	Kscale = vec3{ 20, 20, 20 };
	Krotation = vec3{ 0, 0, 0 };
	Kcolor = vec4{ 0, 0, 1, 1 };

	pCube = new Cube(Kposition, Krotation,Kscale);
	pCube->setColor({1,0,0,1});
	
	timer = new DemoEngine_Animations::DemoTimer();

	const char* path = "rsc/Knuckles_Sprite_Sheet.png";
	knuckles = new DemoEngine_Entities::Sprite(path, 646, 473, 2, 434, 33, 38, Kcolor, Kposition, Kscale, Krotation, true);

	
	walkAnim = new Animation();
	walkAnim->AddFrame(339, 388, 33, 38, 646, 473, 1, 3, 9);

	ballAnim = new Animation();
	ballAnim->AddFrame(1, 314, 31, 28, 646, 473, 1, 6, 1);

	idleAnim = new Animation();
	idleAnim->AddFrame(2, 434, 33, 38, 646, 473, 1, 1);

	knuckles->AddAnimation(walkAnim);
}

void EarthGame::Update()
{
	vec3 translation = vec3(0,0,0);

	if (input->IsKeyPressed(GLFW_KEY_S))
	{
		translation = vec3(0, 0, -1);
		knuckles->AddAnimation(walkAnim);

	}
	else if (input->IsKeyPressed(GLFW_KEY_W))
	{
		translation = vec3(0, 0, 1);
		knuckles->AddAnimation(walkAnim);

	}
	else if (input->IsKeyPressed(GLFW_KEY_A))
	{
		translation = vec3(-1, 0, 0);
		knuckles->setRotationY(-180);

		knuckles->AddAnimation(walkAnim);

	}
	else if (input->IsKeyPressed(GLFW_KEY_D))
	{
		knuckles->setRotationY(1);
		translation = vec3(1, 0, 0);
		knuckles->AddAnimation(walkAnim);
	}
	else if (input->IsKeyPressed(GLFW_KEY_E))
	{
		translation = vec3(0, 1, 0);
		knuckles->AddAnimation(walkAnim);
	}
	else if (input->IsKeyPressed(GLFW_KEY_R))
	{
		translation = vec3(0, -1, 0);
		knuckles->AddAnimation(walkAnim);
	}
	else
	{
		knuckles->AddAnimation(idleAnim);
	}

	if (input->IsKeyPressed(GLFW_KEY_SPACE))
	{
		knuckles->AddAnimation(ballAnim);
	}

	knuckles->Translate(translation);

	knuckles->Update(timer);

	//knuckles->Draw();
	pCube->Draw();
}

void EarthGame::DeInit()
{
	delete knuckles;
	delete idleAnim;
	delete walkAnim;
	delete ballAnim;
	
	delete pCube;
}