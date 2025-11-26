#include "glew.h"
#include "Scene.h"
#include "Plane.h"
#include "../Entities/Model3D.h"

Scene::Scene() {}

Scene::~Scene()
{
    for (Entity* entity : entities)
    {
        delete entity;
    }
}

void Scene::AddEntity(Entity* entity)
{
    entities.push_back(entity);
}

void Scene::Draw(Camera* camera)
{
    if (!camera) return;

    vector<bool> cameraSides;
    vector<Plane> bspPlanes = camera->GetBSPPlanes();
    for (const Plane& plane : bspPlanes)
    {
        cameraSides.push_back(plane.getSide(camera->GetCameraPosition()));
    }

    for (Entity* entity : entities)
    {
        Model3D* model = dynamic_cast<Model3D*>(entity);
        if (model)
        {
            model->DrawOccluded(bspPlanes, cameraSides);
        }
        else
        {
            entity->Draw();
        }
    }
}