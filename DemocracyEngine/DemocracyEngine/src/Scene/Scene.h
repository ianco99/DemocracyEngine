#pragma once
#include "../Camera/Camera.h"
#include "../Tools/Export.h"
#include <vector>

using namespace DemoEngine_Entities;
using namespace DemoEngine_Camera;

class EXPORT Scene
{
public:
    Scene();
    ~Scene();

    void AddEntity(Entity* entity);
    void Draw(Camera* camera);

private:
    std::vector<Entity*> entities;
};