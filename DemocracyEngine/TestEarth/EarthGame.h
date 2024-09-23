#include "BaseGame/BaseGame.h"
#include "Entities/Triangle.h"
#include "Entities/Square.h"

using namespace DemoEngine_BaseGame;

class EarthGame final : public BaseGame
{
private:
	vec3 position;
	vec3 scale;
	vec3 rotation;
	vec4 color;

	DemoEngine_Entities::Square* square;

public:
	EarthGame();
	~EarthGame();

	void Init() override;
	void Update() override;
	void DeInit() override;
};