#include "BaseGame/BaseGame.h"
#include "Entities/Triangle.h"
#include "Entities/Square.h"

using namespace DemoEngine_BaseGame;

class EarthGame final : public BaseGame
{
private:
	vec3 pTposition;
	vec3 pTscale;
	vec3 pTrotation;
	vec4 pTcolor;

	vec3 yTposition;
	vec3 yTscale;
	vec3 yTrotation;
	vec4 yTcolor;

	DemoEngine_Entities::Triangle* yellowTriangle;
	DemoEngine_Entities::Triangle* pinkTriangle;

public:
	EarthGame();
	~EarthGame();

	void Init() override;
	void Update() override;
	void DeInit() override;
};