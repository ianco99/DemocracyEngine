#pragma once
#include <string>
#include <vector>
#include "../Transform.h"
#include "../Mesh/BasicMesh.h"
#include "../Render/Renderer.h"

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace DemoEngine_Importer
{
    struct ImportedModelData
    {
        std::string name;
        std::vector<DemoEngine_Entities::BasicMesh> meshes;
    };

    class EXPORT Importer3D
    {
    private:
        static std::vector<DemoEngine_Entities::Texture> m_loadedTexturesCache;

        static void ProcessNode(aiNode* node,
                                DemoEngine_Entities::Transform* parentTransform,
                                const aiScene* scene,
                                std::vector<DemoEngine_Entities::BasicMesh>& outMeshes,
                                const std::string& directory,
                                bool invertTexture);

        static DemoEngine_Entities::BasicMesh ProcessMesh(aiMesh* mesh,
                                                           const aiScene* scene,
                                                           const std::string& directory,
                                                           bool invertTexture,
                                                           DemoEngine_Entities::Transform* transform);

        static std::vector<DemoEngine_Entities::Texture> LoadMaterialTextures(aiMaterial* mat,
                                                                              aiTextureType type,
                                                                              const std::string& typeName,
                                                                              const std::string& directory,
                                                                              bool invertTexture);

    public:
        static ImportedModelData ImportModel(const std::string& path,
                                             bool invertTexture = true,
                                             DemoEngine_Entities::Transform* rootTransform = nullptr);

        static unsigned int LoadTextureFromFile(const char* path, bool invertTexture);
    };
}