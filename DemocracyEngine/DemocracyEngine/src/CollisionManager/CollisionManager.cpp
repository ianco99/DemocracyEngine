#include "CollisionManager.h"

namespace DemoEngine_Collisions
{
    CollisionManager::CollisionManager()
    {
    }

    CollisionManager::~CollisionManager()
    {
    }

    bool CollisionManager::CheckCollisionEntityEntity(Entity2D a, Entity2D b)
    {
        float aRight = a.transform->GetGlobalPosition().x + glm::abs(a.transform->GetLocalScale().x) / 2;
        float bLeftSide = b.transform->GetGlobalPosition().x - glm::abs(b.transform->GetLocalScale().x) / 2;
        float aLeftSide = a.transform->GetGlobalPosition().x - glm::abs(a.transform->GetLocalScale().x) / 2;
        float bRightSide = b.transform->GetGlobalPosition().x + glm::abs(b.transform->GetLocalScale().x) / 2;
        // collision x-axis?
        bool collisionX = aRight >= bLeftSide &&
            bRightSide >= aLeftSide;


        float aUpSide = a.transform->GetGlobalPosition().y + glm::abs(a.transform->GetLocalScale().y) / 2;
        float bDownSide = b.transform->GetGlobalPosition().y - glm::abs(b.transform->GetLocalScale().y) / 2;
        float bUpSide = b.transform->GetGlobalPosition().y + glm::abs(b.transform->GetLocalScale().y) / 2;
        float aDownSide = a.transform->GetGlobalPosition().y - glm::abs(a.transform->GetLocalScale().y) / 2;
        // collision y-axis?
        bool collisionY = aUpSide >= bDownSide &&
            bUpSide >= aDownSide;


        return collisionX && collisionY;
    }

    bool CollisionManager::CheckCollisionEntityTile(Entity2D a, float posX, float posY, float scaleX, float scaleY)
    {
        float aRight = a.transform->GetGlobalPosition().x + glm::abs(a.transform->GetLocalScale().x) / 2;
        float bLeftSide = posX;
        float aLeftSide = a.transform->GetGlobalPosition().x - glm::abs(a.transform->GetLocalScale().x) / 2;
        float bRightSide = posX + glm::abs(scaleX);
        
        // collision x-axis?
        bool collisionX = aRight >= bLeftSide &&
            bRightSide >= aLeftSide;
        
        float aUpSide = a.transform->GetGlobalPosition().y + glm::abs(a.transform->GetLocalScale().y) / 2;
        float bDownSide = posY;
        float bUpSide = posY + glm::abs(scaleY);
        float aDownSide = a.transform->GetGlobalPosition().y - glm::abs(a.transform->GetLocalScale().y) / 2;
        // collision y-axis?
        bool collisionY = aUpSide >= bDownSide &&
            bUpSide >= aDownSide;
        
        return collisionX && collisionY;
    }
}