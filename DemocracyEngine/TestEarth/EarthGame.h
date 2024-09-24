#include "BaseGame/BaseGame.h"
#include "Entities/Triangle.h"
#include "Entities/Square.h"

using namespace DemoEngine_BaseGame;

class EarthGame final : public BaseGame
{
private:
	vec3 Aposition;
	vec3 Ascale;
	vec3 Arotation;
	vec4 Acolor;

	vec3 Bposition;
	vec3 Bscale;
	vec3 Brotation;
	vec4 Bcolor;

	DemoEngine_Entities::Triangle* Atriangle;

	DemoEngine_Entities::Triangle* Btriangle;

public:
	EarthGame();
	~EarthGame();

	void Init() override;
	void Update() override;
	void DeInit() override;
};