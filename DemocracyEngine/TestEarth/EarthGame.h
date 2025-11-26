#include "BaseGame/BaseGame.h"
#include "Entities/Sprite.h"
#include "CollisionManager/CollisionManager.h"
#include "Entities/Cube.h"
#include "Entities/Model3D.h"
#include "Scene/Scene.h"

using namespace DemoEngine_BaseGame;
using namespace DemoEngine_Entities;
using namespace DemoEngine_Collisions;

class EarthGame final : public BaseGame
{
private:
	vec3 Kposition;
	vec3 Kscale;
	vec3 Krotation;
	vec4 Kcolor;

	vec3 lastPlayerPos;
	Scene* testScene = nullptr;

	Model3D* shield;
	Model3D* bike;
	Model3D* mSword;
	Model3D* cake;
	
	Cube* pCube;
	Cube* floor;
	Cube* wall1;
	Cube* wall2;
	Cube* wall3;
	Cube* wall4;
	Cube* Top;
	
	Animation* idleAnim;
	Animation* walkAnim;

	Animation* ballAnim;

	Sprite* knuckles;

	DemoEngine_Animations::DemoTimer* timer;

	Transform* wheelFront = nullptr;
	Transform* wheelBack = nullptr;

	float playerSpeed = 5;
	
public:
	EarthGame();
	~EarthGame();

	void Init() override;
	void Update() override;
	void DeInit() override;
};