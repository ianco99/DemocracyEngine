#pragma once
#include <vector>
#include <string>
#include <iostream>

#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include "../Tools/Export.h"

namespace DemoEngine_Importer
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
        glm::vec3 tangent;
        glm::vec3 bitangent;
    };

    struct Texture
    {
        unsigned int id;
        std::string type;
        std::string path;
    };

    struct BasicMesh
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        BasicMesh(std::vector<Vertex> v, std::vector<unsigned int> i, std::vector<Texture> t)
            : vertices(std::move(v)), indices(std::move(i)), textures(std::move(t)) {}
    };

    static class EXPORT Importer3D
    {
    public:
        static std::vector<BasicMesh> ImportModel(const std::string& path, bool invertTexture);
        static unsigned int LoadTextureFromFile(const char* path, bool invertTexture);
    private:
        static BasicMesh ProcessMesh(aiMesh* mesh, const aiScene* scene, const std::string& directory, bool invertTexture);
        static std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName, const std::string& directory, bool invertTexture);
    };
}