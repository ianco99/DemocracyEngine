#include "BaseGame/BaseGame.h"
#include "Entities/Sprite.h"
#include "Entities/Triangle.h"
#include "Entities/Square.h"
#include "CollisionManager/CollisionManager.h"

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

	Animation* idleAnim;
	Animation* walkAnim;

	Animation* ballAnim;

	Sprite* knuckles;

	DemoEngine_Animations::DemoTimer* timer;

public:
	EarthGame();
	~EarthGame();

	void Init() override;
	void Update() override;
	void DeInit() override;
};