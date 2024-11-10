#include "CollisionManager.h"

namespace DemoEngine_Collisions
{
	CollisionManager::CollisionManager()
	{

	}

	CollisionManager::~CollisionManager()
	{

	}

	bool CollisionManager::CheckCollisionRecRec(Entity2D* entityOne, Entity2D* entityTwo)
	{
		bool collisionX = entityOne->getPosition().x + entityOne->getScale().x >= entityTwo->getPosition().x &&
						  entityTwo->getPosition().x + entityTwo->getScale().x >= entityOne->getPosition().x;

		bool collisionY = entityOne->getPosition().y + entityOne->getScale().y >= entityTwo->getPosition().y &&
						  entityTwo->getPosition().y + entityTwo->getScale().y >= entityOne->getPosition().y;

		if (collisionX && collisionY)
		{
			cout << "Sprite :" << entityOne->getScale().x << ", " << entityOne->getScale().y << endl;
			cout << "Box :" << entityTwo->getScale().x << ", " << entityTwo->getScale().y << endl;
		}

		return collisionX && collisionY;
	}
}