#include "Importer3D.h"
#include "../Tools/stb_image.h"

#include <glew.h>

#include "assimp/postprocess.h"
#include "assimp/Importer.hpp"

namespace DemoEngine_Importer
{
    std::vector<BasicMesh> Importer3D::ImportModel(const std::string& path, bool invertTexture)
    {
        std::vector<BasicMesh> meshes;

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path,
            aiProcess_Triangulate |
            aiProcess_FlipUVs |
            aiProcess_CalcTangentSpace |
            aiProcess_PreTransformVertices);

        std::cout << "sasa";

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
            return meshes;
        }

        const std::string directory = path.substr(0, path.find_last_of('/'));
        std::cout << "Model loaded: " << path << " | Meshes: " << scene->mNumMeshes << std::endl;

        for (unsigned int i = 0; i < scene->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[i];
            meshes.push_back(ProcessMesh(mesh, scene, directory, invertTexture));
        }

        return meshes;
    }

    BasicMesh Importer3D::ProcessMesh(aiMesh* mesh, const aiScene* scene, const std::string& directory, bool invertTexture)
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
            vertex.normal = mesh->HasNormals() ? glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z) : glm::vec3(0.0f);
            vertex.texCoords = mesh->mTextureCoords[0] ? glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y) : glm::vec2(0.0f);
            vertex.tangent = mesh->HasTangentsAndBitangents() ? glm::vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z) : glm::vec3(0.0f);
            vertex.bitangent = mesh->HasTangentsAndBitangents() ? glm::vec3(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z) : glm::vec3(0.0f);
            vertices.push_back(vertex);
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            const aiFace& face = mesh->mFaces[i];
            indices.insert(indices.end(), face.mIndices, face.mIndices + face.mNumIndices);
        }

        if (mesh->mMaterialIndex >= 0)
        {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

            std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", directory, invertTexture);
            std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", directory, invertTexture);
            std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal", directory, invertTexture);
            std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_height", directory, invertTexture);
            std::vector<Texture> BaseColorMaps = LoadMaterialTextures(material, aiTextureType_BASE_COLOR, "texture_baseColor", directory, invertTexture);

            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
            textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
            textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
            textures.insert(textures.end(), BaseColorMaps.begin(), BaseColorMaps.end());
        }

        std::cout << "Mesh loaded: Vertices = " << vertices.size() << ", Indices = " << indices.size() << ", Textures = " << textures.size() << std::endl;
        return BasicMesh(std::move(vertices), std::move(indices), std::move(textures));
    }

    std::vector<Texture> Importer3D::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName, const std::string& directory, bool invertTexture)
    {
        std::vector<Texture> textures;
        std::cout << "Looking for " << typeName << " in material..." << std::endl;

        for (unsigned int i = 0; i < mat->GetTextureCount(type); ++i)
        {
            aiString str;
            if (mat->GetTexture(type, i, &str) != AI_SUCCESS)
            {
                std::cout << "Failed to get texture path for " << typeName << std::endl;
                continue;
            }

            std::string texturePath = directory + "/" + str.C_Str();
            std::cout << "Found texture path: " << texturePath << std::endl;

            unsigned int textureID = LoadTextureFromFile(texturePath.c_str(), invertTexture);
            if (textureID == 0)
            {
                std::cout << "Failed to load texture from file: " << texturePath << std::endl;
                continue;
            }

            Texture texture;
            texture.id = textureID;
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);

            std::cout << "Successfully loaded texture ID: " << textureID << " (" << typeName << ")" << std::endl;
        }

        std::cout << "Loaded " << textures.size() << " textures for type: " << typeName << std::endl;
        return textures;
    }


    unsigned int Importer3D::LoadTextureFromFile(const char* path, bool invertTexture)
    {
        std::cout << "Loading texture from: " << path << std::endl;

        stbi_set_flip_vertically_on_load(invertTexture);
        
        int width, height, nrComponents;
        unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
        if (!data)
        {
            std::cout << "Failed to load texture: " << path << std::endl;
            return 0;
        }

        GLenum format = (nrComponents == 1) ? GL_RED :
                        (nrComponents == 3) ? GL_RGB :
                        GL_RGBA;

        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);  
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
        std::cout << "Texture loaded OK: " << path << ", ID: " << textureID << std::endl;
        return textureID;
    }

}