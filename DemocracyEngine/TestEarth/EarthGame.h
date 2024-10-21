#include "BaseGame/BaseGame.h"
#include "Entities/Sprite.h"
#include "Entities/Triangle.h"
#include "Entities/Square.h"

using namespace DemoEngine_BaseGame;

class EarthGame final : public BaseGame
{
private:
	vec3 Sposition;
	vec3 Sscale;
	vec3 Srotation;
	vec4 Scolor;

	vec3 Tposition;
	vec3 Tscale;
	vec3 Trotation;
	vec4 Tcolor;

	DemoEngine_Entities::Square* square;

	DemoEngine_Entities::Triangle* triangle;

	DemoEngine_Entities::Sprite* image;

public:
	EarthGame();
	~EarthGame();

	void Init() override;
	void Update() override;
	void DeInit() override;
};