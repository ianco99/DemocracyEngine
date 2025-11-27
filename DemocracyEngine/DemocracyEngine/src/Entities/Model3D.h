#pragma once
#include "Entity3D.h"
#include "../Mesh/BasicMesh.h"
#include "../Mesh/BoundingBox.h"
#include "../Camera/Frustum.h"
#include <vector>
#include <string>
#include <memory>
#include <limits>

using namespace std;
using namespace DemoEngine_Geometry;
using namespace DemoEngine_Importer;

namespace DemoEngine_Entities
{
    class EXPORT Model3D : public Entity3D
    {
    public:
        Model3D(vec3 newPosition = vec3(0.0f), vec3 newRotation = vec3(0.0f), vec3 newScale = vec3(1.0f));
        Model3D(vec3 newPosition, vec3 newRotation, vec3 newScale, const char* path, bool invertTexture = false);
        Model3D(const BasicMesh& mesh);
        ~Model3D() override;

        void AddMesh(const BasicMesh& mesh);
        void AddTexture(string type, string path, bool invertTexture, bool clearTexture);

        void Draw();
        void DrawOccluded(const std::vector<Plane>& bspPlanes, const std::vector<bool>& cameraSides);
        BoundingBox GetBoundingBox() const;
        BoundingBox ProcessRecursiveBoundingBox(Transform* node);
        bool IsVisible(const DemoEngine_Camera::Frustum& frustum) const;
        bool drawWireBox = false;

        bool IsAffectedByBspAndFrustum() const { return _isAffectedByBsp; }
        void SetAffectedByBspAndFrustum(bool value) { _isAffectedByBsp = value; }

    private:
        vector<vector<Vertex>> vertices;
        vector<vector<unsigned int>> indices;
        vector<Transform*> meshTransforms;
        vector<vector<Texture>> textures;
        vector<BoundingBox> meshBoundingBoxes;

        vector<unsigned int> vaos;
        vector<unsigned int> vbos;
        vector<unsigned int> ebos;

        bool _isAffectedByBsp;

        void ComputeAABBForMesh(size_t index);

        void DrawBoundingBoxesRecursive(Transform* node);
        bool IsDescendant(Transform* parent, Transform* child);
        
        void DrawRecursive(Transform* node);
        void DrawRecursive(Transform* node, const std::vector<Plane>& bspPlanes, const std::vector<bool>& cameraSides);
    };
}