#pragma once
#include "Entity3D.h"
#include "../Mesh/Importer3D.h"

using namespace DemoEngine_Importer;

namespace DemoEngine_Entities
{
    class EXPORT Model3D : public Entity3D
    {
    public:
        Model3D(vec3 newPosition, vec3 newRotation, vec3 newScale, const char* path, bool invertTexture);
        ~Model3D();
        void Draw() override;
        void AddTexture(std::string type, std::string path, bool invertTexture, bool ClearTexture);

    private:
        void AddMesh(const BasicMesh& mesh);

        std::vector<std::vector<Vertex>> vertices;
        std::vector<std::vector<unsigned int>> indices;

        std::vector<unsigned int> vaos;
        std::vector<unsigned int> vbos;
        std::vector<unsigned int> ebos;

        std::vector<std::vector<Texture>> textures;
    };
}