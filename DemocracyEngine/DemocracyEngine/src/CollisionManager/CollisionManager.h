#pragma once
#include "../Tools/Export.h"
#include "../Entities/Entity2D.h"

using namespace DemoEngine_Entities;

namespace DemoEngine_Collisions
{
	class EXPORT CollisionManager
	{
	private:

	public:
		CollisionManager();
		~CollisionManager();

		static bool CheckCollisionRecRec(Entity2D entityOne, Entity2D entityTwo);
	};
}
