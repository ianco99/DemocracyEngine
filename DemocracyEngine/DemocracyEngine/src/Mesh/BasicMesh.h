#pragma once
#include <vector>
#include <string>
#include "../Transform.h"

namespace DemoEngine_Entities
{
    struct EXPORT Texture
    {
        unsigned int id = 0;
        std::string type;
        std::string path;
    };
    
    struct EXPORT Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
        glm::vec3 tangent;
        glm::vec3 bitangent;
    };

    struct EXPORT BasicMesh
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;
        Transform* transform = nullptr;

        BasicMesh() = default;

        BasicMesh(std::vector<Vertex> v, std::vector<unsigned int> i, std::vector<Texture> t, Transform* tr)
            : vertices(std::move(v)), indices(std::move(i)), textures(std::move(t)), transform(tr) {}
    };
}