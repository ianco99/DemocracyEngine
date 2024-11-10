#include "CollisionManager.h"

namespace DemoEngine_Collisions
{
	CollisionManager::CollisionManager()
	{

	}

	CollisionManager::~CollisionManager()
	{

	}

	bool CollisionManager::CheckCollisionRecRec(Entity2D a, Entity2D b)
	{
		float aRight = a.getPosition().x + glm::abs(a.getScale().x) / 2;
		float bLeftSide = b.getPosition().x - glm::abs(b.getScale().x) / 2;
		float aLeftSide = a.getPosition().x - glm::abs(a.getScale().x) / 2;
		float bRightSide = b.getPosition().x + glm::abs(b.getScale().x) / 2;
		// collision x-axis?
		bool collisionX = aRight >= bLeftSide &&
			bRightSide >= aLeftSide;


		float aUpSide = a.getPosition().y + glm::abs(a.getScale().y) / 2;
		float bDownSide = b.getPosition().y - glm::abs(b.getScale().y) / 2;
		float bUpSide = b.getPosition().y + glm::abs(b.getScale().y) / 2;
		float aDownSide = a.getPosition().y - glm::abs(a.getScale().y) / 2;
		// collision y-axis?
		bool collisionY = aUpSide >= bDownSide &&
			bUpSide >= aDownSide;


		return collisionX && collisionY;
	}
}